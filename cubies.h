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
  inline static int pointsOfFaces[6][4] = {{0, 1, 2, 3}, {0, 4, 7, 1},
                                           {3, 5, 4, 0}, {3, 2, 6, 5},
                                           {1, 7, 6, 2}, {4, 5, 6, 7}};

  Cubie() { colors.assign(6, BLACK); }
  Cubie(Vector3 pos, std::vector<Color> colors) {
    this->pos = pos;
    this->colors = colors;
  }

  void draw() const {
    DrawCube(pos, innerCubeLen, innerCubeLen, innerCubeLen, BLACK);

    rlBegin(RL_QUADS);
    for (int faces = 0; faces < 6; faces++) {
      // top face 0
      rlColor4ub(colors[faces].r, colors[faces].g, colors[faces].b, 255);
      for (int corner_idx : pointsOfFaces[faces])
        rlVertex3f(pos.x + (corner_vecs[corner_idx].x * padding),
                   pos.y + corner_vecs[corner_idx].y * padding,
                   pos.z + (corner_vecs[corner_idx].z * padding));
    }
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
