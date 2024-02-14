#ifndef SPACEUTILS
#define SPACEUTILS
#include <raylib.h>

Texture loadTexture( const char* ImgPath, int width, int height); //taking img path, width and height if you wish to resize
void clampi (float &cl, int min, int max);
int cloudX();

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


void UpdatePlayer (Player &player, bool &rotation, Rectangle floorRec, float delta);
void UpdatePlayerRec(Player &player);


#endif