#include "InputHandler.h"
#include "RubiksCube.h"
#include "cubies.h"
#include "raylib.h"
#include <rlgl.h>
int main() {
  const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 640;
  int FPS = 60;

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Cubes");

  // camera settings
  Camera3D camera = {0};
  camera.position = {1.0f, 3.0f, 4.0f};
  camera.target = {0.0f, 0.0f, 0.0f};
  camera.up = {0.0f, 1.0f, 0.0f};
  // camera.fovy = 85.0f;
  camera.fovy = 10.0f;
  camera.projection = CAMERA_ORTHOGRAPHIC;

  SetTargetFPS(FPS);
  // DisableCursor();

  RubiksCube rubiksCube;

  while (!WindowShouldClose()) {

    InputHandler::manageMoves();

    // UpdateCamera(&camera, CAMERA_FREE);
    rubiksCube.update();

    if (IsKeyPressed(KEY_Z))
      camera.target = {0.0f, 0.0f, 0.0f};

    BeginDrawing();
    // ClearBackground({105, 187, 236});
    ClearBackground({214, 220, 148});
    BeginMode3D(camera);

    rubiksCube.draw();

    // DrawGrid(20, 1.0f);

    EndMode3D();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
