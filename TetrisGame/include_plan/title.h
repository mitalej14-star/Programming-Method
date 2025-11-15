// title.h
#pragma once

#include "raylib.h"
#include "ranking.h"
#include "game.h"

// Title 화면 전용으로 사용하는 리소스(텍스처/폰트/변수 등)를 여기에 extern 선언
// 예: extern Texture2D logoTexture;
//      extern Font titleFont;
//      extern bool titleTransitionDone;

class TitleMenuSelector {
public:
    TitleMenuSelector();
    void moveUp();
    void moveDown();
    int getIndex() const;
    const char* getText(int i) const;
    void reset();
    int getCurrentState();
    void setCurrentState(int i);

private:
    int currentState; //0 title 1/난이도Marathon blitz// 2//Sprint Blitz// 3//spint Line
    int* currentIndex;
    static constexpr int optionCount = 4;
    const char* modeOptions[optionCount] = { "Marathon", "Sprint", "Ranking", "Quit" };
    const char* blitzOptions[optionCount] = { "EASY", "NORMAL", "HARD", "BACK"};
    const char* sprintOptions[optionCount] = { "10 LINE", "20 LINE", "40 LINE", "BACK"};
    int finalBlitz;
    int modeIndex, blitzIndex, sprintIndex;
};
// helper
void DreawTextInTheMiddle(const char *text, int fontSize, Color color);

// Title 화면 관련 함수
void InitTitleScreen(void);
TitleRet UpdateTitleScreen(void);
void DrawTitleScreen(void);
void UnloadTitleScreen(void);