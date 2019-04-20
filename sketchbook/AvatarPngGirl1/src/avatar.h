#pragma once
#include <M5Stack.h>
#include "data/avatar_bg.jpg.h"
class Mouth
{
private:
  int x;
  int y;
  int minWidth;
  int maxWidth;
  int minHeight;
  int maxHeight;
  int lastX;
  int lastY;
  int lastW;
  int lastH;
  int offsetX;
  int offsetY;
  float openRatio;
  uint32_t insideColor;
  uint32_t outsideColor;
  uint32_t bgColor;
  void clear(void);
  void _draw(int x1, int y1, int x2, int y2);
public:
  // constructor
  Mouth();
  Mouth(int x, int y,
  int minWidth, int maxWidth,
  int minHeight, int maxHeight,
  uint32_t insideColor, uint32_t outsideColor, uint32_t bgColor);
  void setOpenRatio(float ratio);
  void open(int percent);
  void draw(float breath);
  void extendAction();
};

class Avatar
{
private:
  Mouth mouth;
  float breath;
  void drawLoop(void);
public:
  // constructor
  Avatar(void);

  void openMouth(int percent);
  void setMouthOpen(float f);
  void setEyeOpen(float f);
  void setBreath(float f);
  void setGaze(float vertical, float horizontal);
  void setExpression(void); // TODO
  void init(void);
  void draw(void);
  void extendAction(void);
};
