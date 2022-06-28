cmake_minimum_required(VERSION 3.1.0)
project(fanorona-server VERSION 0.1.0)
find_package(Threads REQUIRED)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
add_executable(fanorona-server main.cpp game/FanoronaGame.cpp game/players/GamePlayer.cpp game/players/HumanPlayer.cpp game/players/AiPlayer.cpp)

target_link_libraries(fanorona-server PRIVATE Threads::Threads)

include_directories(include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
