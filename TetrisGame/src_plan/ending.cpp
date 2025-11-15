// ending.cpp

#include "game.h"
#include "ranking.h"   // currentScreen, SCREEN_TITLE 등
#include "ending.h"
#include <iostream>

static Font resultFont;
static int finalScore_M = 0;
static float finalScore_S = 0;
static std::vector<std::pair<std::string,int>> scores_M;
static std::vector<std::pair<std::string,float>> scores_S;
static std::string name = "";
static bool nameEntered = false;
static bool nameEntering = false;
static bool nameUpdate = false;
static bool isGameClear = false;
static int difficulty;
static int clearLine;

void InitEndingScreen(int totalScore, float totalTime, bool isGameClear_, int difficulty_, int goalClearLine) {
    name = "";
    nameEntered = false;
    nameEntering = false;
    nameUpdate = false;
    finalScore_M = totalScore;
    finalScore_S = totalTime;
    isGameClear = isGameClear_;
    difficulty = difficulty_;
    clearLine = goalClearLine; ///받아서 변경
    if (gameMode == MARATHON) {
        static std::vector<std::pair<std::string,int>> newScore;
        std::pair<std::string, int> needToAdd;
        needToAdd = {"!YOU!", finalScore_M};
        newScore = addScores_M(needToAdd.first, needToAdd.second, difficulty);
        scores_M = newScore;
    }
    else if (gameMode == SPRINT) {
        if (isGameClear) {
            static std::vector<std::pair<std::string,float>> newScore;
            std::pair<std::string, float> needToAdd;
            needToAdd = {"!YOU!", finalScore_S};
            newScore = addScores_S(needToAdd.first, needToAdd.second, difficulty, clearLine);
            scores_S = newScore;
        }
        else {
            scores_S = loadScore_S(difficulty, clearLine);
        }
    }
}

void UpdateEndingScreen(void)
{
    int key = GetCharPressed();

    // 다시 시작하거나 종료 선택
    if (!nameEntering && IsKeyPressed(KEY_ENTER)) {
        currentScreen = SCREEN_TITLE; // 타이틀로 돌아가기
        endingInitialized = false;
        if (!nameUpdate) {
            std::cout << "nameUP>";
            std::cout << "MOde" << gameMode;
            std::cout << "CG: " << isGameClear << std::endl;
            if (gameMode == MARATHON) {
                for (int i=0; i<scores_M.size(); i++) {
                    if (scores_M[i].first == "!YOU!") scores_M = updateUserName_M(i, "USER", difficulty);
                }
            }
            else if ((gameMode == SPRINT) && isGameClear) {
                std::cout << "nameUPdatecalled";
                for (int i=0; i<scores_S.size(); i++) {
                    if (scores_S[i].first == "!YOU!") scores_S = updateUserName_S(i, "USER", difficulty, clearLine);
                }
            }
            
        }
        isGameClear = false;
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        // 메인 루프가 끝나도록 아무 동작도 안 함
        // 또는 강제 윈도우 종료 요청
    }
    if (IsKeyPressed(KEY_TAB) && !nameEntered) {
        nameEntering = true;
    }
    
    if (nameEntering) {
        if (key>0) {
            if ((key >= 32) && (key <= 125) && name.length() < 10 && key != '!') {
                name += (char)key;
            }
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && !name.empty()) {
            name.pop_back();
        }
        if (IsKeyPressed(KEY_ENTER) && !name.empty()) {
            nameUpdate = true;
            if (name == "") name = "USER";
            nameEntered = true;
            nameEntering = false;
            if (gameMode == MARATHON) {
                for (int i=0; i<scores_M.size(); i++) {
                    if (scores_M[i].first == "!YOU!") scores_M = updateUserName_M(i, name, difficulty);
                }
            }
            else if ((gameMode == SPRINT) && isGameClear) {
                for (int i=0; i<scores_S.size(); i++) {
                    if (scores_S[i].first == "!YOU!") scores_S = updateUserName_S(i, name, difficulty, clearLine);
                }
            }
                // for (auto& [name, sc] : scores) {
            //     std::cout << name << " : " << sc << "\n";
            // }s
        }
    }
}   

