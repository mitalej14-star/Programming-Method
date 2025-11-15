#include "ranking.h"
#include <cmath>

std::vector<std::pair<std::string,int>> scoresForRendering_M;
std::vector<std::pair<std::string,float>> scoresForRendering_S_10;
std::vector<std::pair<std::string,float>> scoresForRendering_S_20;
std::vector<std::pair<std::string,float>> scoresForRendering_S_40;
static Font resultFont;
static RankMenuSelector selector;  
/*
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
*/

std::string diffIntToString(int diff) {
    std::string difficulty;
    switch (diff)
    {
    case 0:
        difficulty = "EASY";
        break;
    case 1:
        difficulty = "NORMAL";
        break;
    case 2:
        difficulty = "HARD";
        break;
    default:
        break;
    }
    return difficulty;
}

std::vector<std::pair<std::string,int>> loadScore_M(int diff) {
    std::string difficulty = diffIntToString(diff);
    std::string filename = "assets/" + difficulty + "/placeholder_M.txt";
    std::vector<std::pair<std::string,int>> scores;
    std::ifstream in{ filename };
    if (!in.is_open()) {
        std::cerr << "cannot open file\n";
        return scores;
    }

    scores.clear();
    std::string line;
    while (std::getline(in, line)) {
        // 빈 줄 건너뛰기
        if (line.empty()) continue;

        // 한 줄을 파싱: "이름 점수"
        std::istringstream iss{ line };
        std::string name;
        int score;
        if (iss >> name >> score) {
            scores.emplace_back(name, score);
        }
        else {
            // 포맷 오류 처리
            std::cerr << "wrong line format" << line << "\n";
        }
    }
    in.close();

    // for (auto& [name, sc] : scores) {
    //     std::cout << name << " : " << sc << "\n";
    // }
    return scores;

}

std::vector<std::pair<std::string,int>> addScores_M(
    std::string newName,
    int newScore,
    int diff
) {
    auto scores = loadScore_M(diff);
    std::string difficulty = diffIntToString(diff);
    // (a) 삽입 위치 찾기: 기존 점수(newScore)보다 작아지는 첫 지점
    auto it = scores.begin();
    while (it != scores.end() && it->second >= newScore) {
        ++it;
    }

    // (b) 삽입
    scores.insert(it, { newName, newScore });

    // (c) 최대 10개까지만 유지
    if (scores.size() > 10)
        scores.resize(10);

    // (d) 파일에 덮어쓰기
    std::string filename = "assets/" + difficulty + "/placeholder_M.txt";
    std::ofstream out{ filename, std::ios::trunc };
    if (!out.is_open()) {
        std::cerr << "cannot open file for writing\n";
        return scores;
    }
    for (auto& [name, sc] : scores) {
        out << name << ' ' << sc << '\n';
    }

    return scores;
}

std::vector<std::pair<std::string,int>> updateUserName_M(int idx, std::string name, int diff) {
    auto scores = loadScore_M(diff);
    scores[idx].first = name;
    
    std::string difficulty = diffIntToString(diff);
    std::string filename = "assets/" + difficulty + "/placeholder_M.txt";
    std::ofstream out{ filename, std::ios::trunc };
    if (!out.is_open()) {
        std::cerr << "cannot open file for writing\n";
        return scores;
    }
    for (auto& [name, sc] : scores) {
        out << name << ' ' << sc << '\n';
    }
    return scores;
}

std::vector<std::pair<std::string, float>> loadScore_S(int diff, int clearLine) {
    std::vector<std::pair<std::string, float>> scores;
    std::string difficulty = diffIntToString(diff);
    // (1) 파일 이름 구성
    std::string filename = "assets/" + difficulty + "/placeholder_S_" + std::to_string(clearLine) + ".txt";

    // (2) 파일 열기
    std::ifstream in{ filename };
    if (!in.is_open()) {
        std::cerr << "cannot open file: " << filename << "\n";
        return scores;
    }

    // (3) 한 줄씩 읽고 파싱
    std::string fileLine;
    while (std::getline(in, fileLine)) {
        if (fileLine.empty()) continue;

        std::istringstream iss{ fileLine };
        std::string name;
        float score;

        if (iss >> name >> score) {
            // 소수점 둘째 자리로 반올림
            score = std::round(score * 100.0f) / 100.0f;
            scores.emplace_back(name, score);
        } else {
            std::cerr << "wrong line format: " << fileLine << "\n";
        }
    }

    return scores;
}


std::vector<std::pair<std::string,float>> addScores_S(
    std::string newName,
    float newScore,
    int diff,
    int clearLine  // line → clearLine 로 명확히
) {
    auto scores = loadScore_S(diff, clearLine);  // ★ 여기서도 전달
    std::string difficulty = diffIntToString(diff);
    // (a) 삽입 위치 찾기
    auto it = scores.begin();
    while (it != scores.end() && it->second <= newScore) {
        ++it;
    }

    // (b) 삽입
    scores.insert(it, { newName, newScore });

    // (c) 최대 10개까지만 유지
    if (scores.size() > 10)
        scores.resize(10);

    // (d) 파일명 결정
    std::string filename = "assets/" + difficulty + "/placeholder_S_" + std::to_string(clearLine) + ".txt";
    std::ofstream out{ filename, std::ios::trunc };
    if (!out.is_open()) {
        std::cerr << "cannot open file for writing: " << filename << "\n";
        return scores;
    }

    for (auto& [name, sc] : scores) {
        out << name << ' ' << sc << '\n';
    }

    return scores;
}

