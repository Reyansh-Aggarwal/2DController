#include <raylib.h>
#include <cstdlib>
#include <iostream>
Texture loadTexture( const char* ImgPath, int width, int height){ 

  Image img = LoadImage(ImgPath);

  if (!width == 0 && !height == 0){
  Image* point_img = &img;
  ImageResizeNN(point_img, width, height);
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

class Player { //not needed here but to keep a healthy format
public:
  Vector2 pos;
  Vector2 bottomLeft;
  Vector2 topRight;
  float velY;
  float jumpPower;
  float groundY;
  bool onFloor;
  bool collRight;
  bool collLeft;
  bool canJump;

};

void UpdatePlayer (Player &player, bool &rotation, Rectangle floorRec, float delta){
  float grav = 25.0f;
  float jumpSpeed = 20.0f;

  //movement
  if (IsKeyPressed(KEY_SPACE) && player.canJump)
  {
    //player.pos.y-= 5 * delta;
    player.jumpPower = jumpSpeed;
    player.canJump = false;
    std::cout << "Jumped!\n";
  }
  if (IsKeyDown(KEY_A)|| IsKeyDown(KEY_LEFT))
  {
    player.pos.x -= 1;
    rotation = true;
  }

  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
  {
    if(!player.collRight){
      player.pos.x += 1;
      rotation = false;
    }
  }

  
  //----------------------------------------------------------------
  //jumping
  //----------------------------------------------------------------
  if (!player.canJump)
  {
    //std::cout << "vel++\n";
    player.velY -= player.jumpPower * delta;
    player.onFloor = false;

  }
  if (player.onFloor)
  {
    player.groundY = player.pos.y;
  }
  //----------------------------------------------------------------
  //grav
  //----------------------------------------------------------------
  if (!player.onFloor)
  {
    player.velY += grav * delta;
    player.jumpPower = 0;
    std::cout << "grounded\n";
    player.canJump = true;
  }
  
  //----------------------------------------------------------------
  //collisions
  //----------------------------------------------------------------
  if (player.bottomLeft.y == floorRec.y)
  {
      player.onFloor = true;
      if (!(player.velY == 0.0f))
      {
      player.velY = 0.0f;
      }
      if (!(player.jumpPower == 0.0f))
      {
        player.jumpPower = 0.0f;
      }
      std::cout << "collide\n";
  }

  if (player.topRight.x == floorRec.x){
        player.collRight = true;
  } 
  else 
  {
    player.collRight = false;
  }

  //

  //math
  player.bottomLeft.x = player.pos.x;
  player.bottomLeft.y = player.pos.y + 64;
  player.topRight.x = player.pos.x + 64;
  player.topRight.y = player.pos.y;
  player.pos.y += player.velY;
  //
}