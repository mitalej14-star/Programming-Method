// gameplay.cpp
#include "gameplay.h"
#include <random>
#include <vector>
#include <algorithm>
#include <iostream>       // currentScreen, SCREEN_ENDING 등
std::random_device rd;
std::mt19937 rndt(rd());
//std::mt19937 rndt(1);
std::vector<int> tetnumbers = {0, 1, 2, 3, 4, 5, 6};
int tetnum = 0;
std::vector<Shape> testTet = {J,Z,O,L,T,S,I,O,T,J,L,Z,I,S,T,Z,O,S,J,L,I,L,T,O,S,J,I,Z,T,L,Z,S,I,O,J};

TetrisGame::TetrisGame() : board_(), current_(I), hold_(I), ishold_(false),  nexts_(), score_(), input_(), isRunning_(true), 
fastLine_(10), fastConst_(0.9), dropIntervalMs_(1.0f), newLineInterval_(30.0f), elapsedSinceLastDropMs_(0.0f), elapsedSinceLastNewLine_ (0.0f),
realtime(0.0f), gameOver(false), isScoreAdded_(false) {
    std::shuffle(tetnumbers.begin(), tetnumbers.end(), rndt);

    // random
    //for(int i = 0 ; i < 6; i++) { nexts_.push_back(Tetromino(static_cast<Shape>(tetnumbers[i]))); }
    // test
    for(int i = 0 ; i < testTet.size(); i++) { nexts_.push_back(Tetromino(testTet[i])); }
    
    DrawGameStart();
    current_ = nexts_[0];
    nexts_.erase(nexts_.begin());
    tetnum++;
    gameStartTime_ = GetTime();
    gameMode_ = MARATHON;
    totalClearLine_ = 0;
    goalClearLine_ = 0;
    isGameClear_ = false;
}

void TetrisGame::DrawGameStart() {
    double startTime = GetTime();
    while (GetTime() - startTime < 3.0 && !WindowShouldClose()) {
        double elapsed = GetTime() - startTime;
        ClearBackground(RAYWHITE);   
        BeginDrawing();
        DrawBoard(board_);
        DrawTime(0);
        DrawScore(0);
        DrawNext(nexts_);
        DrawHold(hold_, ishold_);
        if (elapsed < 1.0) DrawText("3", 360, 170, 80, WHITE);
        else if (elapsed < 2.0) DrawText("2", 360, 170, 80, WHITE);
        else if (elapsed < 3.0) DrawText("1", 360, 170, 80, WHITE);
        EndDrawing();
    }
}

bool TetrisGame::run() {
    bool ret;
    ret = update();
    render();
    return ret;
}

bool TetrisGame::update() {
    //빨라짐
    if ((gameMode_ == SPRINT) && (totalClearLine_ >= goalClearLine_)) {
        isRunning_ = false;
        isGameClear_ = true;
    }
    bool isDrop = timeUpdate_return_isDrop();
    input_.update();
    if (board_.isGameOver()) {
        isRunning_ = false;
    }
    //tetUpdate는 Drop을 실패하면 false반환, 이 경우 current_는 end
    if(isTetEnd() || !tetUpdate(isDrop)) { // 시간제한 or hard drop
        board_.addTetromino(current_);
        // score_ += board_.clearFullLines();
        int clearLine = board_.clearFullLines();
        totalClearLine_ += clearLine;
        score_.addScore(clearLine, current_);
        if(clearLine > 0) {
            isScoreAdded_ = true;
            scoreEffectStartTime_ = GetTime();
        }
        else isScoreAdded_ = false;
        current_ = nexts_[0];
        nexts_.erase(nexts_.begin());
        if(tetnum == 0) std::shuffle(tetnumbers.begin(), tetnumbers.end(), rndt);
        nexts_.push_back(Tetromino(static_cast<Shape>(tetnumbers[tetnum])));
        tetnum = (tetnum + 1) % 7;
        render();
    }
    isDrop = false;
    if (!isRunning_) {
        currentScreen = SCREEN_ENDING;
        gameplayInitialized = false;
        endingInitialized = false;
        return false;
    }
    return true;
}

void TetrisGame::holdSwap() {
    if(!ishold_) {
        hold_ = current_;
        current_ = nexts_[0];
        nexts_.erase(nexts_.begin());
        if(tetnum == 0) std::shuffle(tetnumbers.begin(), tetnumbers.end(), rndt);
        nexts_.push_back(Tetromino(static_cast<Shape>(tetnumbers[tetnum])));
        tetnum = (tetnum + 1) % 7;
        hold_.isTSRS = false;
        ishold_ = true;
        return;
    }

    Tetromino temp(current_), curtemp(hold_);
    curtemp.setPosition(temp.getX(), temp.getY());
    if(board_.isValid(curtemp)) {
        current_ = curtemp;
        hold_ = temp;
        hold_.isTSRS = false;
    }
    else {
        return;
    }
}


