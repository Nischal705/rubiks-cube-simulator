#pragma once
#include "raylib.h"
#include "rlgl.h"
#include "vector"

enum CUBIE_TYPE { CENTER = 1, EDGE, CORNER };

struct Cubie {
  Vector3 pos;
  std::vector<Color> colors;
  float l = 1.0f;
  float half_l = l / 2;

  Cubie() { colors.assign(6, BLACK); }
  Cubie(Vector3 pos, std::vector<Color> colors) {
    this->pos = pos;
    this->colors = colors;
  }
  void draw() const {
    // just draw the six sides of one cubie

    rlBegin(RL_QUADS);
    // top face 0
    rlColor4ub(colors[0].r, colors[0].g, colors[0].b, 255);
    rlVertex3f(pos.x + half_l, pos.y + half_l, pos.z + half_l);
    rlVertex3f(pos.x + half_l, pos.y + half_l, pos.z - half_l);
    rlVertex3f(pos.x - half_l, pos.y + half_l, pos.z - half_l);
    rlVertex3f(pos.x - half_l, pos.y + half_l, pos.z + half_l);

    // right 1
    rlColor4ub(colors[1].r, colors[1].g, colors[1].b, 255);
    rlVertex3f(pos.x + half_l, pos.y + half_l, pos.z + half_l);
    rlVertex3f(pos.x + half_l, pos.y - half_l, pos.z + half_l);
    rlVertex3f(pos.x + half_l, pos.y - half_l, pos.z - half_l);
    rlVertex3f(pos.x + half_l, pos.y + half_l, pos.z - half_l);

    // front 2
    rlColor4ub(colors[2].r, colors[2].g, colors[2].b, 255);
    rlVertex3f(pos.x - half_l, pos.y + half_l, pos.z + half_l);
    rlVertex3f(pos.x - half_l, pos.y - half_l, pos.z + half_l);
    rlVertex3f(pos.x + half_l, pos.y - half_l, pos.z + half_l);
    rlVertex3f(pos.x + half_l, pos.y + half_l, pos.z + half_l);

    // left 3
    rlColor4ub(colors[3].r, colors[3].g, colors[3].b, 255);
    rlVertex3f(pos.x - half_l, pos.y + half_l, pos.z + half_l);
    rlVertex3f(pos.x - half_l, pos.y + half_l, pos.z - half_l);
    rlVertex3f(pos.x - half_l, pos.y - half_l, pos.z - half_l);
    rlVertex3f(pos.x - half_l, pos.y - half_l, pos.z + half_l);

    // back 4
    rlColor4ub(colors[4].r, colors[4].g, colors[4].b, 255);
    rlVertex3f(pos.x - half_l, pos.y + half_l, pos.z - half_l);
    rlVertex3f(pos.x + half_l, pos.y + half_l, pos.z - half_l);
    rlVertex3f(pos.x + half_l, pos.y - half_l, pos.z - half_l);
    rlVertex3f(pos.x - half_l, pos.y - half_l, pos.z - half_l);

    // down 5
    rlColor4ub(colors[5].r, colors[5].g, colors[5].b, 255);
    rlVertex3f(pos.x - half_l, pos.y - half_l, pos.z - half_l);
    rlVertex3f(pos.x + half_l, pos.y - half_l, pos.z - half_l);
    rlVertex3f(pos.x + half_l, pos.y - half_l, pos.z + half_l);
    rlVertex3f(pos.x - half_l, pos.y - half_l, pos.z + half_l);

    DrawCubeWires(pos, l, l, l, WHITE);
    rlEnd();
  }
};
