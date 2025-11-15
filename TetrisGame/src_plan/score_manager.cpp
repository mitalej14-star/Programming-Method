#include "score_manager.h"
#include <iostream>

int ScoreManager::getScore() const{
    return score_;
}
int ScoreManager::getCombo() const {
    return combo_;
}
int ScoreManager::getAddScore() const {
    return addScore_;
}
int ScoreManager::getTotalLines() const {
    return totalClearLine;
}
bool ScoreManager::getIsBTB() const {
    return isBTB;
}
bool ScoreManager::getIsMiniT() const {
    return isMiniT;
}
bool ScoreManager::getIsFullT() const {
    return isFullT;
}
void ScoreManager::addScore(int numClearLine, Tetromino current_) {
    isMiniT = false;
    isFullT = false;
    int addScore =0;
    combo_ += 1;
    int double_ = 0;
    switch (numClearLine)
    {
    case 0:
        combo_ = 0;
        break;
    case 1:
        addScore += 100;
        break;
    case 2:
        addScore += 300;
        break;
    case 3:
        addScore += 500;
        break;
    case 4:
        if (isTetrisLast || isTSLast) double_ = 1;
        addScore += 800;
        isTetrisLast = true;
        break;
    default:
        break;
    }
    bool temp_TSLast = false;
    if (combo_ > 1) addScore += combo_ * 50;
    if (current_.isTSRS > 0 && numClearLine > 0) {
        if (isTSLast || isTetrisLast) double_ = 1;
        addScore += TspinAddScore(current_.isTSRS, numClearLine);
        temp_TSLast = true;
    }
    if (numClearLine > 0) isTSLast = temp_TSLast;
    score_ += addScore + addScore*double_;
    addScore_ = addScore + addScore*double_;
    if(numClearLine > 0 && numClearLine < 4) isTetrisLast = false;
    if(double_ == 1) isBTB = true;
    else isBTB = false;
    totalClearLine += numClearLine;
    return ; 
}

int ScoreManager::TspinAddScore(int isTSRS, int clearLine) {
    if(isTSRS == 1) {
        isMiniT = true;
        if(clearLine == 1) return 100;
        if(clearLine == 2) return 100;
    }
    else if(isTSRS == 2) {
        isFullT = true;
        if(clearLine == 1) return 700;
        if(clearLine == 2) return 900;
        if(clearLine == 3) return 1100;
    }
    return 0;
}