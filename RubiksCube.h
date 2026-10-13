#pragma once
#include "Maths.h"
#include "Moves.h"
#include "cubies.h"
#include "raylib.h"
#include "rlgl.h"
#include <iostream>
#include <queue>
#include <vector>

enum FACE_ID { TOP = 0, RIGHT, FRONT, LEFT, BACK, DOWN };
enum CUBE_STATE { SOLVED, SOLVING, JUST_SOLVED, SCRAMBLING, SCRAMBLED };

struct RubiksCube {
  std::vector<Cubie> cubies;
  Vector3 pos = {4.0f, 2.0f, 2.0f};
  float len = 3.0f;
  Move::MOVE curr_move = Move::NO_MOVE;
  float angle = 0.0f;
  float step = 1000.0f; // angle per seceond
  inline static std::queue<Move::MOVE> moves_queue;
  Color ColorScheme[6] = {YELLOW, RED, GREEN, ORANGE, BLUE, WHITE};
  CUBE_STATE state = SOLVED;

  RubiksCube() {
    float l = len / 3;
    // middle layer
    cubies.push_back(Cubie(
        {pos.x - l, pos.y, pos.z - l},
        {BLACK, BLACK, BLACK, ColorScheme[LEFT], ColorScheme[BACK], BLACK}));
    cubies.push_back(
        Cubie({pos.x, pos.y, pos.z - l},
              {BLACK, BLACK, BLACK, BLACK, ColorScheme[BACK], BLACK}));
    cubies.push_back(Cubie(
        {pos.x + l, pos.y, pos.z - l},
        {BLACK, ColorScheme[RIGHT], BLACK, BLACK, ColorScheme[BACK], BLACK}));
    cubies.push_back(
        Cubie({pos.x - l, pos.y, pos.z},
              {BLACK, BLACK, BLACK, ColorScheme[LEFT], BLACK, BLACK}));
    cubies.push_back(Cubie({pos.x, pos.y, pos.z},
                           {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK}));
    cubies.push_back(
        Cubie({pos.x + l, pos.y, pos.z},
              {BLACK, ColorScheme[RIGHT], BLACK, BLACK, BLACK, BLACK}));
    cubies.push_back(Cubie(
        {pos.x - l, pos.y, pos.z + l},
        {BLACK, BLACK, ColorScheme[FRONT], ColorScheme[LEFT], BLACK, BLACK}));
    cubies.push_back(
        Cubie({pos.x, pos.y, pos.z + l},
              {BLACK, BLACK, ColorScheme[FRONT], BLACK, BLACK, BLACK}));
    cubies.push_back(Cubie(
        {pos.x + l, pos.y, pos.z + l},
        {BLACK, ColorScheme[RIGHT], ColorScheme[FRONT], BLACK, BLACK, BLACK}));

    // bottom layer
    cubies.push_back(Cubie({pos.x - l, pos.y - l, pos.z - l},
                           {BLACK, BLACK, BLACK, ColorScheme[LEFT],
                            ColorScheme[BACK], ColorScheme[DOWN]}));
    cubies.push_back(Cubie(
        {pos.x, pos.y - l, pos.z - l},
        {BLACK, BLACK, BLACK, BLACK, ColorScheme[BACK], ColorScheme[DOWN]}));
    cubies.push_back(Cubie({pos.x + l, pos.y - l, pos.z - l},
                           {BLACK, ColorScheme[RIGHT], BLACK, BLACK,
                            ColorScheme[BACK], ColorScheme[DOWN]}));
    cubies.push_back(Cubie(
        {pos.x - l, pos.y - l, pos.z},
        {BLACK, BLACK, BLACK, ColorScheme[LEFT], BLACK, ColorScheme[DOWN]}));
    cubies.push_back(
        Cubie({pos.x, pos.y - l, pos.z},
              {BLACK, BLACK, BLACK, BLACK, BLACK, ColorScheme[DOWN]}));
    cubies.push_back(Cubie(
        {pos.x + l, pos.y - l, pos.z},
        {BLACK, ColorScheme[RIGHT], BLACK, BLACK, BLACK, ColorScheme[DOWN]}));
    cubies.push_back(Cubie({pos.x - l, pos.y - l, pos.z + l},
                           {BLACK, BLACK, ColorScheme[FRONT], ColorScheme[LEFT],
                            BLACK, ColorScheme[DOWN]}));
    cubies.push_back(Cubie(
        {pos.x, pos.y - l, pos.z + l},
        {BLACK, BLACK, ColorScheme[FRONT], BLACK, BLACK, ColorScheme[DOWN]}));
    cubies.push_back(Cubie({pos.x + l, pos.y - l, pos.z + l},
                           {BLACK, ColorScheme[RIGHT], ColorScheme[FRONT],
                            BLACK, BLACK, ColorScheme[DOWN]}));

    // top layer
    cubies.push_back(Cubie({pos.x - l, pos.y + l, pos.z - l},
                           {ColorScheme[TOP], BLACK, BLACK, ColorScheme[LEFT],
                            ColorScheme[BACK], BLACK}));
    cubies.push_back(Cubie(
        {pos.x, pos.y + l, pos.z - l},
        {ColorScheme[TOP], BLACK, BLACK, BLACK, ColorScheme[BACK], BLACK}));
    cubies.push_back(Cubie({pos.x + l, pos.y + l, pos.z - l},
                           {ColorScheme[TOP], ColorScheme[RIGHT], BLACK, BLACK,
                            ColorScheme[BACK], BLACK}));
    cubies.push_back(Cubie(
        {pos.x - l, pos.y + l, pos.z},
        {ColorScheme[TOP], BLACK, BLACK, ColorScheme[LEFT], BLACK, BLACK}));
    cubies.push_back(
        Cubie({pos.x, pos.y + l, pos.z},
              {ColorScheme[TOP], BLACK, BLACK, BLACK, BLACK, BLACK}));
    cubies.push_back(Cubie(
        {pos.x + l, pos.y + l, pos.z},
        {ColorScheme[TOP], ColorScheme[RIGHT], BLACK, BLACK, BLACK, BLACK}));
    cubies.push_back(Cubie({pos.x - l, pos.y + l, pos.z + l},
                           {ColorScheme[TOP], BLACK, ColorScheme[FRONT],
                            ColorScheme[LEFT], BLACK, BLACK}));
    cubies.push_back(Cubie(
        {pos.x, pos.y + l, pos.z + l},
        {ColorScheme[TOP], BLACK, ColorScheme[FRONT], BLACK, BLACK, BLACK}));
    cubies.push_back(Cubie({pos.x + l, pos.y + l, pos.z + l},
                           {ColorScheme[TOP], ColorScheme[RIGHT],
                            ColorScheme[FRONT], BLACK, BLACK, BLACK}));
  }

