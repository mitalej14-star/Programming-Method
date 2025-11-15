// gameplay.cpp
#include "gameplay/gameplay.h"
#include "game.h"       // currentScreen, SCREEN_ENDING 등



// (1) 게임 보드, 블록, 점수 등 내부 데이터
/*
static const int ROWS = 20;
static const int COLS = 10;
static int board[20][10] = { 0 }; // 0: 빈칸, 1~7: 테트로미노 ID

static Texture2D blockTextures[7];
static int currentScore = 0;
static bool gameOver = false;


void InitGameplayScreen(void)
{   
    // 리소스 로드
    for (int i = 0; i < 7; i++) {
        char path[32];
        sprintf(path, "resources/block%d.png", i + 1);
        blockTextures[i] = LoadTexture(path);
    }
    
    // 보드 초기화
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) board[r][c] = 0;
    }
    currentScore = 0;
    gameOver = false;

    // 초기 블록 스폰, 타이머 초기화 등 필요 로직
}


void UpdateGameplayScreen(void)
{
    if (gameOver) {
        currentScreen = SCREEN_ENDING;
        return;
    }

    // 테트리스 로직 (입력 처리, 블록 이동/회전, 충돌 검사, 라인 제거, 점수 계산 등)
    // 예: if (IsKeyPressed(KEY_LEFT)) {  좌측 이동  }
    //     if (IsKeyPressed(KEY_DOWN))  {  빠른 떨어뜨리기  }
    //     // … 그 외 로직 …

    // 예: 특정 점수 이상이면 Ending 화면으로 전환
    // if (currentScore >= targetScore) currentScreen = SCREEN_ENDING;
}

void DrawGameplayScreen(void)
{
    // 배경 그리기
    DrawRectangle(50, 50, COLS*32, ROWS*32, DARKGRAY);

    // 보드 렌더링
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            int id = board[r][c];
            if (id > 0) {
                DrawTexture(blockTextures[id - 1], 50 + c * 32, 50 + r * 32, WHITE);
            }
        }
    }

    // 점수, 다음 블록, 레벨 등 UI 그리기
    DrawText(TextFormat("SCORE: %04d", currentScore), 600, 100, 20, WHITE);
}

void UnloadGameplayScreen(void)
{   
    for (int i = 0; i < 7; i++) {
        UnloadTexture(blockTextures[i]);
    }
} */

TetrisGame::TetrisGame()
    : board_(), current_(), next_(), score_(), input_(), renderer_(),
      isRunning_(false), dropIntervalMs_(500), elapsedSinceLastDropMs_(0)
{ }
TetrisGame::~TetrisGame() {
    //
}
void TetrisGame::init() {
    //
}
void TetrisGame::run() {
    isRunning_ = true;
}

void TetrisGame::update(int deltaMs) {
    
}
