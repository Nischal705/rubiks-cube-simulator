#pragma once
#include "constants.h"
#include "fileHandler.h"
#include "raylib.h"
#include <string>
#include <vector>

namespace DisplayHandler {
// for box
float x = 10, y = 10;
float w = 0.3 * (float)SCREEN_WIDTH, h = 500;
float roundedness = 0.15f;
int segments = 8;
Color color = GRAY;
int rows = fileHandler::N;
// for data
float sn_start_x = x + 10;
float sn_start_y = y + 20;
int fontSize = 37;
int step_y = fontSize + 5;    // line height
float time_start_x = x + 100; // starting x for time column
Font fontStyle;

void initialize() {
  fontStyle = LoadFontEx("/usr/share/fonts/truetype/iosevka/Iosevka-Bold.ttf",
                         fontSize, 0, 0);
  fileHandler::updateLatestTimesArray();
  fileHandler::syncPBwithHistory();
}
void displayHistoryBox() {
  DrawRectangleRounded({x, y, w, h}, roundedness, 16, color);

  for (int row = 0; row < rows + 1; row++) {
    if (row < rows) {
      std::string sn = std::to_string(row + 1) + ".";
      std::string time = fileHandler::latestTimesArray[row];

      DrawTextEx(fontStyle, sn.c_str(), {sn_start_x, sn_start_y + row * step_y},
                 fontSize, segments, BLACK);
      DrawTextEx(fontStyle, time.c_str(),
                 {time_start_x, sn_start_y + row * step_y}, fontSize, 2, BLACK);
    } else {
      // display pb
      DrawTextEx(fontStyle, "PB:", {sn_start_x, sn_start_y + row * step_y},
                 fontSize, 2, BLACK);
      DrawTextEx(fontStyle, fileHandler::getPBinObject().getString().c_str(),
                 {time_start_x, sn_start_y + row * step_y}, fontSize, 2, BLACK);
    }
  }
}

} // namespace DisplayHandler
