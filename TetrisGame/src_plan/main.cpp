// main.cpp
#include "raylib.h"
#include "game.h"         // GameScreen, 함수 프로토타입, currentScreen extern
#include "title.h"
#include "gameplay.h"
#include "ending.h"

#include <iostream>

// --- 1) 전역 변수 정의 ---
GameScreen currentScreen = SCREEN_TITLE;  // 처음엔 타이틀 화면
bool titleInitialized = false;
bool rankingInitialized =false;
bool gameplayInitialized = false;
bool endingInitialized = false;
GameMode gameMode = MARATHON;

// (Optional) 각 화면 초기화/언로드 상태 플래그
int main(void)
{
    // Raylib 윈도우, 폰트 등 초기화
    InitWindow(800, 600, "Tetris Example");
    SetTargetFPS(60);

    TetrisGame* currentGame = nullptr;
    int totalScore =0;
    float totalTime = 0.0;
    bool isGameClear = false;
    int goalClearLine = 0;
    int difficulty = -1;
    TitleRet titleRet; //0 easy 1 normal 2 hard

    while (true) {
        if (!WindowShouldClose() && currentScreen == SCREEN_TITLE) {
            if (!titleInitialized) {
                InitTitleScreen();
                titleInitialized = true;
            }
            titleRet = UpdateTitleScreen();
            ClearBackground(RAYWHITE);
            BeginDrawing();
            DrawTitleScreen();
            EndDrawing();
        } //finish

        if (!WindowShouldClose() && currentScreen == SCREEN_RANKING) {
            if (!rankingInitialized) {
                InitRanking();
                rankingInitialized = true;
            }
            UpdateRankScreen();
            ClearBackground(RAYWHITE);
            BeginDrawing();
            DrawRankScreen();
            EndDrawing();
        } //finish

        if (!WindowShouldClose() && currentScreen == SCREEN_GAMEPLAY) {
            if (!gameplayInitialized) {
                //titleRet
                currentGame = new TetrisGame;
                currentGame->setMode(gameMode, titleRet);
                gameplayInitialized = true;
            } 
            gameplayInitialized = currentGame->run();
            totalScore = currentGame->getScore();
            totalTime = currentGame->getTime();
            isGameClear = currentGame->getClear();
            goalClearLine = currentGame->getGoalClearLine();
            difficulty = currentGame->getDifficulty();
        }
        
        if (!WindowShouldClose() && currentScreen == SCREEN_ENDING) {
            if (!endingInitialized) {
                endingInitialized = true;
                InitEndingScreen(totalScore, totalTime, isGameClear, difficulty, goalClearLine);
            }
            UpdateEndingScreen();
            ClearBackground(RAYWHITE);
            BeginDrawing();
            DrawEndingScreen();
            EndDrawing();
        }
        if (WindowShouldClose()) {
            CloseWindow();
            break;
        }
    }
    return 0;
}
