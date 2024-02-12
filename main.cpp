#include "raylib.h"
#include <iostream>
#include "utils.h"

//TODO: FIX JUMPING
int main() {   


	Player player = {0};
	player.pos.y = 400 - 56;
	player.groundY = player.pos.y;
	bool rotation = true; //true = left
	Vector2 screen;
	screen.x = 960;
	screen.y = 540;

	//rectangle
	Rectangle floorRec;
	floorRec.x = -100;
	floorRec.y = 400;
	floorRec.width = 1500;
	floorRec.height = 100;
	//camera
	Camera2D camera;
	camera.target = (Vector2){player.pos.x, player.pos.y+ 10};
	camera.offset = (Vector2){0,0};
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;
	//

	InitWindow(screen.x, screen.y, "2D controller" );
	SetTargetFPS(144);
	Texture2D sky = loadTexture("/assets/sky.jpg", 626,540);
	Texture2D playerLeft = loadTexture("assets/spriteLeft.png", 56, 56);
	Texture2D playerRight = loadTexture("assets/spriteRight.png", 56, 56);

	while (!WindowShouldClose()){

		
		BeginDrawing(); 
		
		BeginMode2D(camera);
		ClearBackground(WHITE);
		DrawText("lmao", 100, 200, 20, WHITE);

		DrawRectangleRec(floorRec, BLACK);
		//checking orientation of player
		if (rotation){
			DrawTextureV(playerLeft, player.pos, WHITE); 
		}
		else {
			DrawTextureV(playerRight, player.pos, WHITE); 
		}

		UpdatePlayer(player, rotation, floorRec,GetFrameTime());
		//std::cout << "player.y = " << player.pos.y << std::endl;  //debugging
		
		//camera settings
		camera.target = {player.pos.x, player.pos.y};
		camera.offset = {490, 380};
		//
		EndMode2D();

		//gui
		DrawText(TextFormat("Y: %f", player.pos.y), 100,20,20,  BLACK);

		//
		EndDrawing();  
	}

	//unloading all textures
	UnloadTexture (sky);
	UnloadTexture(playerLeft);
	UnloadTexture(playerRight);

	CloseWindow();
	return 0;
}
