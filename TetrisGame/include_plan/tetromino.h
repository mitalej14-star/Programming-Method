// tetromino.h
#pragma once
#include <array>
#include "raylib.h"
//#include "input_type.h"

// 7가지 모양 (I, J, L, O, S, T, Z)
enum Shape { I, J, L, O, S, T, Z };
const std::array<Color, 7> Colors = {{SKYBLUE, BLUE, ORANGE, YELLOW, GREEN, VIOLET, RED}};

class Tetromino {
public:
    Tetromino(Shape shape);
    ~Tetromino();

    void initTetromino();

    // 이동/회전
    //void doInput(inputType currentInput);
    void rotateCW();
    void rotateCCW();
    void moveLeft();
    void moveRight();
    void moveDown();
    void moveUp();

    // set
    void setPosition(int x, int y);
    void setColor(Color color);

    // get
    Shape getShape() const;
    const std::array<std::array<int,4>,4>& getCurrentMatrix() const;
    int getRotationState() const;
    int getX() const;
    int getY() const;
    Color getColor() const;

    // operator overloading
    friend bool operator==(const Tetromino& tet1, const Tetromino& tet2);
    friend bool operator!=(const Tetromino& tet1, const Tetromino& tet2);


    int isTSRS;// 0 - no, 1 - mini, 2- full
    
protected:
    Shape shape_;
    std::array<std::array<int,4>,4> shapeNow_;
    int rotationState_; // 0 1 2 3 시계방향
    int x_, y_; // 4 x 4 행렬에서 (0, 0) 위치
    Color color_;
};

/* derived classes
class Tetromino_I : public Tetromino {
public:
    Tetromino_I();
    ~Tetromino_I();

    // 이동/회전
    void moveLeft();
    void moveRight();
    void moveDown();
    void moveUp();
};

class Tetromino_J : public Tetromino {
public:
    Tetromino_J();
    ~Tetromino_J();

    // 이동/회전
    void moveLeft();
    void moveRight();
    void moveDown();
    void moveUp();
};

class Tetromino_L : public Tetromino {
public:
    Tetromino_L();
    ~Tetromino_L();

    // 이동/회전
    void moveLeft();
    void moveRight();
    void moveDown();
    void moveUp();
};

class Tetromino_O : public Tetromino {
public:
    Tetromino_O();
    ~Tetromino_O();

    // 이동/회전
    void moveLeft();
    void moveRight();
    void moveDown();
    void moveUp();
};

class Tetromino_S : public Tetromino {
public:
    Tetromino_S();
    ~Tetromino_S();

    // 이동/회전
    void moveLeft();
    void moveRight();
    void moveDown();
    void moveUp();
};

class Tetromino_T : public Tetromino {
public:
    Tetromino_T();
    ~Tetromino_T();

    // 이동/회전
    void moveLeft();
    void moveRight();
    void moveDown();
    void moveUp();
};

class Tetromino_Z : public Tetromino {
public:
    Tetromino_Z();
    ~Tetromino_Z();

    // 이동/회전
    void moveLeft();
    void moveRight();
    void moveDown();
    void moveUp();
};
*/