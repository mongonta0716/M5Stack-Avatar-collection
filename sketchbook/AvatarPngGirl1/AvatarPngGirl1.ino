#include <M5Stack.h>
#include <M5StackUpdater.h>
#include "src/avatar.h"
#include "src/eye.h"

Avatar *avatar;
Eye *eye;
TaskHandle_t taskHandle;

void drawLoop(void *args)
{
  for(;;)
  {
    avatar->setMouthOpen(0);
    avatar->draw();
    delay(1000);
  }
}

void blink(void *args)
{
  for(;;)
  {
    eye->blink();
  }
}

void startAvatar()
{
  avatar = new Avatar();
  eye = new Eye(80, 75, 160, 44);
  xTaskCreatePinnedToCore(
                    drawLoop,     /* Function to implement the task */
                    "drawLoop",   /* Name of the task */
                    2048,      /* Stack size in words */
                    NULL,      /* Task input parameter */
                    1,         /* Priority of the task */
                    &taskHandle,      /* Task handle. */
                    1);        /* Core where the task should run */
  xTaskCreatePinnedToCore(
                    blink,     /* Function to implement the task */
                    "blink",   /* Name of the task */
                    2048,      /* Stack size in words */
                    NULL,      /* Task input parameter */
                    0,         /* Priority of the task */
                    NULL,      /* Task handle. */
                    0);        /* Core where the task should run */  
}


void setup()
{
  M5.begin();
  Wire.begin();
  if(digitalRead(BUTTON_A_PIN) == 0) {
    Serial.println("Will Load menu binary");
    updateFromFS(SD);
    ESP.restart();
  }
  M5.Lcd.setBrightness(30);
  M5.Lcd.clear();
  M5.Lcd.setRotation(1);
  startAvatar(); // start drawing
}

void loop()
{
  // avatar's face updates in another thread
  // so no need to loop-by-loop rendering
  M5.update();
  if (M5.BtnA.wasPressed()) {
    vTaskSuspend(taskHandle);
    eye->right();
    vTaskResume(taskHandle);
  } else if (M5.BtnA.wasReleased()) {
  }
  if (M5.BtnB.isPressed()) {
    vTaskSuspend(taskHandle);
    for (int i=0; i <= 10; i++) {
      float open = (float)i/10.0;
      avatar->setMouthOpen(open);
      avatar->draw();
      delay(100);
    }
    for (int i=10; i > 1; i--) {
      float open = (float)i/10.0;
      avatar->setMouthOpen(open);
      avatar->draw();
      delay(100);
    }
  } else if (M5.BtnB.wasReleased()) {
    vTaskResume(taskHandle);
  }
  if (M5.BtnC.wasPressed()) {
    vTaskSuspend(taskHandle);
    while (M5.BtnC.isPressed()) {
      M5.update();
      float mouseopenratio = float(random(5)) / 10;
      avatar->setMouthOpen(mouseopenratio);
      avatar->draw();
      delay(500);
    }
    vTaskResume(taskHandle);
  } else if (M5.BtnC.wasReleased()) {
  }

}
