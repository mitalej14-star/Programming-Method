// score_manager.h
#pragma once

class ScoreManager {
public:
    ScoreManager();
    ~ScoreManager();

    // 초기화
    void reset();

    // n줄 제거 후 점수 추가 및 레벨 업데이트
    void addLinesCleared(int n);

    int getScore() const;
    int getLevel() const;
    int getTotalLines() const;

    // 현재 레벨에 따른 블록 자동 하강 속도 (밀리초)
    int getDropIntervalMs() const;

private:
    int score_;
    int level_;
    int totalLinesCleared_;
};
