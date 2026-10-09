#pragma once
#include "Moves.h"
#include "raylib.h"
#include "rlgl.h"
#include "vector"
#include <cmath>

enum CUBIE_TYPE { CENTER = 1, EDGE, CORNER };

struct Cubie {
  Vector3 pos;
  std::vector<Color> colors;
  float padding = 0.01f;
  float l = 1.0f;
  float padded_half_l = l / 2 - padding;
  float half_l = l / 2;

  Cubie() { colors.assign(6, BLACK); }
  Cubie(Vector3 pos, std::vector<Color> colors) {
    this->pos = pos;
    this->colors = colors;
  }
  void draw() const {
    // just draw the six sides of one cubie
    DrawCube(pos, l - 0.01f, l - 0.01f, l - 0.01f, BLACK);

    rlBegin(RL_QUADS);
    // top face 0
    rlColor4ub(colors[0].r, colors[0].g, colors[0].b, 255);
    rlVertex3f(pos.x + padded_half_l, pos.y + half_l, pos.z + padded_half_l);
    rlVertex3f(pos.x + padded_half_l, pos.y + half_l, pos.z - padded_half_l);
    rlVertex3f(pos.x - padded_half_l, pos.y + half_l, pos.z - padded_half_l);
    rlVertex3f(pos.x - padded_half_l, pos.y + half_l, pos.z + padded_half_l);

    // right 1
    rlColor4ub(colors[1].r, colors[1].g, colors[1].b, 255);
    rlVertex3f(pos.x + half_l, pos.y + padded_half_l, pos.z + padded_half_l);
    rlVertex3f(pos.x + half_l, pos.y - padded_half_l, pos.z + padded_half_l);
    rlVertex3f(pos.x + half_l, pos.y - padded_half_l, pos.z - padded_half_l);
    rlVertex3f(pos.x + half_l, pos.y + padded_half_l, pos.z - padded_half_l);

    // front 2
    rlColor4ub(colors[2].r, colors[2].g, colors[2].b, 255);
    rlVertex3f(pos.x - padded_half_l, pos.y + padded_half_l, pos.z + half_l);
    rlVertex3f(pos.x - padded_half_l, pos.y - padded_half_l, pos.z + half_l);
    rlVertex3f(pos.x + padded_half_l, pos.y - padded_half_l, pos.z + half_l);
    rlVertex3f(pos.x + padded_half_l, pos.y + padded_half_l, pos.z + half_l);

    // left 3
    rlColor4ub(colors[3].r, colors[3].g, colors[3].b, 255);
    rlVertex3f(pos.x - half_l, pos.y + padded_half_l, pos.z + padded_half_l);
    rlVertex3f(pos.x - half_l, pos.y + padded_half_l, pos.z - padded_half_l);
    rlVertex3f(pos.x - half_l, pos.y - padded_half_l, pos.z - padded_half_l);
    rlVertex3f(pos.x - half_l, pos.y - padded_half_l, pos.z + padded_half_l);

    // back 4
    rlColor4ub(colors[4].r, colors[4].g, colors[4].b, 255);
    rlVertex3f(pos.x - padded_half_l, pos.y + padded_half_l, pos.z - half_l);
    rlVertex3f(pos.x + padded_half_l, pos.y + padded_half_l, pos.z - half_l);
    rlVertex3f(pos.x + padded_half_l, pos.y - padded_half_l, pos.z - half_l);
    rlVertex3f(pos.x - padded_half_l, pos.y - padded_half_l, pos.z - half_l);

    // down 5
    rlColor4ub(colors[5].r, colors[5].g, colors[5].b, 255);
    rlVertex3f(pos.x - padded_half_l, pos.y - half_l, pos.z - padded_half_l);
    rlVertex3f(pos.x + padded_half_l, pos.y - half_l, pos.z - padded_half_l);
    rlVertex3f(pos.x + padded_half_l, pos.y - half_l, pos.z + padded_half_l);
    rlVertex3f(pos.x - padded_half_l, pos.y - half_l, pos.z + padded_half_l);

    // DrawCubeWires(pos, l, l, l, BLACK);
    rlEnd();
  }

  bool fallsInFace(Move::MOVE curr_move) const {
    float ok_error = 0.01f;
    switch (curr_move) {
    case Move::R:
    case Move::R_PRIME:
      return fabs(this->pos.x - l) <= ok_error;
    case Move::L:
    case Move::L_PRIME:
      return fabs(this->pos.x + l) <= ok_error;
    case Move::D:
    case Move::D_PRIME:
      return fabs(this->pos.y + l) <= ok_error;
    case Move::U:
    case Move::U_PRIME:
      return fabs(this->pos.y - l) <= ok_error;
    case Move::F:
    case Move::F_PRIME:
      return fabs(this->pos.z - l) <= ok_error;
    case Move::B:
    case Move::B_PRIME:
      return fabs(this->pos.z + l) <= ok_error;
    case Move::Y:
    case Move::Y_PRIME:
    case Move::X:
    case Move::X_PRIME:
      return true;
    default:
      return false;
    }
  }
};
