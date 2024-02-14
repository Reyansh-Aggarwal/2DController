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
  Rectangle rect;
  float velY;
  float jumpPower;
  float groundY;
  float width;
  float height;
  bool onPlatform;
  bool canJump;

};


void UpdatePlayer (Player &player, bool &rotation, Rectangle floorRec, float delta){
  float grav = 9.8f;
  float jumpSpeed;
  //player.onPlatform = player.canJump;

  //movement
  if (IsKeyDown(KEY_SPACE) && player.canJump)
  {
    //player.pos.y-= 5 * delta;
    jumpSpeed = player.jumpPower;
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
      player.pos.x += 1;
      rotation = false;
  }

  //----------------------------------------------------------------
  //jumping
  //----------------------------------------------------------------
  if (!(player.canJump) && !(player.pos.y <= (player.groundY - 50)))
  {
    //std::cout << "vel++\n";
    player.velY -= jumpSpeed * delta;
    player.onPlatform = false;
  } else {
    jumpSpeed = 0.0f;
  }

  if (player.onPlatform)
  {
    player.groundY = player.pos.y;
  }
  //----------------------------------------------------------------
  //grav
  //----------------------------------------------------------------
  if (player.pos.y < (player.groundY - 50))
  {
    player.velY += grav * delta;
    //std::cout << "grounded\n";
  }
  

  //----------------------------------------------------------------
  //collisions
  //----------------------------------------------------------------
  if (CheckCollisionRecs(floorRec, player.rect)) //platform collision
  {
      player.onPlatform = true;
      
      if (!player.canJump){
      player.canJump = true;
      }

      if (!(player.velY == 0.0f))
      {
      player.velY = 0.0f;
      }
      //std::cout << "collide\n";
  }

  //----------------------------------------------------------------
  //math
  //----------------------------------------------------------------
  player.pos.y += player.velY;
  //
}

void UpdatePlayerRec(Player &player){
  player.rect.width = player.width; //incase we are transforming player size during game
  player.rect.height = player.height;
  player.rect.y = player.pos.y;
  player.rect.x = player.pos.x;
  //std::cout << "rect updated\n";
}
