// renderer.h
#pragma once

#include "raylib.h"

// 화면 그리기(렌더링)를 담당하는 클래스
class Renderer {
public:
    Renderer();
    ~Renderer();

    // 한 번만 호출: 폰트, 텍스처, 셰이더 등 공통 리소스 로드
    void init();

    // 매 프레임 호출: 내부에서 BeginDrawing(), ClearBackground() 등을 수행
    void beginDraw();

    // 매 프레임 호출: 내부에서 EndDrawing() 수행
    void endDraw();

    // (필요 시) 로드했던 리소스 해제
    void unload();

    //--------------------------------------------
    // 필요에 따라 블록 하나를 그리는 헬퍼 함수 등을 추가하세요.
    // 예:
    // void drawBlock(int x, int y, Color color);
    // void drawTextCentered(const char* text, int x, int y, int fontSize, Color color);
    //--------------------------------------------
};
