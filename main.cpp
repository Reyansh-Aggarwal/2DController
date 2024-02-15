#include "raylib.h"
#include <iostream>
#include "utils.h"

// can jump twice you stupid
int main() {		
  Player player = {0};
  player.pos.y = 400 - 56;
  player.width = 56;
  player.height = 56;
  player.onPlatform = true;
  player.jumpPower = 350.0f;
  player.dashDist = 50.0f;
  player.canJump = true;
  bool rotation = true; //true = left

  Vector2 screen;
  screen.x = 960;
  screen.y = 540;

  Rectangle floorRec;
  floorRec.x = -100;
  floorRec.y = 400;
  floorRec.width = 1500;
  floorRec.height = 100;
	
  Camera2D camera;
  camera.target = (Vector2){player.pos.x, player.pos.y+ 10};
  camera.offset = (Vector2){0,0};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;
	
  InitWindow(screen.x, screen.y, "2D controller" );
  SetTargetFPS(144);

  Texture2D playerLeft = loadTexture("assets/spriteLeft.png", player.width, player.height);
  Texture2D playerRight = loadTexture("assets/spriteRight.png", player.width, player.height);


  while (!WindowShouldClose()){

    UpdatePlayerRec(player);
    UpdatePlayer(player, rotation, floorRec,GetFrameTime());

    camera.target = {player.pos.x, player.pos.y};
    camera.offset = {490, 380};

    BeginDrawing(); 
		
    BeginMode2D(camera);

    ClearBackground(WHITE);
    DrawRectangleRec(floorRec, BLACK);
    //checking orientation of player
    if (rotation){
      DrawTextureV(playerLeft, player.pos, WHITE); 
    }
    else {
      DrawTextureV(playerRight, player.pos, WHITE); 
    }

    EndMode2D();

    //gui
    DrawText(TextFormat("Y: %f", player.pos.y), 100, 20, 20, BLACK);

    EndDrawing();  
  }

  //UnloadTexture (sky);
  UnloadTexture(playerLeft);
  UnloadTexture(playerRight);

  CloseWindow();
  return 0;
}
