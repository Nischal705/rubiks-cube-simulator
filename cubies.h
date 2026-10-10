#pragma once
#include "Maths.h"
#include "Moves.h"
#include "raylib.h"
#include "rlgl.h"
#include "vector"
#include <cmath>

// enum CORNER_NAME {  = 0, T };

struct Cubie {
  Vector3 pos;
  std::vector<Color> colors;
  float padding = 0.92f; // scaling factor
  float l = 1.0f;
  float half_l = l / 2;
  float innerCubeLen = 0.9 * padding * l;
  Vector3 corner_vecs[8] = {
      {half_l, half_l, half_l},    {half_l, half_l, -half_l},
      {-half_l, half_l, -half_l},  {-half_l, half_l, half_l},
      {half_l, -half_l, half_l},   {-half_l, -half_l, half_l},
      {-half_l, -half_l, -half_l}, {half_l, -half_l, -half_l}};

  Cubie() { colors.assign(6, BLACK); }
  Cubie(Vector3 pos, std::vector<Color> colors) {
    this->pos = pos;
    this->colors = colors;
  }
  void draw() const {
    // just draw the six sides of one cubie
    //
    //
    //
    DrawCube(pos, innerCubeLen, innerCubeLen, innerCubeLen, BLACK);

    rlBegin(RL_QUADS);
    // extract r, u, f and their padded version
    // later replace it with direction extraction from basic vector
    // top face 0
    rlColor4ub(colors[0].r, colors[0].g, colors[0].b, 255);
    rlVertex3f(pos.x + (corner_vecs[0].x * padding),
               pos.y + corner_vecs[0].y * padding,
               pos.z + (corner_vecs[0].z * padding));
    rlVertex3f(pos.x + (corner_vecs[1].x * padding),
               pos.y + corner_vecs[1].y * padding,
               pos.z + (corner_vecs[1].z * padding));
    rlVertex3f(pos.x + (corner_vecs[2].x * padding),
               pos.y + corner_vecs[2].y * padding,
               pos.z + (corner_vecs[2].z * padding));
    rlVertex3f(pos.x + (corner_vecs[3].x * padding),
               pos.y + corner_vecs[3].y * padding,
               pos.z + (corner_vecs[3].z * padding));

    // right 1
    rlColor4ub(colors[1].r, colors[1].g, colors[1].b, 255);
    rlVertex3f(pos.x + corner_vecs[0].x * padding,
               pos.y + (corner_vecs[0].y * padding),
               pos.z + (corner_vecs[0].z * padding));
    rlVertex3f(pos.x + corner_vecs[4].x * padding,
               pos.y + (corner_vecs[4].y * padding),
               pos.z + (corner_vecs[4].z * padding));
    rlVertex3f(pos.x + corner_vecs[7].x * padding,
               pos.y + (corner_vecs[7].y * padding),
               pos.z + (corner_vecs[7].z * padding));
    rlVertex3f(pos.x + corner_vecs[1].x * padding,
               pos.y + (corner_vecs[1].y * padding),
               pos.z + (corner_vecs[1].z * padding));

    // front 2
    // staring from corner 3
    rlColor4ub(colors[2].r, colors[2].g, colors[2].b, 255);
    rlVertex3f(pos.x + (corner_vecs[3].x * padding),
               pos.y + (corner_vecs[3].y * padding),
               pos.z + corner_vecs[3].z * padding);
    rlVertex3f(pos.x + (corner_vecs[5].x * padding),
               pos.y + (corner_vecs[5].y * padding),
               pos.z + corner_vecs[5].z * padding);
    rlVertex3f(pos.x + (corner_vecs[4].x * padding),
               pos.y + (corner_vecs[4].y * padding),
               pos.z + corner_vecs[4].z * padding);
    rlVertex3f(pos.x + (corner_vecs[0].x * padding),
               pos.y + (corner_vecs[0].y * padding),
               pos.z + corner_vecs[0].z * padding);

    // left 3
    // starting from corner 3
    rlColor4ub(colors[3].r, colors[3].g, colors[3].b, 255);
    rlVertex3f(pos.x + corner_vecs[3].x * padding,
               pos.y + (corner_vecs[3].y * padding),
               pos.z + (corner_vecs[3].z * padding));
    rlVertex3f(pos.x + corner_vecs[2].x * padding,
               pos.y + (corner_vecs[2].y * padding),
               pos.z + (corner_vecs[2].z * padding));
    rlVertex3f(pos.x + corner_vecs[6].x * padding,
               pos.y + (corner_vecs[6].y * padding),
               pos.z + (corner_vecs[6].z * padding));
    rlVertex3f(pos.x + corner_vecs[5].x * padding,
               pos.y + (corner_vecs[5].y * padding),
               pos.z + (corner_vecs[5].z * padding));

    // back 4
    // starting from corner 1
    rlColor4ub(colors[4].r, colors[4].g, colors[4].b, 255);
    rlVertex3f(pos.x + (corner_vecs[1].x * padding),
               pos.y + (corner_vecs[1].y * padding),
               pos.z + corner_vecs[1].z * padding);
    rlVertex3f(pos.x + (corner_vecs[7].x * padding),
               pos.y + (corner_vecs[7].y * padding),
               pos.z + corner_vecs[7].z * padding);
    rlVertex3f(pos.x + (corner_vecs[6].x * padding),
               pos.y + (corner_vecs[6].y * padding),
               pos.z + corner_vecs[6].z * padding);
    rlVertex3f(pos.x + (corner_vecs[2].x * padding),
               pos.y + (corner_vecs[2].y * padding),
               pos.z + corner_vecs[2].z * padding);

    // down 5
    // starting from corner 4
    rlColor4ub(colors[5].r, colors[5].g, colors[5].b, 255);
    rlVertex3f(pos.x + (corner_vecs[4].x * padding),
               pos.y + corner_vecs[4].y * padding,
               pos.z + (corner_vecs[4].z * padding));
    rlVertex3f(pos.x + (corner_vecs[5].x * padding),
               pos.y + corner_vecs[5].y * padding,
               pos.z + (corner_vecs[5].z * padding));
    rlVertex3f(pos.x + (corner_vecs[6].x * padding),
               pos.y + corner_vecs[6].y * padding,
               pos.z + (corner_vecs[6].z * padding));
    rlVertex3f(pos.x + (corner_vecs[7].x * padding),
               pos.y + corner_vecs[7].y * padding,
               pos.z + (corner_vecs[7].z * padding));

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

  void updatePositionAndOrientation(Move::MOVE curr_move) {
    Vector3 axis = Move::getAxis(curr_move);
    pos = Maths::rotatePlus90AroundGivenAxis(pos, axis);
    for (int i = 0; i < 8; i++) {
      corner_vecs[i] = Maths::rotatePlus90AroundGivenAxis(corner_vecs[i], axis);
    }
  }
};
