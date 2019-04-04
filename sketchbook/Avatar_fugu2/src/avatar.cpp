#include "avatar.h"

// Mouth
Mouth::Mouth(void)
{

}
Mouth::Mouth(int x, int y, int minWidth, int maxWidth, int minHeight, int maxHeight, uint32_t primaryColor, uint32_t secondaryColor)
{
  // TODO: validation
  this->x = x;
  this->y = y;
  this->minWidth = minWidth;
  this->maxWidth = maxWidth;
  this->minHeight = minHeight;
  this->maxHeight = maxHeight;
  this->primaryColor = primaryColor;
  this->secondaryColor = secondaryColor;
  this->openRatio = 0;
  this->lastX = 0;
  this->lastY = 0;
  this->lastW = 0;
  this->lastH = 0;
  this->offsetX = 0;
  this->offsetY = 5;
}
void Mouth::clear()
{
//  M5.Lcd.fillRect(lastX, lastY, lastW, lastH, secondaryColor);
  M5.Lcd.fillEllipse(lastX+lastW/2+offsetX, lastY+lastH/2+offsetY, lastW/2, lastH/2, TFT_LIGHTGREY);
}
void Mouth::_draw(int x, int y, int w, int h)
{
  if (lastX == x && lastY == y && lastW == w && lastH == h) return;
  clear();
//  M5.Lcd.fillRect(x, y, w, h, primaryColor);
  M5.Lcd.fillEllipse(160, 155, 50, 45, TFT_LIGHTGREY);
  M5.Lcd.fillEllipse(x+w/2+offsetX, y+h/2+offsetY, w/2, h/2, RED);
  M5.Lcd.drawEllipse(x+w/2+offsetX, y+h/2+offsetY, w/2, h/2, TFT_LIGHTGREY);
  if(h > 3) {
    M5.Lcd.drawEllipse(x+w/2+offsetX, y+h/2+offsetY, w/2-1, h/2-1, TFT_LIGHTGREY);
  }
  lastX = x + offsetX;
  lastY = y + offsetY;
  lastW = w;
  lastH = h;
}
void Mouth::setOpenRatio(float ratio)
{
  openRatio = ratio;
}
/**
 * @deprecated
 */
void Mouth::open(int percent)
{
  float f = percent / 100.0;
  setOpenRatio(f);
  draw(0.0);
}
void Mouth::draw(float breath /* FIXME: wrap it by context */)
{
  breath = min(1.0, breath);
  int h = minHeight + (maxHeight - minHeight) * openRatio;
  int w = minWidth + (maxWidth - minWidth) * (1 - openRatio);
  int x = this->x - w / 2;
  int y = this->y - h / 2 + breath * 2;
  _draw(x, y, w, h);
}

// Eye
Eye::Eye(void)
{
  
}
Eye::Eye(int x, int y, int r, uint32_t primaryColor, uint32_t secondaryColor)
{
  this->openRatio = 1;
  this->x = x;
  this->y = y;
  this->r = r;
  this->lastX = 0;
  this->lastY = 0;
  this->lastR = 0;
  this->offsetX = 0;
  this->offsetY = 0;
  this->primaryColor = primaryColor;
  this->secondaryColor = secondaryColor;
}
void Eye::clear()
{
  M5.Lcd.fillCircle(lastX , lastY ,
                  lastR / 2 + 10 , secondaryColor);
}
void Eye::drawCircle(int x, int y, int r)
{
//  if (lastX == x && lastY == y && lastR == r) return;
  clear();
  M5.Lcd.fillCircle(x, y, r, primaryColor);
  // TODO: Sleepy face
  lastX = x;
  lastY = y;
  lastR = r;
}
void Eye::drawRect(int x, int y, int w, int h)
{
  clear();
  M5.Lcd.fillRect(x, y, w , h , primaryColor);
  lastX = x + w / 2;
  lastY = y + h / 2;
  lastR = w; // TODO: ellipse
}
void Eye::draw(float breath /* FIXME: wrap it by context */)
{
  breath = min(1.0, breath);
  if (openRatio > 0)
  {
    drawCircle(x + offsetX, y + offsetY + breath * 3, r);
  }
  else
  {
    int x1 = x - r + offsetX;
    int y1 = y - 2 + offsetY + breath * 1;
    int w = r * 2;
    int h = 4;
    drawRect(x1, y1, w, h);
  }

}
void Eye::setOpenRatio(float ratio)
{
  this->openRatio = ratio;
}
void Eye::setOffset(int offsetX, int offsetY)
{
  this->offsetX = offsetX;
  this->offsetY = offsetY;
}
/**
 * @deprecated
 */
void Eye::open(boolean isOpen)
{
  float ratio = isOpen ? 1 : 0;
  setOpenRatio(ratio);
  draw(0.0);
}

#define PRIMARY_COLOR WHITE
#define SECONDARY_COLOR TFT_DARKGREY

Avatar::Avatar()
{
  this->mouth = Mouth(160, 150, 50, 100, 4, 60, PRIMARY_COLOR, SECONDARY_COLOR);
  this->eyeballR = Eye(90, 90, 8, SECONDARY_COLOR, PRIMARY_COLOR);
  this->eyeballL = Eye(230, 90, 8, SECONDARY_COLOR, PRIMARY_COLOR);
  this->eyeR = Eye(90, 90, 20, PRIMARY_COLOR, SECONDARY_COLOR);
  this->eyeL = Eye(230, 90, 20, PRIMARY_COLOR, SECONDARY_COLOR);
  this->breath = 0.0;
  isEyeOpen = true;
  EyeOpenRatio = 1.0;
}
void Avatar::openMouth(int percent)
{
  mouth.open(percent);
}
void Avatar::setMouthOpen(float f)
{
  if(f < 0.1) f = 0.1;
  mouth.setOpenRatio(f);
}
/**
 * @deprecated
 */
void Avatar::openEye(boolean isOpen)
{
  eyeR.open(isOpen);
  eyeL.open(isOpen);
}
void Avatar::setEyeOpen(float f)
{
  EyeOpenRatio = f;
  eyeR.setOpenRatio(f);
  eyeL.setOpenRatio(f);
}
void Avatar::setExpression()
{
  // TODO
}
/**
 * @deprecated
 */
void Avatar::init()
{
  // TODO: start animation loop
}

/**
 * @experimental
 */
void Avatar::setBreath(float breath)
{
  this->breath = breath;
}

void Avatar::setGaze(float vertical, float horizontal)
{
  int v = floor(4 * vertical);
  int h = floor(4 * horizontal);
  eyeballL.setOffset(v, h);
  eyeballR.setOffset(v, h);
}

void Avatar::draw()
{
  mouth.draw(breath);
  eyeR.draw(breath);
  eyeL.draw(breath);
  if(EyeOpenRatio > 0) {
    eyeballR.draw(breath);
    eyeballL.draw(breath);
  }
}

void Avatar::extendAction()
{
  eyeL.open(0);
  eyeR.open(0);
  
}