bool TetrisGame::timeUpdate_return_isDrop() {
    bool isDrop = false;
    float deltaTime = GetFrameTime();
    elapsedSinceLastDropMs_ += deltaTime;
    elapsedSinceLastNewLine_ += deltaTime;
    realtime += deltaTime;
    if ((score_.getTotalLines() != 0) && score_.getTotalLines() >= fastLine_) {
        dropIntervalMs_ *= 0.9f;
        fastLine_ += 2;
    }
    if (elapsedSinceLastNewLine_ > newLineInterval_) {
        isRunning_ = !board_.addNewLine();
        elapsedSinceLastNewLine_ = 0.0f; 
    }
    if (elapsedSinceLastDropMs_> dropIntervalMs_) {
        isDrop = true;
        elapsedSinceLastDropMs_ = 0.0f;
    }
    return isDrop;
}

void TetrisGame::render() {
    ClearBackground(RAYWHITE);   
    BeginDrawing();
    DrawBoard(board_);
    DrawTetromino(current_);
    DrawTetromino(Ghost());
    DrawTime(GetTime() - gameStartTime_);
    DrawScore(score_.getScore());
    if (isScoreAdded_ && GetTime() - scoreEffectStartTime_ < 1.5) {
        if(isScoreAdded_) DrawAddScore(score_.getAddScore());
        if(isScoreAdded_ && score_.getCombo() > 0) DrawCombo(score_.getCombo());
        if(isScoreAdded_ && score_.getIsBTB()) DrawBTB();
        if(isScoreAdded_ && score_.getIsMiniT()) DrawMiniT();
        if(isScoreAdded_ && score_.getIsFullT()) DrawFullT();
    }
    DrawNext(nexts_);
    DrawHold(hold_, ishold_);
    DrawMode (gameMode_, totalClearLine_, difficulty_, goalClearLine_);
    EndDrawing(); 
}

const Tetromino TetrisGame::Ghost() {
    Tetromino temp(current_);
    Color ghost(LIGHTGRAY);
    ghost.a = 100;
    while (true) {
        temp.moveDown();
        if(!board_.isValid(temp)) {
            break;
        }
    }
    temp.moveUp();
    temp.setColor(ghost);
    return temp;
}

bool TetrisGame::isTetEnd() {
    if(input_.currentInput == HARD_DROP) {
        while (true) {
            current_.moveDown();
            if(!board_.isValid(current_)) {
                break;
            }
        }
        current_.moveUp();
        return true;
    }
    
    return false;
}

bool TetrisGame::tetUpdate(bool isDrop) {
    if (isDrop) {
        current_.moveDown();
        if (!board_.isValid(current_)) {
            current_.moveUp();
            return false; //isDrop이 실패하면 false로 바꿈
            int nomeaning;
        }
    }
    bool isNormalMove;
    Tetromino temp(current_);
    inputType input = input_.currentInput;
    if (input == MOVE_LEFT) {
        current_.moveLeft();
        if(!board_.isValid(current_)) current_.moveRight();
        input = NORMAL;
    }
    if (input == MOVE_RIGHT) {
        current_.moveRight();
        if(!board_.isValid(current_)) current_.moveLeft();
        input = NORMAL;
    }
    if (input == SOFT_DROP) {
        current_.moveDown();
        if(!board_.isValid(current_)) current_.moveUp();
        input = NORMAL;
    }
    if (input == HOLD_SWAP) {
        holdSwap();
        input = NORMAL;
    }
    if (temp.getX() == current_.getX() && temp.getY() == current_.getY()) {
        //블럭이 움직이지 않았으면 아무것도 안함
    }
    else current_.isTSRS = false; //normal move했으면 T spin아님님
    // if (input == HARD_DROP) {}
    if (input == ROTATE_CW) {
        SRSRotationCW(current_);
        input = NORMAL;
    }
    if (input == ROTATE_CCW) {
        SRSRotationCCW(current_);
        input = NORMAL;
    } //여기서 Tspin켜줌
    // if (input == HOLD_SWAP) {}
    return true;
}

void TetrisGame::isTspin(Tetromino& tet, int wallkickn) {
    int x0 = tet.getX() + 1, y0 = tet.getY() + 2;
    int x1, y1, cntf = 0, cntb = 0;;
    std::array<std::array<int,4>,4> tetShape = tet.getCurrentMatrix();
    for(int i = -1; i < 2; i += 2){
        if(tetShape[2 + i][1] == 0) {
            x1 = 0; y1 = -i;
            for(int j = -1; j < 2; j += 2) {
                if(board_.isOccupied(x0 + j, y0 + y1) || !board_.isInside(x0 + j, y0 + y1)) cntf++;
                if(board_.isOccupied(x0 + j, y0 - y1) || !board_.isInside(x0 + j, y0 - y1)) cntb++;
            }
            break;
        }
        else if(tetShape[2][1 + i] == 0) {
            x1 = -i; y1 = 0;
            for(int j = -1; j < 2; j += 2) {
                if(board_.isOccupied(x0 + x1, y0 + j) || !board_.isInside(x0 + x1, y0 + j)) cntf++;
                if(board_.isOccupied(x0 - x1, y0 + j) || !board_.isInside(x0 - x1, y0 + j)) cntb++;
            }
            break;
        }
    }
    tet.isTSRS = 0;
    if(cntf + cntb > 2) {
        tet.isTSRS++;
        if(cntf > 1 || wallkickn == 4) tet.isTSRS++;
    }
}

