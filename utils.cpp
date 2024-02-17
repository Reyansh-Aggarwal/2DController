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

// class Player { //not needed here but to keep a healthy format
// public:
//   Vector2 pos;
//   Rectangle rect;
//   float velY;
//   float jumpPower;
//   float dashDist;
//   float groundY;
//   float width;
//   float height;
//   bool onPlatform;
//   bool canJump;
// };

void UpdatePlayer (Player &player, Rectangle floorRec, bool &dashEnd, bool &toDash, float delta){
  float grav = 9.8f;
  float jumpSpeed;
  //stoDash = false;
  //----------------------------------------------------------------
  //INPUT & MOVEMENT
  //----------------------------------------------------------------
  if (dashEnd){
    if (IsKeyPressed(KEY_LEFT_SHIFT)){ //dashing
        //player.status = "dash";

      if (player.status == "left"){
        player.dir = -1;
      } 
      else if(player.status == "right") 
      {
        player.dir = 1;
      }
      toDash = true;
      //player.pos.x += player.dashDist * player.dir;
      } 
    if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP))){
      //player.pos.y-= 5 * delta;
      player.groundY = player.pos.y;
      jumpSpeed = player.jumpPower;
      player.toJump = true;
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
  }
  if (dashEnd){
    toDash = false;
  }
  //----------------------------------------------------------------
  //jumping
  //----------------------------------------------------------------
  if (player.toJump){
    //std::cout << "vel++\n";
    player.velY -= jumpSpeed * delta;

  }
  if (player.pos.y < player.groundY - 50){
    player.toJump = false;
  }
  if (player.onPlatform){
    player.groundY = player.pos.y;
  }
  //----------------------------------------------------------------
  //grav
  //----------------------------------------------------------------
  // if (player.pos.y < (player.groundY - 50))
  // {
  //   player.velY += grav * delta;
  // }

  /*if (player.pos.y < (player.groundY - 50) && player.onPlatform || player.canJump){
    player.velY += grav * delta;
    player.onPlatform = true;
  }*/

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

/*bool Dash(Player &player, float &startPos, bool &toDash, float delta){  // not
  //make dashing look better
  float dashLimit = 100 * player.dir;
  if (toDash)
  {
    if (!(player.pos.y == startPos + dashLimit))
    {
      std::cout << "dash!\n";
      player.pos.y += 100 * player.dir;
      return false;
    } 
    else 
    {
      return true;
    }
  } else {
    return false;
  }
}*/