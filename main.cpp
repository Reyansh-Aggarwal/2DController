#include "raylib.h"
#include <iostream>
#include "utils.h"
#include <string>

int main() {		
  int frameCounter = 0;
  Image* imgPtr = nullptr;
  Player player = {0};
  player.pos.y = 400 - 56;
  player.width = 64;
  player.height = 64;
  player.onPlatform = true;
  player.jumpPower = 500.0f;
  player.dashDist = 100.0f;
  player.status = "neutral"; //1 = left, 2 = right, 0 = front
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

  Texture2D playerLeft = loadTexture("assets/sprite_left.png", player.width, player.height, imgPtr);
  Texture2D playerRight = loadTexture("assets/sprite_right.png", player.width, player.height, imgPtr);
  Texture2D playerPassive = loadTexture("assets/sprite_passive.png", player.width, player.height, imgPtr);


  //---------------------------------------------------------------
  //while loop
  //--------------------------------------------------------------
  while (!WindowShouldClose())
  {
	 float delta = GetFrameTime();

	 UpdatePlayerRec(player);
	 UpdatePlayer(player, floorRec, delta);

	 camera.target = {player.pos.x, player.pos.y};
	 camera.offset = {490, 380};

  //---------------------------------------------  
  //Drawing
  //---------------------------------------------
	 BeginDrawing(); 
		
	 BeginMode2D(camera);

	 ClearBackground(BLUE);
	 DrawRectangleRec(floorRec, GREEN);
	 //====
	 //drawing player
	 //====

	 if (player.status == "turn" && player.dir == -1)
	 {
		DrawTextureV(playerLeft, player.pos, WHITE); 
	 }
	 else if (player.status == "turn" && player.dir == 1)
	 {
		DrawTextureV(playerRight, player.pos, WHITE); 
	 } 
	 else if (player.status == "neutral")
	 {
		DrawTextureV(playerPassive, player.pos, WHITE);
	 }
	 

	 EndMode2D();

	 //gui
	 DrawText(TextFormat("Y: %f", player.pos.y), 100, 20, 20, BLACK);
	 DrawText(TextFormat("X: %f", player.pos.x), 100, 40, 20, BLACK);

	 EndDrawing();  
	 frameCounter++;
  }

  //UnloadTexture (sky);
  UnloadTexture(playerLeft);
  UnloadTexture(playerRight);
  UnloadTexture(playerPassive);
  CloseWindow();
  return 0;
}