void DrawEndingScreen(void)
{   
    //print ranking
    if (nameEntering) {
        DrawNameSpace();
        return ;
    }
    // if (gameMode == SPRINT) DrawTextEx(resultFont, std::to_string(clearLine).c_str(), (Vector2){10, 80}, 20, 2, RED);
    if ((gameMode == SPRINT) && isGameClear) DrawTextEx(resultFont, TextFormat("GAME CLEAR"), (Vector2){300, 200}, 48, 2, RED);
    else DrawTextEx(resultFont, TextFormat("GAME OVER"), (Vector2){300, 200}, 48, 2, RED);
    std::string diffRender, gameModeRender;
    switch (difficulty)
    {
    case 0:
        diffRender = "EASY";
        break;
    case 1:
        diffRender = "NORMAL";
        break;
    case 2:
        diffRender = "HARD";
        break;
    default:
        break;
    }
    switch (gameMode) {
    case MARATHON:
        gameModeRender = "MARATHON";
        break;
    case SPRINT:
        switch (clearLine) {
        case 10:
            gameModeRender = "SPRINT 10";
            break;
        case 20:
            gameModeRender = "SPRINT 20";
            break;
        case 40:
            gameModeRender = "SPRINT 40";
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    DrawTextEx(resultFont, diffRender.c_str(), (Vector2){50, 90}, 24, 2, BLACK);
    DrawTextEx(resultFont, gameModeRender.c_str(), (Vector2){50, 60}, 24, 2, BLACK);
    DrawTextEx(resultFont, "PRESS [ENTER] TO RESTART", (Vector2){250, 400}, 24, 2, BLUE);
    if (nameEntered) DrawTextEx(resultFont, name.c_str(), (Vector2){450, 450}, 24, 2, BLACK);
    else {
        DrawTextEx(resultFont, "PRESS [TAB] TO ENTER YOUR NAME", (Vector2){210, 450}, 24, 2, BLUE);
        DrawTextEx(resultFont, "(DEFAUILT:USER)", (Vector2){340, 480}, 24, 2, BLUE);
    }
    DrawRankInEnding();
}


void DrawNameSpace() {
    DrawTextEx(resultFont, TextFormat(name.c_str()), (Vector2){350, 200}, 48, 2, BLACK);
    DrawTextEx(resultFont, "PRESS [ENTER] TO FINISH YOUR NAME", (Vector2){170, 400}, 24, 2, RED);
    if (gameMode == MARATHON) {
        DrawTextEx(resultFont, TextFormat("FINAL SCORE: %04d", finalScore_M), (Vector2){240, 280}, 32, 2, BLACK);
    }
    else if (gameMode == SPRINT) {
        DrawTextEx(resultFont, TextFormat("FINAL SCORE: %.2f", finalScore_S), (Vector2){250, 280}, 32, 2, BLACK);
    }
}

void DrawRankInEnding() {
    DrawTextEx(resultFont, "RANKING", (Vector2){50, 130}, 23, 2, BLACK);
    if (gameMode == MARATHON) {
        DrawTextEx(resultFont, TextFormat("FINAL SCORE: %04d", finalScore_M), (Vector2){310, 280}, 32, 2, RED);
        std::string temp;
        for (int i=0; i<scores_M.size(); i++) {
        std::string line = scores_M[i].first + ": " + std::to_string(scores_M[i].second);
            DrawTextEx(resultFont, line.c_str(), (Vector2){50, 170+30*i}, 20, 2, BLACK);
        }
    }
    else if (gameMode == SPRINT) {
        DrawTextEx(resultFont, TextFormat("FINAL SCORE: %.2f", finalScore_S), (Vector2){310, 280}, 32, 2, RED);
        std::string temp;
        for (int i=0; i<scores_S.size(); i++) {
            const auto& [rendname, rawTime] = scores_S[i];
            // TextFormat에서 %.2f가 소수점 둘째 자리까지 포맷
            std::string time = TextFormat("%s: %.2f", rendname.c_str(), rawTime);
            DrawTextEx(resultFont, time.c_str(), (Vector2){50, 170 + 30*i}, 20, 2, BLACK);
        }
    }
}
