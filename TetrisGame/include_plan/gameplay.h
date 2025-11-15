// gameplay.h
#pragma once

#include "tetromino.h"
#include "board.h"
#include "renderer.h"
#include "input_handler.h"
#include "wall_kick.h"
#include "score_manager.h"
#include "game.h"

#include "input_type.h"

class TetrisGame {
public:
    TetrisGame();

    bool run();

    void SRSRotationCW(Tetromino& tet);
    void SRSRotationCCW(Tetromino& tet);

    void holdSwap();

    bool tetUpdate(bool isDrop);
    bool isTetEnd();
    const Tetromino Ghost();

    int getScore();
    float getTime();

    float realtime = 0.0f;
    bool gameOver = false;

    void setMode(GameMode gameMode, TitleRet titleRet);
    bool getClear();
    int getGoalClearLine();
    int getDifficulty();

private:
    Board board_;
    Tetromino current_;
    Tetromino hold_;
    bool ishold_;
    std::vector<Tetromino> nexts_;
    ScoreManager score_;
    InputHandler input_;
    GameMode gameMode_;

    bool isRunning_;
    int fastLine_ = 2; //second for time faseter
    int fastConst_ = 0.9; // speed up by fastConst*current speed;
   
    bool isGameOver_ = false;
    float dropIntervalMs_; //second for drop
    float newLineInterval_; //second for newline
    float elapsedSinceLastDropMs_;
    float elapsedSinceLastNewLine_;

    bool isScoreAdded_;
    double scoreEffectStartTime_ = -1.0;
    double gameStartTime_;

    int totalClearLine_;

    bool isGameClear_ = false;
    int goalClearLine_;
    int difficulty_;

    // 한 프레임마다 업데이트 << 지금은 그냥 update함수
    bool update();
    bool timeUpdate_return_isDrop(); //time update && drop decision

    // 화면 그리기
    void render();

    void DrawGameStart();
    void isTspin(Tetromino& tet, int wallkickn);

};
