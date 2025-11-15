#pragma once
#include "raylib.h"
#include "game.h"
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include <iostream>

std::vector<std::pair<std::string,int>> loadScore_M(int diff);
std::vector<std::pair<std::string,int>> addScores_M(std::string name, int totalScore, int diff);
std::vector<std::pair<std::string,int>> updateUserName_M(int idx, std::string name, int diff);

std::vector<std::pair<std::string,float>> loadScore_S(int diff, int line);
std::vector<std::pair<std::string,float>> addScores_S(std::string name, float totalTime, int diff, int line);
std::vector<std::pair<std::string,float>> updateUserName_S(int idx, std::string name, int diff, int line);

void InitRanking();
void DrawRankScreen();
std::string diffIntToString(int diff);
// void DrawTextInTheMiddle(const char *text, int fontSize, Color color, int y = -1);
std::pair<std::string,int> getBestScore_M(int diff);
std::pair<std::string,float> getBestScore_S(int diff, int goalLine);

class RankMenuSelector {
public:
    RankMenuSelector();
    void moveRight();
    void moveLeft();
    int getIndex() const;
    const char* getText(int i) const;
    void reset();
    int getCurrentState();
    void setCurrentState(int i);

private:
    int currentDiff; //0 title 1/난이도Marathon blitz// 2//Sprint Blitz// 3//spint Line
    static constexpr int optionCount = 3;
    const char* options[optionCount] = { "EASY", "NORMAL", "HARD"};

};

void UpdateRankScreen();