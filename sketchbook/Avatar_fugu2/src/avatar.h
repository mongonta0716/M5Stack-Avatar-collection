#pragma once
#include <M5Stack.h>


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
  uint32_t primaryColor;
  uint32_t secondaryColor;
  void clear(void);
  void _draw(int x1, int y1, int x2, int y2);
public:
  // constructor
  Mouth();
  Mouth(int x, int y,
  int minWidth, int maxWidth,
  int minHeight, int maxHeight,
  uint32_t primaryColor, uint32_t secondaryColor);
  void setOpenRatio(float ratio);
  void open(int percent);
  void draw(float breath);
  void spitWater();
};

class Eye
{
private:
  int x;
  int y;
  int r;
  int offsetX;
  int offsetY;
  int lastX;
  int lastY;
  int lastR;
  float openRatio;
  uint32_t primaryColor;
  uint32_t secondaryColor;
  void clear(void);
  void drawCircle(int x, int y, int r);
  void drawRect(int x, int y, int w, int h);
public:
  // constructor
  Eye();
  Eye(int x, int y, int r, uint32_t primaryColor, uint32_t secondaryColor);
  void setOpenRatio(float ratio);
  void setOffset(int offsetX, int offsetY);
  void open(boolean isOpen);
  void draw(float breath);
};

class Avatar
{
private:
  Mouth mouth;
  Eye eyeR;
  Eye eyeL;
  Eye eyeballR;
  Eye eyeballL;
  float breath;
  boolean isEyeOpen;
  float EyeOpenRatio;
  void drawLoop(void);
public:
  // constructor
  Avatar(void);

  void openMouth(int percent);
  void openEye(boolean isOpen);
  void setMouthOpen(float f);
  void setEyeOpen(float f);
  void setBreath(float f);
  void setGaze(float vertical, float horizontal);
  void setExpression(void); // TODO
  void init(void);
  void draw(void);
  void extendAction(void);
};
