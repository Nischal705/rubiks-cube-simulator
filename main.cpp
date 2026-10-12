#include "InputHandler.h"
#include "RubiksCube.h"
#include "Timer.h"
#include "cubies.h"
#include "raylib.h"
#include <rlgl.h>
int main() {
  const int SCREEN_WIDTH = 1820, SCREEN_HEIGHT = 980;
  int FPS = 60;

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Cubes");

  // font
  // Font fontStyle =
  // LoadFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
  RubiksCube rubiksCube;

  // camera settings
  Camera3D camera = {0};
  camera.position = {1.0f, 3.0f, 5.0f};
  camera.target = {0.0f, 0.0f, 0.0f};
  camera.up = {0.0f, 1.0f, 0.0f};
  // camera.fovy = 85.0f;
  camera.fovy = 10.0f;
  camera.projection = CAMERA_ORTHOGRAPHIC;

  SetTargetFPS(FPS);
  // DisableCursor();

  // Timer
  Timer timer({GetScreenWidth() * 0.2f, GetScreenHeight() * 0.5f}, 140, BLACK);

  while (!WindowShouldClose()) {

    InputHandler::manageProgramFlow(rubiksCube, timer);

    timer.display();
    // UpdateCamera(&camera, CAMERA_FREE);
    // rubiksCube.update();

    // if (IsKeyPressed(KEY_Z))
    //   camera.target = {0.0f, 0.0f, 0.0f};

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
