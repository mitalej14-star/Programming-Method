#include "input_handler.h"
#include <iostream>

InputHandler::InputHandler() {}
InputHandler::~InputHandler() {}

void InputHandler::init() {}
void InputHandler::update() {
    currentInput = NORMAL;
    if (IsKeyPressed(KEY_LEFT)) currentInput = MOVE_LEFT;
    if (IsKeyPressed(KEY_RIGHT)) currentInput = MOVE_RIGHT;
    if (IsKeyPressed(KEY_DOWN)) currentInput = SOFT_DROP;
    if (IsKeyPressed(KEY_SPACE)) currentInput = HARD_DROP;
    if (IsKeyPressed(KEY_Z)) currentInput = ROTATE_CCW;
    if (IsKeyPressed(KEY_X) || IsKeyPressed(KEY_UP)) currentInput = ROTATE_CW;
    if (IsKeyPressed(KEY_C)) currentInput = HOLD_SWAP;
}