void TetrisGame::SRSRotationCW(Tetromino& tet) {
    int dx, dy;
    int rotationState = tet.getRotationState();
    int rot = 2 * rotationState; // 표에서 행 0, 2, 4, 6
    Tetromino temp = tet;
    if(tet.getShape() == O) return;
    if(tet.getShape() == I) {
        for(int i = 0; i < 5; i++) {
            dx = WallKick_I[rot][i][0];
            dy = WallKick_I[rot][i][1];
            temp = tet;

            for(int j = 0; j < dx; j++) { // dx > 0
                temp.moveRight();
            }
            for(int j = dx; j < 0; j++) { // dx < 0
                temp.moveLeft();
            }
            for(int j = 0; j < dy; j++) { // dy > 0
                temp.moveUp();
            }
            for(int j = dy; j < 0; j++) { // dy < 0
                temp.moveDown();
            }
            temp.rotateCW();

            if(board_.isValid(temp)) {
                tet = temp;
                return;
            }
        }
    }
    else {
        for(int i = 0; i < 5; i++) {
            dx = WallKick_ELSE[rot][i][0];
            dy = WallKick_ELSE[rot][i][1];
            temp = tet;

            for(int j = 0; j < dx; j++) { // dx > 0
                temp.moveRight();
            }
            for(int j = dx; j < 0; j++) { // dx < 0
                temp.moveLeft();
            }
            for(int j = 0; j < dy; j++) { // dy > 0
                temp.moveUp();
            }
            for(int j = dy; j < 0; j++) { // dy < 0
                temp.moveDown();
            }
            temp.rotateCW();

            if(board_.isValid(temp)) {
                tet = temp;
                if ((tet.getShape() == T)) {
                    isTspin(tet, i);
                }
                return;
            }
        }
    }
}

void TetrisGame::SRSRotationCCW(Tetromino& tet) {
    int dx, dy;
    int rotationState = tet.getRotationState();
    int rot = 1 + 2 * ((rotationState + 3) % 4); // 표에서 행 1, 3, 5, 7
    Tetromino temp = tet;
    if(tet.getShape() == O) return;
    if(tet.getShape() == I) {
        for(int i = 0; i < 5; i++) {
            dx = WallKick_I[rot][i][0];
            dy = WallKick_I[rot][i][1];
            temp = tet;

            for(int j = 0; j < dx; j++) { // dx > 0
                temp.moveRight();
            }
            for(int j = dx; j < 0; j++) { // dx < 0
                temp.moveLeft();
            }
            for(int j = 0; j < dy; j++) { // dy > 0
                temp.moveUp();
            }
            for(int j = dy; j < 0; j++) { // dy < 0
                temp.moveDown();
            }
            temp.rotateCCW();

            if(board_.isValid(temp)) {
                tet = temp;
                return;
            }
        }
    }
    else {
        for(int i = 0; i < 5; i++) {
            dx = WallKick_ELSE[rot][i][0];
            dy = WallKick_ELSE[rot][i][1];
            temp = tet;

            for(int j = 0; j < dx; j++) { // dx > 0
                temp.moveRight();
            }
            for(int j = dx; j < 0; j++) { // dx < 0
                temp.moveLeft();
            }
            for(int j = 0; j < dy; j++) { // dy > 0
                temp.moveUp();
            }
            for(int j = dy; j < 0; j++) { // dy < 0
                temp.moveDown();
            }
            temp.rotateCCW();

            if(board_.isValid(temp)) {
                tet = temp;
                if ((tet.getShape() == T)) {
                    isTspin(tet, i);
                }
                return;
            }
        }
    }
}

int TetrisGame::getScore() {
    return score_.getScore();
}

float TetrisGame::getTime() {
    return realtime;
}

void TetrisGame::setMode(GameMode gameMode, TitleRet titleRet) {
    gameMode_ = gameMode;
    dropIntervalMs_ = 1.0 - titleRet.hardness * 0.25;
    if (gameMode == SPRINT) goalClearLine_ = titleRet.sprintLine;
    difficulty_ = titleRet.hardness;
}

bool TetrisGame::getClear() {
    return isGameClear_;
}

int TetrisGame::getGoalClearLine() {
    return goalClearLine_;
}

int TetrisGame::getDifficulty() {
    return difficulty_;
}