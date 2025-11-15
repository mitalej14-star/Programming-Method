// game.h
#pragma once
#include "raylib.h"

// --- 1) 게임의 화면 상태 정의 (열거형) ---
enum GameScreen {
    SCREEN_TITLE = 0,
    SCREEN_RANKING, 
    SCREEN_GAMEPLAY,
    SCREEN_ENDING
    // 필요에 따라 PAUSE, HIGH_SCORE 등 추가 가능
};
enum GameMode{
    MARATHON =0,
    SPRINT
};

struct TitleRet{
    int hardness;
    int sprintLine;
};
// --- 2) 전역 변수 (현재 화면) ---
extern GameScreen currentScreen;

extern bool titleInitialized;
extern bool rankingInitialized;
extern bool gameplayInitialized;
extern bool endingInitialized;

extern GameMode gameMode;


// --- 4) 메인 루프 관련 함수(선택) ---
// 예를 들어, 각 화면 간 전환 시 처리할 로직을
// 모듈화하고 싶으면 여기도 선언해 두세요.