  void update() {

    if (angle >= 90 ||
        curr_move == Move::NO_MOVE) { // first move is NO_MOVE so
                                      // remove it after valid move arrives
      angle = 0;
      // fix the stickers for angle >= 90 case
      // in that fixing function just early return if NO_MOVE
      // take curr_move as input, maybe swap positions and colors cyclically
      // then fix each cubie's stickers
      //
      //
      if (curr_move != Move::NO_MOVE)
        updatePositionAndOrientationOfCubies(curr_move);
      // get move from queue if queue not empty
      if (!moves_queue.empty()) {
        curr_move = moves_queue.front();
        moves_queue.pop();
      } else {
        curr_move = Move::NO_MOVE;
      }
    } else {
      angle += step * GetFrameTime();
    }
  }

  void draw() const {
    for (int i = 0; i < cubies.size(); i++) {
      if (cubies[i].fallsInFace(curr_move, pos)) {
        Vector3 axis = Move::getAxis(curr_move);
        // std::cout << axis.x << " " << axis.y << " " << axis.z << std::endl;
        rlPushMatrix();
        rlTranslatef(pos.x, pos.y, pos.z);
        rlRotatef(angle, axis.x, axis.y, axis.z);
        rlTranslatef(-pos.x, -pos.y, -pos.z);
        // std::cout << angle << std::endl;
        cubies[i].draw();
        rlPopMatrix();
      } else
        cubies[i].draw();
    }
  }

  void updatePositionAndOrientationOfCubies(Move::MOVE curr_move) {
    for (int i = 0; i < cubies.size(); i++)
      if (cubies[i].fallsInFace(curr_move, pos)) {
        cubies[i].updatePositionAndOrientation(curr_move, pos);
        // check if cubie in correct position
      }
  }

  bool isSolved() {
    Color color_of_face[20];
    std::vector<bool> first_of_face(20, true);
    for (auto &cube : cubies) {
      for (Move::MOVE move : {Move::U_PRIME, Move::F_PRIME, Move::R_PRIME,
                              Move::L_PRIME, Move::D_PRIME}) {
        if (cube.fallsInFace(move, pos)) {
          if (first_of_face[move]) {
            color_of_face[move] = cube.colorInTheDirection(move);
            first_of_face[move] = false;
          } else if (!ColorIsEqual(cube.colorInTheDirection(move),
                                   color_of_face[move]))
            return false;
        }
      }
    }
    return true;
  }

  void scramble(int scramble_len = 40) {
    for (int i = 0; i < scramble_len; i++) {
      curr_move = (Move::MOVE)GetRandomValue(1, 16);
      // updatePositionAndOrientationOfCubies(curr_move);
      moves_queue.push(curr_move);
    }
  }
};
