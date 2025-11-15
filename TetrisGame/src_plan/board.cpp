#include "board.h"
#include <iostream>
#include <random>

std::mt19937 rnd(1557);

Board::Board() {
    for(int i = 0; i < WIDTH; i++) {
        for(int j = 0; j < HEIGHT; j++) {
            grid_[i][j] = BACKGROUNDCOLOR;
        }
    }

    // test
    Color b = BACKGROUNDCOLOR, r = RED;
    std::array<std::array<Color, WIDTH>, HEIGHT> temp;
    temp = {{
        {{b, b, b, b, b, b, b, b, b, b}},
        {{b, b, b, b, b, b, b, b, b, b}},
        {{b, b, b, b, b, b, b, b, b, b}},
        {{b, b, b, b, b, b, b, b, b, b}},
        {{b, b, b, b, b, b, b, b, b, b}},
        {{b, b, b, b, b, b, b, b, b, b}},
        {{b, b, b, b, b, b, b, b, b, b}},
        {{b, b, b, b, b, b, b, b, b, b}},
        {{b, b, b, b, b, b, b, b, b, b}},
        {{b, b, b, b, b, b, b, b, b, b}},
        {{b, b, b, b, b, b, b, b, b, b}},
        {{b, b, b, b, b, b, b, b, b, b}},
        {{b, b, b, b, b, b, b, b, b, b}},
        {{b, b, b, b, b, b, b, b, b, b}},
        {{b, b, b, b, b, b, b, b, b, b}},
        {{b, b, b, b, b, b, b, b, b, b}},
        {{b, b, b, b, b, b, b, b, b, b}},
        {{b, b, b, b, b, b, b, b, b, b}},
        {{b, b, b, b, b, b, b, b, b, b}},
        {{b, b, b, b, b, b, b, b, b, b}}
    }};

    for(int i = 0; i < WIDTH; i++) {
        for(int j = 0; j < HEIGHT; j++) {
            grid_[i][j] = temp[j][i];
        }
    }
}

Board::~Board() {}

void Board::reset() {
    for(int i = 0; i < WIDTH; i++) {
        for(int j = 0; j < HEIGHT; j++) {
            grid_[i][j] = BACKGROUNDCOLOR;
        }
    }
}

bool Board::isInside(int x, int y) const {
    return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
}

bool Board::isOccupied(int x, int y) const {
    return (ColorToInt(grid_[x][y]) != ColorToInt(BACKGROUNDCOLOR));
}

bool Board::isValid(const Tetromino tetromino) const {
    std::array<std::array<int, 4>, 4> tet_shape = tetromino.getCurrentMatrix();
    int tet_x = tetromino.getX(), tet_y = tetromino.getY();

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) { 
            if(tet_shape[j][i] && (!isInside(tet_x + i, tet_y + j) || isOccupied(tet_x + i, tet_y + j) ))  {
                return false;
            }
        }
    }

    return true;
}


void Board::setCell(int x, int y, Color color) {
    grid_[x][y] = color;
}

int Board::clearFullLines() {
    int cnt = 0;
    for(int j = HEIGHT - 1; j >= 0; j--) {
        bool flag = true;
        for(int i = 0; i < WIDTH; i++) {
            if(ColorToInt(grid_[i][j]) == ColorToInt(BACKGROUNDCOLOR)) {
                flag = false;
                break;
            }
        }
        if(flag) {
            cnt++;
            for(int i = j; i > 0; i--) {
                for(int k = 0; k < WIDTH; k++) {
                    grid_[k][i] = grid_[k][i - 1];
                }
            }
            for(int k = 0; k < WIDTH; k++) {
                grid_[k][0] = BACKGROUNDCOLOR;
            }
            j++;
        }
    }
    return cnt;
}

void Board::addTetromino(Tetromino tetromino) {
    Color color = tetromino.getColor();
    int x = tetromino.getX(), y = tetromino.getY();
    std::array<std::array<int,4>,4> te_shape = tetromino.getCurrentMatrix();
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(te_shape[j][i] == 1) grid_[x + i][y + j] = color;
        }
    }
}

const std::array<std::array<Color, Board::HEIGHT>, Board::WIDTH>& Board::getGrid() const {
    return grid_;
}

bool Board::addNewLine() {
    // std::cout << "call" << std::endl;
    //over
    for (int i=0; i<WIDTH; i++) {
        if (ColorToInt(grid_[i][1]) != ColorToInt(BACKGROUNDCOLOR)) {
            // std::cout << "ddd" << std::endl;
            return true;
        }
    }
    for(int j = 2; j < HEIGHT; j++) {
        bool isEmpty = true;
        for (int i=0; i<WIDTH; i++) {
            if(ColorToInt(grid_[i][j]) == ColorToInt(BACKGROUNDCOLOR)) {
            isEmpty = false;
            break;
        }
        }
        if (!isEmpty) {
            for (int i=0; i<WIDTH; i++) {
                grid_[i][j-1] = grid_[i][j]; 
            }
        }
    }
    for (int i=0; i<WIDTH; i++) {
        grid_[i][HEIGHT-1] = LIGHTGRAY;
        // std::cout << "red" <<std::endl;
    }

    grid_[std::uniform_int_distribution<int>(0, WIDTH-1)(rnd)][HEIGHT-1] = BACKGROUNDCOLOR;
    return false;
}

bool Board::isGameOver() {
    bool ret;
    for (int i=0; i<WIDTH; i++) {
        if (ColorToInt(grid_[i][1]) != ColorToInt(BACKGROUNDCOLOR)) return true;
    }
    return false;
}