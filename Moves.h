#pragma once
#include "raylib.h"
#include <unordered_map>

namespace Move {

enum MOVE {
  NO_MOVE,
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
  B_PRIME,
  // including rotations too
  Y,
  Y_PRIME,
  X,
  X_PRIME
};

std::unordered_map<int, Move::MOVE> mapUserKeysToMoves = {
    {KEY_I, Move::R},         {KEY_K, Move::R_PRIME}, {KEY_D, Move::L},
    {KEY_E, Move::L_PRIME},   {KEY_J, Move::U},       {KEY_F, Move::U_PRIME},
    {KEY_H, Move::F},         {KEY_G, Move::F_PRIME}, {KEY_S, Move::D},
    {KEY_L, Move::D_PRIME},   {KEY_W, Move::B},       {KEY_O, Move::B_PRIME},
    {KEY_SEMICOLON, Move::Y}, {KEY_A, Move::Y_PRIME}, {KEY_Y, Move::X},
    {KEY_T, Move::X},         {KEY_N, Move::X_PRIME}};

bool isRotation(MOVE move) {
  return (move == Y || move == Y_PRIME || move == X || move == X_PRIME);
}

Vector3 getAxis(MOVE curr_move) {
  if (curr_move == R || curr_move == X)
    return {-1, 0, 0};
  if (curr_move == R_PRIME || curr_move == X_PRIME)
    return {1, 0, 0};
  if (curr_move == L)
    return {1, 0, 0};
  if (curr_move == L_PRIME)
    return {-1, 0, 0};
  if (curr_move == U || curr_move == Y)
    return {0, -1, 0};
  if (curr_move == U_PRIME || curr_move == Y_PRIME)
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
