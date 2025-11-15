#include <raylib.h>

void DrawTextInTheMiddle(const char *text, int fontSize, Color color) {
  int textWidth = MeasureText(text, fontSize);
  int x = (GetScreenWidth() - textWidth) / 2;
  int y = (GetScreenHeight() / 2) - fontSize / 2;

  DrawText(text, x, y, fontSize, color);
}

int main() {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(300, 600, "Term Project");
  SetTargetFPS(60);

  while (WindowShouldClose() == false) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTextInTheMiddle("Start Your Term Project!", 20, BLACK);
    EndDrawing();
  }

  CloseWindow();
}
