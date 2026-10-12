#pragma once
#include "Moves.h"
#include "RubiksCube.h"
#include "Timer.h"
#include "raylib.h"
#include <unordered_map>

struct InputHandler {

  static void manageMoves(int key) {
    if (Move::mapUserKeysToMoves.find(key) != Move::mapUserKeysToMoves.end())
      RubiksCube::moves_queue.push(Move::mapUserKeysToMoves[key]);
  }

  /*
   *
   * features it should have :
   *
   *  initially solved
   *  when space pressed
   *   scramble
   *   when a valid move entered
   *   timer start
   *   when solved
   *   timer stop
   *   not reseted
   *
   *   when space pressed
   *   timer reset to 0
   *   and scramble
   *
   *
   *   RubiksCube States:
   *     SOLVED : solved
   *     SOLVING : currently solving by user
   *     SCRAMBLED: scrambled and waiting for user to start
   *
   *  pseudo-code:
   *   get key pressed
   *
   *   if state = solving :
   *     if key == valid key
   *       perform that move
   *     if solved :
   *        state = solved
   *
   *   if state == solved :
   *     if key == space
   *      scramble
   *      then state = scrambled
   *
   *   if state == scrambled :
   *     if key == rotational moves
   *       perform that move
   *     if key == non rotational moves
   *       state = solving
   *       perform that move
   *     if ... features ...
   *       ...
   *
   */
  static void manageProgramFlow(RubiksCube &Cube, Timer &timer) {
    int key = GetKeyPressed();

    switch (Cube.state) {
    case SOLVING:
      if (Move::mapUserKeysToMoves.find(key) !=
          Move::mapUserKeysToMoves.end()) {
        RubiksCube::moves_queue.push(Move::mapUserKeysToMoves[key]);
      }
      Cube.update();
      timer.update();
      if (Cube.isSolved()) {
        Cube.state = SOLVED;
        timer.stop();
      }
      break;
    case SOLVED:
      if (key == KEY_SPACE) {
        Cube.scramble(); // fills the scramble in moves_queue
        Cube.state = SCRAMBLING;
        timer.reset();
      }
      break;
    case SCRAMBLING:
      // no input taken during scramblibg
      if (Cube.curr_move != Move::NO_MOVE) {
        Cube.update();
      } else {
        Cube.state = SCRAMBLED;
      }
      break;
    case SCRAMBLED:
      if (Move::mapUserKeysToMoves.find(key) !=
          Move::mapUserKeysToMoves.end()) {
        Move::MOVE move = Move::mapUserKeysToMoves[key];
        RubiksCube::moves_queue.push(move);
      }
      Cube.update();
      if (!Move::isRotation(Cube.curr_move) &&
          Cube.curr_move != Move::NO_MOVE) {
        Cube.state = SOLVING;
        timer.start();
      }
      break;
    }
  }
};
