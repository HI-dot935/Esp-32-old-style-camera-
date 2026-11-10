// So this code is just to check the preview if camera shows image on display or not.
#include "esp_camera.h"
#include <LovyanGFX.hpp>

LGFX tft;

void setup() {
  Serial.begin(115200);

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  camera_config_t config = {};

// Note for reviewer that I haven't defined the pins yet.


  config.pixel_format = PIXFORMAT_RGB565;
  config.frame_size = FRAMESIZE_QVGA;
  config.fb_count = 2;
  config.fb_location = CAMERA_FB_IN_PSRAM;

  if (esp_camera_init(&config) != ESP_OK) {
    Serial.println("Camera failed!");
    while (true) delay(1000);
  }
}

void loop() {
  camera_fb_t *frame = esp_camera_fb_get();
  if (!frame) return;

  tft.pushImage(0, 0, 320, 240,
                (uint16_t *)frame->buf);

  esp_camera_fb_return(frame);
}
