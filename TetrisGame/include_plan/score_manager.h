// score_manager.h
#pragma once
#include "raylib.h"
#include "tetromino.h"


class ScoreManager {
public:
    // ScoreManager();
    // ~ScoreManager();

    // 초기화
    void reset();

    // n줄 제거 후 점수 추가 및 레벨 업데이트
    // void addLinesCleared(int n);

    int getScore() const;
    int getCombo() const;
    int getAddScore() const;
    int getTotalLines() const;
    bool getIsBTB() const;
    bool getIsMiniT() const;
    bool getIsFullT() const;

    void addScore(int numClearLine, Tetromino current_);


private:
    int score_= 0;
    int combo_ =0;
    bool isTetrisLast = false;
    bool isTSLast =false;
    int totalClearLine = 0;
    int addScore_ = 0;
    bool isBTB = false;
    bool isMiniT = false;
    bool isFullT = false;
    int TspinAddScore(int isTSRS, int clearLine);
};
