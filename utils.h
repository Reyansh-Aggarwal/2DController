#ifndef SPACEUTILS
#define SPACEUTILS
#include <raylib.h>
#include <iostream>
#include <cstdlib>
#include <string>
Texture loadTexture( const char* ImgPath, int width, int height, Image* imgPtr); //taking img path, width and height if you wish to resize
void clampi (float &cl, int min, int max);
int cloudX();

class Player { 
public:
  Vector2 pos;
  Rectangle rect;
  float velY;
  float jumpPower;
  float dashDist; 
  float groundY;
  float width;
  float height;
  bool onPlatform;
  bool toJump;  
  int dir; //direction
  std::string status;
};


void UpdatePlayer (Player &player,Rectangle floorRec, float delta);
void UpdatePlayerRec(Player &player);
bool Dash (Player &player, float &startPos, bool &toDash, float delta);

#endif
