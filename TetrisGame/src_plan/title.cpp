// title.cpp
#include "title.h"// currentScreen, SCREEN_GAMEPLAY 등

#include <iostream>

static TitleMenuSelector selector;  
static TitleRet titleRet;

// --- Class --- //
TitleMenuSelector::TitleMenuSelector() : modeIndex(0), blitzIndex(0), sprintIndex(0) {
    currentIndex = &modeIndex;
    currentState = 0;

}
void TitleMenuSelector::moveUp() {
    if (*currentIndex > 0) (*currentIndex)--;
}
void TitleMenuSelector::moveDown() {
    if (*currentIndex < optionCount - 1) (*currentIndex)++;
}
int TitleMenuSelector::getIndex() const {
    return (*currentIndex);
}
const char* TitleMenuSelector::getText(int i) const {
    if (currentState == 0) return modeOptions[i];
    else if (currentState == 1) return blitzOptions[i];
    else if (currentState == 2) return sprintOptions[i];
}
void TitleMenuSelector::reset() {
    *currentIndex = 0;
}

int TitleMenuSelector::getCurrentState() {
    return currentState;
}

// --- Helper -----//

void DrawTextInTheMiddle(const char *text, int fontSize, Color color, int y = -1) {
  int textWidth = MeasureText(text, fontSize);
  int y_location;
  y_location = y;

  int x = (GetScreenWidth() - textWidth) / 2;
  if(y == -1) {
    y_location = (GetScreenHeight() / 2) - fontSize / 2;
  }
  DrawText(text, x, y_location, fontSize, color);
}

// --- Function --- //

void InitTitleScreen() {
    selector.reset();  // 선택 위치 초기화
    selector.setCurrentState(0);
}

void DrawTitleScreen(void)
{   
    //Tetris logo
    DrawTextInTheMiddle("Modified by Wonyoung & Eunji", 30, BLACK);
    DrawTextInTheMiddle("up down key to move, enter to select", 20, BLACK, 340);
    
    if(selector.getCurrentState() == 0) {
        DrawTextInTheMiddle("Marathon", 25, BLACK, 400);
        DrawTextInTheMiddle("Sprint", 25, BLACK, 430);
        DrawTextInTheMiddle("Ranking", 25, BLACK, 460);
        DrawTextInTheMiddle("Quit", 25, BLACK, 490);

        if (selector.getIndex() == 0)  DrawTextInTheMiddle("Marathon", 25, RED, 400);
        if (selector.getIndex() == 1)  DrawTextInTheMiddle("Sprint", 25, RED, 430);
        if (selector.getIndex() == 2)  DrawTextInTheMiddle("Ranking", 25, RED, 460);
        if (selector.getIndex() == 3)  DrawTextInTheMiddle("Quit", 25, RED, 490);
    }
    else if (selector.getCurrentState() == 1) {
        DrawTextInTheMiddle("EASY", 25, BLACK, 400);
        DrawTextInTheMiddle("NORMAL", 25, BLACK, 430);
        DrawTextInTheMiddle("HARD", 25, BLACK, 460);
        DrawTextInTheMiddle("BACK", 25, BLACK, 490);

        if (selector.getIndex() == 0)  DrawTextInTheMiddle("EASY", 25, RED, 400);
        if (selector.getIndex() == 1)  DrawTextInTheMiddle("NORMAL", 25, RED, 430);
        if (selector.getIndex() == 2)  DrawTextInTheMiddle("HARD", 25, RED, 460);
        if (selector.getIndex() == 3)  DrawTextInTheMiddle("BACK", 25, RED, 490);
    }
    else if (selector.getCurrentState() == 2) {
        DrawTextInTheMiddle("10 LINE", 25, BLACK, 400);
        DrawTextInTheMiddle("20 LINE", 25, BLACK, 430);
        DrawTextInTheMiddle("40 LINE", 25, BLACK, 460);
        DrawTextInTheMiddle("BACK", 25, BLACK, 490);

        if (selector.getIndex() == 0)  DrawTextInTheMiddle("10 LINE", 25, RED, 400);
        if (selector.getIndex() == 1)  DrawTextInTheMiddle("20 LINE", 25, RED, 430);
        if (selector.getIndex() == 2)  DrawTextInTheMiddle("40 LINE", 25, RED, 460);
        if (selector.getIndex() == 3)  DrawTextInTheMiddle("BACK", 25, RED, 490);
    }
    else std::cout << "error in DrawTitleScreen" << std::endl;
}

TitleRet UpdateTitleScreen(void)
{
    if (IsKeyPressed(KEY_UP)) {
        selector.moveUp();
    }
    if (IsKeyPressed(KEY_DOWN)) {
        selector.moveDown();
    }
    if (IsKeyPressed(KEY_ENTER)) {
        int currentState = selector.getCurrentState();
        int nextState = selector.getIndex();
        if (currentState == 0) {//title
            if (nextState == 0) {
                selector.setCurrentState(1);
                selector.reset();
                // currentScreen  = SCREEN_GAMEPLAY;
                gameMode =  MARATHON;
                // titleInitialized = false;
            }
            if (nextState == 1) {
                selector.setCurrentState(1);
                selector.reset();
                gameMode = SPRINT;
                // titleInitialized = false;

            }
            if (nextState == 2) {
                currentScreen = SCREEN_RANKING;
            }
            if (nextState == 3) {
                CloseWindow();
            }
        }
        else if (currentState == 1) {
            if (nextState == 0) {
                titleRet.hardness = 0;
                titleRet.sprintLine = 0;
            }
            if (nextState == 1) {
                titleRet.hardness = 1;
                titleRet.sprintLine = 0;
            }
            if (nextState == 2) {
                titleRet.hardness = 2;
                titleRet.sprintLine = 0;

            }
            if (nextState == 3) {
                selector.setCurrentState(0);
                selector.reset();
                return titleRet;
            }
            if (gameMode == MARATHON) {
                currentScreen  = SCREEN_GAMEPLAY;
                gameMode = MARATHON;
                titleInitialized = false;
            }
            else if (gameMode == SPRINT) {
                selector.setCurrentState(2);
                selector.reset();
            }
            return titleRet;
        }
        else if (currentState == 2) {
            if (nextState == 0) {
                titleRet.sprintLine =10;
            }
            if (nextState == 1) {
                titleRet.sprintLine =20;
            }
            if (nextState == 2) {
                titleRet.sprintLine =40;
            }
            if (nextState == 3) {
                selector.setCurrentState(1);
                selector.reset();
                return titleRet;
            }
            gameMode = SPRINT;
            currentScreen = SCREEN_GAMEPLAY;
            titleInitialized = false;
            return titleRet;
        }       
        
    }
    // 로고 페이드 애니메이션 등 추가 로직
    return titleRet;
}

void UnloadTitleScreen(void)
{
    // UnloadTexture(logoTexture);
    // UnloadFont(titleFont);
}

void TitleMenuSelector::setCurrentState(int i) {
    currentState = i;
}