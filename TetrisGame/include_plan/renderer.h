// renderer.h
#pragma once
#include <vector>

#include "raylib.h"
#include "board.h"
#include "game.h"
#include "ranking.h"

// 보드 그리기
void DrawBoard(Board& board);
void DrawTetromino(const Tetromino& current_);
void DrawNext(std::vector<Tetromino>& tetrominos);
void DrawHold(const Tetromino& tetromino, bool ishold);

void DrawTime(double time);
void DrawScore(int score);
void DrawBTB();
void DrawMiniT();
void DrawFullT();
void DrawCombo(int combo);
void DrawAddScore(int addScore);
void DrawMode (GameMode gameMode, int totalClearLine, int difficulty, int goalLine);