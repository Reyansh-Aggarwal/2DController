#include "utils.h"
#include <string>

Texture loadTexture( const char* ImgPath, int width, int height, Image* imgPtr){ 

  Image img = LoadImage(ImgPath);

  if (!width == 0 && !height == 0){
  imgPtr= &img;
  ImageResizeNN(imgPtr, width, height);
  }

  Texture texture = LoadTextureFromImage(img);
  return texture;
}


void clampi (float &cl, int min, int max){
  if (cl > max){
    cl = max;
  } 
  else if(cl < min){
    cl = min;
  }
}


int cloudX (){
  int posx =rand() % (856 + 1 - 0) + 0;
  return posx;
}


void UpdatePlayer (Player &player, Rectangle floorRec, float delta){
  float grav = 9.8f;

  //----------------------------------------------------------------
  //INPUT & MOVEMENT
  //----------------------------------------------------------------
   
    if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_W))){
      player.status = "jump";
    }

    if (IsKeyDown(KEY_A)|| IsKeyDown(KEY_LEFT)){
      player.dir = -1;
      player.status = "turn";
    }
    else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        player.dir = 1;
        player.status = "turn";
    } 
    if (!(IsKeyDown(KEY_D) || IsKeyDown(KEY_A))) {
      player.status = "neutral";
      player.dir = 0;
    } 
    else {
      player.status = "turn";
    }

    player.pos.x += 100 * delta * player.dir;

  //----------------------------------------------------------------
  //jumping
  //----------------------------------------------------------------



  //----------------------------------------------------------------
  //grav
  //----------------------------------------------------------------

  if (!(player.onPlatform)){
    player.velY += grav*delta;
  }
  
  //----------------------------------------------------------------
  //collisions
  //----------------------------------------------------------------
  if (CheckCollisionRecs(floorRec, player.rect)) { // platform collision 
    if (!(player.pos.y == floorRec.y)){
      player.pos.y = floorRec.y - player.height;
    }
    player.onPlatform = true;
    player.groundY = player.pos.y;
    if (!(player.velY == 0.0f)){
      player.velY = 0.0f;
    }
  }
  else  {
    player.onPlatform = false;
  }

  //----------------------------------------------------------------
  //math
  //----------------------------------------------------------------
  player.pos.y += (int)player.velY;
  //
}

void UpdatePlayerRec(Player &player){

  player.rect.width = player.width; //incase we are transforming player size during game
  player.rect.height = player.height;
  player.rect.y = player.pos.y;
  player.rect.x = player.pos.x;
  //std::cout << "rect updated\n";
}

