#include "raylib.h"
#include <iostream>
#include "utils.h"
#include <string>
//ok nigger
//dashing is incomplete, dont mess with that shit rn
int main() {		
	bool dashEnd = false;
	bool toDash = false;
  float startPos = 400 - 56;
  int frameCounter = 0;

  Player player = {0};
  player.pos.y = 400 - 56;
  player.width = 64;
  player.height = 64;
  player.onPlatform = true;
  player.jumpPower = 350.0f;
  player.dashDist = 100.0f;
  player.canJump = true;
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

  Texture2D playerLeft = loadTexture("assets/sprite_left.png", player.width, player.height);
  Texture2D playerRight = loadTexture("assets/sprite_right.png", player.width, player.height);
  Texture2D playerPassive = loadTexture("assets/sprite_passive.png", player.width, player.height);
  Texture2D playerRightDash = loadTexture("assets/sprite_rightdash.png", player.width, player.height);
  Texture2D playerLeftDash = loadTexture("assets/sprite_leftdash.png", player.width, player.height);


  while (!WindowShouldClose()){
	 float delta = GetFrameTime();
	 dashEnd = Dash(player, startPos, toDash, delta);
	 UpdatePlayerRec(player);
	 UpdatePlayer(player, floorRec, dashEnd, toDash, delta);

	 camera.target = {player.pos.x, player.pos.y};
	 camera.offset = {490, 380};

	 BeginDrawing(); 
		
	 BeginMode2D(camera);

	 ClearBackground(BLUE);
	 DrawRectangleRec(floorRec, GREEN);
	 //checking orientation of player
	 if (player.status == "turn" && player.dir == -1){
		DrawTextureV(playerLeft, player.pos, WHITE); 
	 }
	 else if (player.status == "turn" && player.dir == 1){
		DrawTextureV(playerRight, player.pos, WHITE); 
	 } else if (player.status == "neutral"){
		DrawTextureV(playerPassive, player.pos, WHITE);
	 } else if (player.status == "dash" && player.dir == -1){
		DrawTextureV(playerLeftDash, player.pos, WHITE);
	 } else if (player.status == "dash" && player.dir == 1){
		DrawTextureV(playerRightDash, player.pos, WHITE);
	 }

	 EndMode2D();

	 //gui
	 DrawText(TextFormat("Y: %f", player.pos.y), 100, 20, 20, BLACK);

	 EndDrawing();  
	 frameCounter++;
  }

  //UnloadTexture (sky);
  UnloadTexture(playerLeft);
  UnloadTexture(playerRight);
  UnloadTexture(playerPassive);
  UnloadTexture(playerLeftDash);
  UnloadTexture(playerRightDash);
  CloseWindow();
  return 0;
}
