#pragma once
#include <M5Stack.h>
#include "data/eye_center_open.png.h"
#include "data/eye_center_half.png.h"
#include "data/eye_close.png.h"
#include "data/eye_left.png.h"
#include "data/eye_right.png.h"

class Eye
{
private:
  int x;
  int y;
  int width;
  int height;
  int lastX;
  int lasyY;
public:
  // constructor
  Eye();
  Eye(int x, int y, int width, int height);
  void close();
  void blink();
  void center();
  void left();
  void right();
};
