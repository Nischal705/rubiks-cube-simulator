#pragma once
#include "raylib.h"

namespace Move {

enum MOVE {
  R,
  R_PRIME,
  L,
  L_PRIME,
  U,
  U_PRIME,
  D,
  D_PRIME,
  F,
  F_PRIME,
  B,
  B_PRIME
};

Vector3 getAxis(MOVE curr_move) {
  if (curr_move == R)
    return {-1, 0, 0};
  if (curr_move == R_PRIME)
    return {1, 0, 0};
  if (curr_move == L)
    return {1, 0, 0};
  if (curr_move == L_PRIME)
    return {-1, 0, 0};
  if (curr_move == U)
    return {0, -1, 0};
  if (curr_move == U_PRIME)
    return {0, 1, 0};
  if (curr_move == D)
    return {0, 1, 0};
  if (curr_move == D_PRIME)
    return {0, -1, 0};
  if (curr_move == F)
    return {0, 0, -1};
  if (curr_move == F_PRIME)
    return {0, 0, 1};
  if (curr_move == B)
    return {0, 0, 1};
  if (curr_move == B_PRIME)
    return {0, 0, -1};
  return {0, 0, 0};
}

} // namespace Move