std::vector<std::pair<std::string,float>> updateUserName_S(int idx, std::string name, int diff, int clearLine) {
    auto scores = loadScore_S(diff, clearLine);
    std::string difficulty = diffIntToString(diff);
    scores[idx].first = name;

    std::string filename = "assets/" + difficulty + "/placeholder_S_" + std::to_string(clearLine) + ".txt";
    std::ofstream out{ filename, std::ios::trunc };
    if (!out.is_open()) {
        std::cerr << "cannot open file for writing: " << filename << "\n";
        return scores;
    }

    for (auto& [n, sc] : scores) {
        out << n << ' ' << sc << '\n';
    }

    return scores;
}



void InitRanking() {
    //
}

void DrawRankScreen() {
    int diff = selector.getCurrentState();
    if (diff != 0)DrawTextEx(resultFont, "<", (Vector2){10, 300}, 25, 5, BLACK);
    if (diff != 2)DrawTextEx(resultFont, ">", (Vector2){780, 300}, 20, 3, BLACK);
    std::string difficulty;
    switch (diff)
    {
    case 0:
        difficulty = "EASY";
        break;
    case 1:
        difficulty = "NORMAL";
        break;
    case 2:
        difficulty = "HARD";
        break;
    default:
        break;
    }
    DrawTextEx(resultFont, difficulty.c_str(), (Vector2){340, 50}, 35, 5, BLACK);
    scoresForRendering_M = loadScore_M(diff);
    scoresForRendering_S_10 = loadScore_S(diff, 10);
    scoresForRendering_S_20 = loadScore_S(diff, 20); 
    scoresForRendering_S_40 = loadScore_S(diff, 40); 
    DrawTextEx(resultFont, "MARATHON", (Vector2){30, 150}, 23, 4, BLUE);
    DrawTextEx(resultFont, "SPRINT 10", (Vector2){220, 150}, 23, 4, BLUE);
    DrawTextEx(resultFont, "SPRINT 20", (Vector2){420, 150}, 23, 4, BLUE);
    DrawTextEx(resultFont, "SPRINT 40", (Vector2){620, 150}, 23, 4, BLUE);
    DrawTextEx(resultFont, "PRESS [SPACE] TO TITLE", (Vector2){250, 500}, 20, 3, RED);
    for (int i=0; i<scoresForRendering_M.size(); i++) {
        std::string line = scoresForRendering_M[i].first + ": " + std::to_string(scoresForRendering_M[i].second);
        DrawTextEx(resultFont, line.c_str(), (Vector2){30, 200+30*i}, 20, 2, BLACK);
    }
    for (int j =0; j<scoresForRendering_S_10.size(); j++) {
        const auto& [name, rawTime] = scoresForRendering_S_10[j];
        // TextFormat에서 %.2f가 소수점 둘째 자리까지 포맷
        std::string line = TextFormat("%s: %.2f", name.c_str(), rawTime);
        DrawTextEx(resultFont, line.c_str(), (Vector2){220, 200 + 30*j}, 20, 2, BLACK);
    }
    for (int j =0; j<scoresForRendering_S_20.size(); j++) {
        const auto& [name, rawTime] = scoresForRendering_S_20[j];
        // TextFormat에서 %.2f가 소수점 둘째 자리까지 포맷
        std::string line = TextFormat("%s: %.2f", name.c_str(), rawTime);
        DrawTextEx(resultFont, line.c_str(), (Vector2){420, 200 + 30*j}, 20, 2, BLACK);
    }
    for (int j =0; j<scoresForRendering_S_40.size(); j++) {
        const auto& [name, rawTime] = scoresForRendering_S_40[j];
        // TextFormat에서 %.2f가 소수점 둘째 자리까지 포맷
        std::string line = TextFormat("%s: %.2f", name.c_str(), rawTime);
        DrawTextEx(resultFont, line.c_str(), (Vector2){620, 200 + 30*j}, 20, 2, BLACK);
    }
}




// --- Class --- //
RankMenuSelector::RankMenuSelector() : currentDiff(0) {}
void RankMenuSelector::moveLeft() {
    if (currentDiff > 0) currentDiff--;
}
void RankMenuSelector::moveRight() {
    if (currentDiff < optionCount - 1) currentDiff++;
}
int RankMenuSelector::getIndex() const {
    return currentDiff;
}
const char* RankMenuSelector::getText(int i) const {
    // if (currentState == 0) return modeOptions[i];
    // else if (currentState == 1) return blitzOptions[i];
    // else if (currentState == 2) return sprintOptions[i];
}
void RankMenuSelector::reset() {
    currentDiff = 0;
}

int RankMenuSelector::getCurrentState() {
    return currentDiff;
}

void UpdateRankScreen() {
    if (IsKeyPressed(KEY_LEFT)) {
        selector.moveLeft();
    }
    if (IsKeyPressed(KEY_RIGHT)) {
        selector.moveRight();
    }
    if (IsKeyPressed(KEY_SPACE)) {
        currentScreen = SCREEN_TITLE;
    }
}

std::pair<std::string,int> getBestScore_M(int diff) {
    std::vector<std::pair<std::string,int>> ret = loadScore_M(diff);
    return ret[0];
}
std::pair<std::string,float> getBestScore_S(int diff, int goalLine){
    std::vector<std::pair<std::string,float>> ret = loadScore_S(diff, goalLine);
    return ret[0];
}
