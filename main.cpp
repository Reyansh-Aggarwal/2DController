#include "raylib.h"
#include <iostream>
#include "utils.h"
#include <string>
//ok nigger
//dashing isnt working
int main() {		
	bool dashEnd = true;
	bool toDash = false;
  float startPos = 400 - 56;
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
  //Texture2D playerRightDash = loadTexture("assets/sprite_rightdash.png", player.width, player.height);
  //Texture2D playerLeftDash = loadTexture("assets/sprite_leftdash.png", player.width, player.height);
  Texture2D dashTrail = loadTexture("assets/dashTrail.png", 128, 64, imgPtr);

  //---------------------------------------------------------------
  //while loop
  //--------------------------------------------------------------
  while (!WindowShouldClose())
  {
	 float delta = GetFrameTime();

	 //dashEnd = Dash(player, startPos, toDash, delta);
	 UpdatePlayerRec(player);
	 UpdatePlayer(player, floorRec, dashEnd, toDash, delta);

	 camera.target = {player.pos.x, player.pos.y};
	 camera.offset = {490, 380};
	 //---------------------------------------------
	 //dashing
	 //---------------------------------------------
	 //if (frameCounter % 50 == 0){
 	 float dashLimit = 100 * player.dir;

 	 if (player.dir == 1)
 	 {
 		dashEnd = player.pos.x > startPos + dashLimit;
 	 } else if (player.dir == -1){
 	 	dashEnd = player.pos.x < startPos - dashLimit;
 	 }
	 if (!toDash)
	 {
	 	startPos = player.pos.x;
	 }

   if (toDash)
	 {
	  if (!dashEnd)
	  {
	    player.pos.x += 10 * player.dir * delta;
		}
	 }
	 if (dashEnd)
	 {
	 	toDash = false;
	 }
	//---------------------------------------------  
  //Drawing
  //---------------------------------------------
	 BeginDrawing(); 
		
	 BeginMode2D(camera);

	 ClearBackground(BLUE);
	 DrawRectangleRec(floorRec, GREEN);
	 //====
	 //drawing player & dash trail
	 //====
	 if (toDash && player.dir == -1)
	 {
		DrawTexture(dashTrail, player.pos.x + 48 ,player.pos.y, WHITE);
	 } 
	 else if (toDash && player.dir == 1)
	 {
		DrawTexture(dashTrail, player.pos.x - 100, player.pos.y, WHITE);
	 }

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
  UnloadTexture(dashTrail);
  CloseWindow();
  return 0;
}