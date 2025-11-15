// board.h
#pragma once
#include <array>

class Board {
public:
    static constexpr int WIDTH = 10;
    static constexpr int HEIGHT = 20;
    
    Board();
    ~Board();

    // 보드 초기화
    void reset();

    // (x,y)가 범위 내인지
    bool isInside(int x, int y) const;

    // (x,y)에 블록이 차 있는지
    bool isOccupied(int x, int y) const;

    // (x,y)에 색상(color)을 채움 (0은 빈 칸)
    void setCell(int x, int y, int color);

    // 꽉 찬 줄을 제거하고, 지워진 줄 수를 반환
    int clearFullLines();

    // 보드 렌더링 시 사용할 그리드 정보 반환
    const std::array<std::array<int, WIDTH>, HEIGHT>& getGrid() const;

private:
    std::array<std::array<int, WIDTH>, HEIGHT> grid_;
};
