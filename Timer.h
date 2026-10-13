#pragma once
#include "raylib.h"
#include <string>
/* ---class for timer
 *
 *  user input
 *  for now
 *  space_key start timer
 *  space_key stop timer
 *
 *  first initial time 0.00s
 *  start timer:
 *   start timer display
 *   save start time
 *
 *  while running:
 *   display curr time - start time
 *
 *  stop timer:
 *   stop timer display
 *   final time displayed in that zone
 *
 *  display space
 *   a dedicated space on the left
 *
 *  SS:mSmS maybe minute to after limit exceeded
 *  maybe make Time struct first that handles addition and display
 */

struct Time {
  int m, s, ms;

  Time() { m = 0, s = 0, ms = 0; };
  Time(int ms) {
    this->ms = ms % 1000;
    s = ms / 1000;
    m = s / 60;
    s %= 60;
    m %= 60;
  }
  Time(int m, int s, int ms) : m(m), s(s), ms(ms) {}

  operator int() { return (m * 60 + s) * 1000 + ms; }

  std::string getString() {
    std::string timeString = "";
    if (m > 0)
      timeString += std::to_string(m) + ":";
    if (s >= 10)
      timeString += std::to_string(s) + ".";
    else if (s >= 0)
      timeString += ("0" + std::to_string(s)) + ".";
    int ms_2_digit = ms / 10;
    if (ms_2_digit >= 10)
      timeString += std::to_string(ms_2_digit);
    else
      timeString += ("0" + std::to_string(ms_2_digit));

    return timeString;
  }
};

enum TIMER_STATE { RUNNING, STOPPED };

class Timer {
  Time t;
  int startTime = 0;
  TIMER_STATE t_state;

  Vector2 pos;
  int fontSize = 30;
  Color fontColor = BLACK;
  int fontSpacing = 2;
  Font fontStyle;

public:
  Timer(Vector2 pos, int fontSize = 30, Color fontColor = BLACK) {
    this->pos = pos;
    this->fontSize = fontSize;
    this->fontColor = fontColor;
    fontStyle =
        LoadFontEx("/usr/share/fonts/truetype/iosevka/Iosevka-BoldItalic.ttf",
                   fontSize, 0, 0);
    t_state = STOPPED;
    startTime = 0;
  }

  std::string getTime() { return t.getString(); }

  void reset() {
    t.m = t.s = t.ms = 0;
    startTime = 0;
  }

  void start() {
    t_state = RUNNING;
    startTime = GetTime() * 1000;
  }

  void stop() { t_state = STOPPED; }

  void update() { // just add FrameTime
    // t += (int)(GetFrameTime() * 1000);
    t = GetTime() * 1000 - startTime;
  }

  void display() {
    DrawTextEx(fontStyle, t.getString().c_str(), pos, fontSize, fontSpacing,
               fontColor);
  }

  bool isRunning() { return t_state == RUNNING; }

  operator int() { return (int)t; }
};
