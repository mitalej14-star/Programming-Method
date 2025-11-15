// board.h
#pragma once
#include <array>
#include "tetromino.h"

class Board {
public:
    static constexpr int WIDTH = 10;
    static constexpr int HEIGHT = 20;
    static constexpr Color BACKGROUNDCOLOR = DARKGRAY;

    
    Board();
    ~Board();

    // 보드 초기화
    void reset();

    // (x,y)가 범위 내인지
    bool isInside(int x, int y) const;

    // (x,y)에 블록이 차 있는지
    bool isOccupied(int x, int y) const;

    // 테트로미노가 들어갈 수 있는지
    bool isValid(const Tetromino Tetromino) const;

    // (x,y)에 색상(color)을 채움 (0은 빈 칸)
    void setCell(int x, int y, Color color);

    // 꽉 찬 줄을 제거하고, 지워진 줄 수를 반환
    int clearFullLines();

    // 보드에 테트로미노 추가
    void addTetromino(Tetromino tetromino);

    // 보드 렌더링 시 사용할 그리드 정보 반환
    const std::array<std::array<Color, HEIGHT>, WIDTH>& getGrid() const;

    //
    bool addNewLine();
    bool isGameOver();
private:
    std::array<std::array<Color, HEIGHT>, WIDTH> grid_;
};
