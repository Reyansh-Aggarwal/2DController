#ifndef SPACEUTILS
#define SPACEUTILS
#include <raylib.h>

Texture loadTexture( const char* ImgPath, int width, int height); //taking img path, width and height if you wish to resize
void clampi (float &cl, int min, int max);
int cloudX();

class Player {
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

void UpdatePlayer (Player &player, bool &rotation, Rectangle floorRec, float delta);

#endif