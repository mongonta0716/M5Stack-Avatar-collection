#include "avatar.h"

// Mouth
Mouth::Mouth(void)
{

}
Mouth::Mouth(int x, int y, int minWidth, int maxWidth, int minHeight, int maxHeight,
             uint32_t insideColor, uint32_t outsideColor, uint32_t bgColor)
{
  // TODO: validation
  this->x = x;
  this->y = y;
  this->minWidth = minWidth;
  this->maxWidth = maxWidth;
  this->minHeight = minHeight;
  this->maxHeight = maxHeight;
  this->insideColor = insideColor; 
  this->outsideColor = outsideColor; 
  this->bgColor = bgColor;
  this->openRatio = 0;
  this->lastX = 0;
  this->lastY = 0;
  this->lastW = 0;
  this->lastH = 0;
  this->offsetX = 0;
  this->offsetY = 0;
}
void Mouth::clear()
{
  M5.Lcd.fillEllipse(lastX + lastW / 2 + offsetX,
                     lastY + lastH / 2 + offsetY,
                     lastW / 2 + 2,
                     lastH / 2 + 2,
                     bgColor);
}
void Mouth::_draw(int x, int y, int w, int h)
{
  if (lastX == x && lastY == y && lastW == w && lastH == h) return;
  clear();
  M5.Lcd.fillEllipse(x + w / 2 + offsetX,
                     y + h / 2 + offsetY,
                     w / 2 + 2,
                     h / 2 + 2,
                     outsideColor);
  M5.Lcd.fillEllipse(x + w / 2 + offsetX,
                     y + h / 2 + offsetY,
                     w / 2 - 1,
                     h / 2 - 2,
                     insideColor);
  // Serial.printf("h:%d\n", h);
  if(h < 7) {
    M5.Lcd.drawLine(x + 2, y + h / 2 + offsetY, x + w - 3 , y + h / 2 + offsetY , BLACK);
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
void Mouth::extendAction()
{
}


Avatar::Avatar()
{
  M5.Lcd.drawJpg(avatar_bg_jpg, 0); // jpg_len is not used.
  const unsigned int INNER = M5.Lcd.color565(203,56,132);
  const unsigned int RIP = M5.Lcd.color565(252,218,214);
  const unsigned int HADAIRO = M5.Lcd.color565(255,233,218);

  this->mouth = Mouth(160, 170, 25, 50, 4, 30, INNER, RIP, HADAIRO);
  this->breath = 0.0;
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

void Avatar::draw()
{
  mouth.draw(breath);
}

void Avatar::extendAction()
{
}
