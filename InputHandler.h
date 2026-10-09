#pragma once
#include "Moves.h"
#include "RubiksCube.h"
#include "raylib.h"
#include <unordered_map>

struct InputHandler {
  inline static std::unordered_map<int, Move::MOVE> mapUserKeysToMoves = {
      {KEY_I, Move::R},         {KEY_K, Move::R_PRIME}, {KEY_D, Move::L},
      {KEY_E, Move::L_PRIME},   {KEY_J, Move::U},       {KEY_F, Move::U_PRIME},
      {KEY_H, Move::F},         {KEY_G, Move::F_PRIME}, {KEY_S, Move::D},
      {KEY_L, Move::D_PRIME},   {KEY_W, Move::B},       {KEY_O, Move::B_PRIME},
      {KEY_SEMICOLON, Move::Y}, {KEY_A, Move::Y_PRIME}, {KEY_Y, Move::X},
      {KEY_T, Move::X},         {KEY_N, Move::X_PRIME}};

  static void manageMoves() {
    int key = GetKeyPressed();
    if (mapUserKeysToMoves.find(key) != mapUserKeysToMoves.end())
      RubiksCube::moves_queue.push(mapUserKeysToMoves[key]);
  }
};
