const BOARD_HEIGHT = 5;
const BOARD_WIDTH = 9;

function GamePawn(x, y) {
    this.element = document.createElement("td");
    this.x = x;
    this.y = y;
    this.state = 0;
    this.onClickCallback = null;

    this.setState = (state) => {
        if(state) { this.state = state; }
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
            this.selectedPawn = null;
        }else {
            this.selectedPawn = pawn;
        }

    }

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

let gb = new GameBoard(document.getElementById("pawnTable"));
gb.setPawnStates([[2,2,2,1,1],[2,2,1,1,1],[2,2,2,1,1],[2,2,1,1,1],[2,2,0,1,1], [2,2,2,1,1],[2,2,1,1,1],[2,2,2,1,1],[2,2,1,1,1]]);