#pragma once
#include "cubies.h"
#include "raylib.h"
#include "rlgl.h"
#include <vector>

enum FACE_ID { TOP = 0, RIGHT, FRONT, LEFT, BACK, DOWN };

struct RubiksCube {
  std::vector<Cubie> cubies;
  Vector3 pos = {0.0f, 0.0f, 0.0f};
  float len = 3.0f;

  Color ColorScheme[6] = {YELLOW, RED, GREEN, ORANGE, BLUE, WHITE};

  RubiksCube() {
    float l = len / 3;
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

    // top layer
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
  }

  void draw() const {
    for (int i = 0; i < cubies.size(); i++) {
      cubies[i].draw();
    }
  }
};
