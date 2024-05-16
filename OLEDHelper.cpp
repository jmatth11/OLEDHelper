#include "OLEDHelper.h"

OLEDHelper::OLEDHelper(uint8_t height, uint8_t width) {
  this->height = height;
  this->width = width;
  display = Adafruit_SSD1306(width, height, &Wire, -1);
  if (height == 64) {
    i2cAddr = 0x3D;
  } else {
    i2cAddr = 0x3C;
  }
}
OLEDHelper::~OLEDHelper() {}

bool OLEDHelper::setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, i2cAddr)) {
    return false;
  }
  // wait for display to initialize
  delay(2000);
  display.clearDisplay();
  // need to set color to white so text shows up
  display.setTextColor(WHITE);
  display.setTextSize(1);
  return true;
}

void OLEDHelper::write(String header, String msg) {
  display.clearDisplay();
  const int16_t x_pos = getCenteredX(header);
  display.setCursor(x_pos, 0);
  display.println(header);
  display.setCursor(1, 10);
  display.println(msg);
  display.display();
}

void OLEDHelper::write(String msg, int16_t x, int16_t y) {
  display.clearDisplay();
  display.setCursor(x, y);
  display.println(msg);
  display.display();
}

int16_t OLEDHelper::getCenteredX(String s, int16_t offset) {
  int16_t outx = 0, outy = 0;
  uint16_t outw = 0, outh = 0;
  display.getTextBounds(s, 0, 0, &outx, &outy, &outw, &outh);
  const int16_t half_screen_width = width /2;
  const int16_t half_string_width = outw / 2;
  int16_t x_pos = half_screen_width - half_string_width;
  if (x_pos < 0) {
    x_pos = 0;
  }
  return x_pos + offset;
}
int16_t OLEDHelper::getCenteredY(String s, int16_t offset) {
  int16_t outx = 0, outy = 0;
  uint16_t outw = 0, outh = 0;
  display.getTextBounds(s, 0, 0, &outx, &outy, &outw, &outh);
  const int16_t half_screen_height = height /2;
  const int16_t half_string_height = outh / 2;
  int16_t y_pos = half_screen_height - half_string_height;
  if (y_pos < 0) {
    y_pos = 0;
  }
  return y_pos + offset;
}

int16_t OLEDHelper::getRightAlignedX(String s, int16_t offset) {
  int16_t outx = 0, outy = 0;
  uint16_t outw = 0, outh = 0;
  display.getTextBounds(s, 0, 0, &outx, &outy, &outw, &outh);
  int16_t new_x = width - outw;
  if (new_x < 0) {
    new_x = 0;
  }
  return new_x + offset;
}

int16_t OLEDHelper::getBottomAlignedY(String s, int16_t offset) {
  int16_t outx = 0, outy = 0;
  uint16_t outw = 0, outh = 0;
  display.getTextBounds(s, 0, 0, &outx, &outy, &outw, &outh);
  int16_t new_y = height - outh;
  if (new_y < 0) {
    new_y = 0;
  }
  return new_y + offset;
}

const Adafruit_SSD1306 OLEDHelper::getDisplay() {
  return display;
}
