// input_handler.h
#pragma once

#include "raylib.h"
#include "input_type.h"

// 입력 처리를 담당하는 클래스
class InputHandler {
public:
    inputType currentInput;
    InputHandler();
    ~InputHandler();

    // 한 번만 호출: 키 매핑, 내부 상태 초기화 등
    void init();

    // 매 프레임 호출: 현재 키/마우스 상태를 읽어 들이고
    // 필요한 이벤트를 내부 상태에 반영
    void update();

    // (필요 시) 리소스 해제 혹은 뒤처리
    // void unload();

    //--------------------------------------------
    // 필요에 따라 키 입력 상태를 질의할 수 있는 헬퍼 함수들을 추가하세요.
    // 예:
    // bool isLeftPressed() const;
    // bool isRotatePressed() const;
    //--------------------------------------------
};
