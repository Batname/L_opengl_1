#include "Game.hpp"

Game *game;

int main(int argc, const char * argv[]) {
    game = new Game();
    return game->render();
}
