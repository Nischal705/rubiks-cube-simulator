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
  Time(int ms) : m(0), s(0), ms(ms) {};
  Time(int m, int s, int ms) : m(m), s(s), ms(ms) {}

  void operator+=(Time delta) {
    ms += delta.ms;
    if (ms >= 1000) {
      ms %= 1000;
      s++;
    }
    if (s >= 60) {
      s %= 60;
      m++;
    }
    if (m >= 60) {
      m %= 60; // display some msg instead of time later in timer class
    }
  }

  std::string getString() {
    std::string timeString = "";
    if (m > 0)
      timeString += std::to_string(m) + ":";
    if (s >= 10)
      timeString += std::to_string(s) + ":";
    else if (s >= 0)
      timeString += ("0" + std::to_string(s)) + ":";
    if (ms >= 100)
      timeString += std::to_string(ms);
    else if (ms >= 10)
      timeString += ("0" + std::to_string(ms));
    else
      timeString += ("00" + std::to_string(ms));

    return timeString;
  }
};

enum TIMER_STATE { RUNNING, STOPPED };

class Timer {
  Time t;
  TIMER_STATE t_state;

  Vector2 pos;
  int fontSize = 30;
  Color fontColor = BLACK;
  int fontSpacing = 2;
  Font fontStyle = LoadFont("/usr/share/fonts/truetype/lato/Lato-Black.ttf");

public:
  Timer() { t_state = STOPPED; }

  void setTimerAttributes(Vector2 pos, int fontSize = 30,
                          Color fontColor = BLACK) {
    this->pos = pos;
    this->fontSize = fontSize;
    this->fontColor = fontColor;
  }

  void reset() { t.m = t.s = t.ms = 0; }

  void start() { t_state = RUNNING; }

  void stop() { t_state = STOPPED; }

  void update() { // just add FrameTime
    t += (int)(GetFrameTime() * 1000);
  }

  void display() {
    DrawTextEx(fontStyle, t.getString().c_str(), pos, fontSize, fontSpacing,
               fontColor);
  }

  bool isRunning() { return t_state == RUNNING; }

};
