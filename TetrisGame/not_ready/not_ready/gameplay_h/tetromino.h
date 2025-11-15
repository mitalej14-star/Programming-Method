// tetromino.h
#pragma once
#include <array>

class Tetromino {
public:
    // 7가지 모양 (I, J, L, O, S, T, Z)
    enum Shape { I, J, L, O, S, T, Z };

    Tetromino(Shape shape);
    ~Tetromino();

    // 이동/회전
    void rotate();
    void moveLeft();
    void moveRight();
    void moveDown();
    void moveUp(); // (충돌 시 원상 복귀용)

    // 현재 위치 & 상태 얻기
    int getX() const;
    int getY() const;
    void setPosition(int x, int y);

    // 현재 4×4 매트릭스 반환 (0/1로 블록 형태)
    const std::array<std::array<int,4>,4>& getCurrentMatrix() const;

    // 블록 색상(렌더링용)
    int getColor() const;

private:
    Shape shape_;
    int rotationState_;
    int x_, y_;
    static const std::array<std::array<std::array<int,4>,4>, 7> shapes_; 
};
