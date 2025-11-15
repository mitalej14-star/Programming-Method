// ending.h
#pragma once

#include "raylib.h"
#include "ending.h"
#include <string>
#include <vector>

// Ending 화면 전용 리소스(예: 점수 공유 UI, 다시 시작 버튼 등)
// extern Font resultFont;

void UpdateEndingScreen(void);
void DrawEndingScreen(void);
void InitEndingScreen(int totalScore, float totalTime, bool isGameClear, int difficulty, int goalClearLine);
void DrawNameSpace();
void updateRealName();
void DrawRankInEnding();