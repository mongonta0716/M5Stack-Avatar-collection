#include "eye.h"

TFT_eSprite eyeSprite = TFT_eSprite(&M5.Lcd);

// Eye

Eye::Eye()
{

}
Eye::Eye(int x, int y, int width, int height)
{
  // TODO: validation
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  eyeSprite.setColorDepth(16);
  eyeSprite.createSprite(width, height);
}

void Eye::close()
{
  eyeSprite.pushImage(0, 0, width, height, eye_center_half);
  eyeSprite.pushSprite(x, y);
  delay(100 + 10 * random(20));
  eyeSprite.pushImage(0, 0, width, height, eye_close);
  eyeSprite.pushSprite(x, y);
}

void Eye::blink()
{
  int eyemode = random(8);
  if (eyemode == 1) {
	left();
  } else if (eyemode == 2) {
	right();
  } else {
	center();
  }
}

void Eye::center()
{
  eyeSprite.pushImage(0, 0, width, height, eye_center_open);
  eyeSprite.pushSprite(x, y);
  delay(2500 + 100 * random(20));
  close();
}

void Eye::left()
{
  eyeSprite.pushImage(0, 0, width, height, eye_left);
  eyeSprite.pushSprite(x, y);
  delay(500 + 100 * random(3));
  close();
}

void Eye::right()
{
  eyeSprite.pushImage(0, 0, width, height, eye_right);
  eyeSprite.pushSprite(x, y);
  delay(500 + 100 * random(3));
  close();
}


