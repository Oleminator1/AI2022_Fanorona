const BOARD_HEIGHT = 5;
const BOARD_WIDTH = 9;
const GAME_SERVER = "ws://127.0.0.1:9002";

function MessageBox(element) {
    this.element = element;

    this.setMessage = (message, state) => {
        this.element.textContent = message;
        this.element.className = "message message-" + state;
    }
    this.setInfo = (message) => this.setMessage(message, "info");
    this.setError = (message) => this.setMessage(message, "error");
    this.setSuccess = (message) => this.setMessage(message, "success");
}
function GamePawn(x, y) {
    this.element = document.createElement("td");
    this.x = x;
    this.y = y;
    this.state = 0;
    this.onClickCallback = null;

    this.setState = (state) => {
        if(typeof(state) !== "undefined") { this.state = state; }
        this.element.className = "pawn " + this.getClass();
    }

    this.getClass = () => {
        switch(this.state) {
            case 0: return "pawn-empty";
            case 1: return "pawn-player1";
            case 2: return "pawn-player2";
            default: return "";
        }
    }
    this.getElement = () => this.element;
    this.onClick = (callback) => this.onClickCallback = callback;

    this.element.addEventListener("click", () => {
        console.log(this.x + ", " + this.y + " clicked");
        if(this.onClickCallback){ this.onClickCallback(this); }
    })
    this.setState();
}
function GameBoard(table) {
    this.table = table;
    this.pawns = [];
    this.selectedPawn = null;
    this.onPawnMoveCallback = null;

    this.setPawnStates = (pawnStates) => {
        for(let y = 0; y < BOARD_HEIGHT; y++) {
            for(let x = 0; x < BOARD_WIDTH; x++) {
                this.setPawnState(x,y,pawnStates[x][y]);
            }
        }
    }
    this.setPawnState = (x, y, pawnState) => {
        this.pawns.find(p => p.x === x && p.y === y).setState(pawnState);
    }
    this.pawnClicked = (pawn) => {
        if(this.selectedPawn) {
            // Transfer state
            console.log("move from " + this.selectedPawn.x + ", "+ this.selectedPawn.y + " to " + pawn.x + ", "+ pawn.y);
            this.onPawnMoveCallback({ row: this.selectedPawn.y, col: this.selectedPawn.x }, { row: pawn.y, col: pawn.x });
            this.selectedPawn = null;
        }else {
            this.selectedPawn = pawn;
        }

    }

    this.onPawnMove = (callback) => this.onPawnMoveCallback = callback;

    for(let y = 0; y < BOARD_HEIGHT; y++) {
        let row = document.createElement("tr");
        for(let x = 0; x < BOARD_WIDTH; x++) {
            let pawn = new GamePawn(x, y);
            pawn.onClick(pawn => this.pawnClicked(pawn));
            this.pawns.push(pawn);
            row.appendChild(pawn.getElement());
        }
        this.table.appendChild(row);
    }
}
function GameConnection(address) {
    this.address = address;
    this.sock = new WebSocket(address);

    this.onBoardUpdateCallback = null;
    this.onErrorCallback = null;
    this.onConnectedCallback = null;

    this.connect = () => {
        this.sock = new WebSocket(this.address);
        this.sock.addEventListener("message", e => this.onMessage(JSON.parse(e.data)));
        this.sock.addEventListener("open", e => this.onConnectedCallback());
    }
    this.startGame = () => {
        this.sock.send(JSON.stringify({ command: "start" }));
    }
    this.movePawn = (from, to) => {
        this.sock.send(JSON.stringify({ command: "move", from, to }));
    }
    this.onMessage = (msg) => {
        if(msg.command === "board") {
            this.onBoardUpdateCallback(msg.board);
        } else if(msg.command === "error") {
            this.onErrorCallback(msg.message);
        } else {
            console.error("Unknown command: " + msg.command);
        }
    }

    this.onBoardUpdate = (callback) => this.onBoardUpdateCallback = callback;
    this.onError = (callback) => this.onErrorCallback = callback;
    this.onConnected = (callback) => this.onConnectedCallback = callback;
}

let mb = new MessageBox(document.getElementById("message"));
let gb = new GameBoard(document.getElementById("pawnTable"));

let gc = new GameConnection(GAME_SERVER);
gc.onBoardUpdate(board => gb.setPawnStates(board[0].map((_, colIndex) => board.map(row => row[colIndex]))));
gc.onError(message => mb.setError(message));
gc.onConnected(() => {
    gc.startGame();
});

gb.onPawnMove((from, to) => {
    gc.movePawn(from, to);
});

gc.connect();

//gb.setPawnStates([[2,2,2,1,1],[2,2,1,1,1],[2,2,2,1,1],[2,2,1,1,1],[2,2,0,1,1], [2,2,2,1,1],[2,2,1,1,1],[2,2,2,1,1],[2,2,1,1,1]]);