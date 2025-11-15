#include "renderer.h"
#include <iostream>
#include "game.h"

const int board_x0 = (800/2 - Board::WIDTH * 14 + 5);
const int board_y0 = 53;

void DrawBoard(Board& board) {
    DrawRectangle(board_x0 - 5, board_y0 - 5, Board::WIDTH * 24 + 4, Board::HEIGHT * 24 + 4, BLACK);

    std::array<std::array<Color, Board::HEIGHT>, Board::WIDTH> m = board.getGrid();
    for(int i=0; i < Board::WIDTH; i++) {
        for(int j = 0; j < Board::HEIGHT; j++) {
            DrawRectangle(board_x0 + 24*i, board_y0 + 24*j, 18, 18, m[i][j]);
        }
    }
}

void DrawTetromino(const Tetromino& current_) {
    std::array<std::array<int, 4>, 4> tet_shape = current_.getCurrentMatrix();
    Color color = current_.getColor();
    int x = current_.getX(), y = current_.getY();
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(tet_shape[i][j]) DrawRectangle(board_x0 + 24*(x + j), board_y0 + 24*(y + i), 18, 18, color);
        }
    }
}

void DrawNext(std::vector<Tetromino>& tetrominos) {
    DrawText(TextFormat("NEXT"), 130, 15, 30, BLACK);

    for(int k = 0; k < 4; k++) {
        DrawRectangle(120, 50 + 124 * k, 110, 110, DARKGRAY);
        std::array<std::array<int, 4>, 4> tet_shape = tetrominos[k].getCurrentMatrix();
        Color color = tetrominos[k].getColor();
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                if(tet_shape[i][j]) DrawRectangle(130 + 24*j, 60 + 124 * k + 24*i, 18, 18, color);
            }
        }
    }
}

void DrawHold(const Tetromino& tetromino, bool ishold) {
    DrawText(TextFormat("HOLD"), 545, 385, 30, BLACK);
    DrawRectangle(530, 420, 110, 110, DARKGRAY);
    if(!ishold) return;
    std::array<std::array<int, 4>, 4> tet_shape = tetromino.getCurrentMatrix();
    Color color = tetromino.getColor();
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(tet_shape[i][j]) DrawRectangle(540 + 24*j, 430 + 24*i, 18, 18, color);
        }
    }
}


void DrawTime(double time) {
    DrawText(TextFormat("TIME: %.2f", time), 575, 60, 30, BLACK);
}

void DrawScore(int score) {
    DrawText(TextFormat("SCORE: %04d", score), 550, 120, 30, BLACK);
}

void DrawBTB() {
    DrawText("BTB", 370, 110, 23, WHITE);
}

void DrawMiniT() {
    DrawText("mini Tspin", 330, 200, 23, WHITE);
}

void DrawFullT() {
    DrawText("full Tspin", 330, 200, 23, WHITE);
}

void DrawCombo(int combo) {
    DrawText(TextFormat("Combo: %04d", combo), 320, 140, 23, WHITE);
}

void DrawAddScore(int addScore) {
    DrawText(TextFormat("+ %d", addScore), 360, 170, 23, WHITE);
}

void DrawMode (GameMode gameMode, int totalClearLine, int difficulty, int goalLine) {
    DrawText("BEST SCORE", 550, 310, 23, BLACK);
    if (gameMode == MARATHON) {
        std::pair<std::string, int> best_M = getBestScore_M(difficulty);
        std::string bestm = best_M.first + " " + std::to_string(best_M.second);
        DrawText(bestm.c_str(), 550, 330, 23, BLACK);
    }
    else if (gameMode == SPRINT) {
        std::pair<std::string, int> best_S = getBestScore_S(difficulty, goalLine);
        std::string bests = best_S.first + " " + std::to_string(best_S.second);
        DrawText(bests.c_str(), 550, 330, 23, BLACK);
    }
    std::string lineClear = "Line Clear: " + std::to_string(totalClearLine);
    if (gameMode == MARATHON) {
        DrawText("MARATHON", 550, 200, 25, BLUE);
        DrawText(lineClear.c_str(), 550, 250, 23, RED);
    }
    else if (gameMode == SPRINT) {
        DrawText("SPRINT", 550, 200, 25, BLUE);
        DrawText(lineClear.c_str(), 550, 250, 23, RED);
        std::string goal = "GOAL: " + std::to_string(goalLine) + " LINE";
        DrawText(goal.c_str(), 550, 280, 23, RED);
    }
    else std::cout << "error in RenderMode" <<std::endl;  

}