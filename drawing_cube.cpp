#include "RubiksCube.h"
#include "cubies.h"
#include "raylib.h"
#include <rlgl.h>
int main() {
  const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 640;
  int FPS = 60;

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Cubes");

  Camera3D camera = {0};
  camera.position = {0.0f, 0.0f, 8.0f};
  camera.target = {0.0f, 0.0f, 0.0f};
  camera.up = {0.0f, 1.0f, 0.0f};
  camera.fovy = 85.0f;
  camera.projection = CAMERA_PERSPECTIVE;

  Vector3 position = {0.0f, 0.0f, 0.0f};

  SetTargetFPS(FPS);
  DisableCursor();

  // cubie
  // Cubie cubie1;
  // cubie1.pos = {1, 1, 1};
  // cubie1.colors = {BLUE, RED, YELLOW, BLACK, BLACK, BLACK};

  RubiksCube rubiksCube;

  while (!WindowShouldClose()) {

    UpdateCamera(&camera, CAMERA_FREE);

    if (IsKeyPressed(KEY_Z))
      camera.target = {0.0f, 0.0f, 0.0f};

    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(camera);

    rubiksCube.draw();

    DrawGrid(20, 1.0f);

    EndMode3D();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
