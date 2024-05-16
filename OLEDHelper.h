#ifndef GARDENOMETER_DISPLAY_H
#define GARDENOMETER_DISPLAY_H

#include <stdint.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WString.h>

class OLEDHelper {

  /* main display class */
  Adafruit_SSD1306 display;
  /* dimensions of screen */
  uint8_t width;
  uint8_t height;
  /* I2C address */
  uint16_t i2cAddr;

  public:
    /**
     * Construct the OLED helper.
     * Currently only supports height of 32 or 64 and width of only 128.
     */
    OLEDHelper(uint8_t height=32, uint8_t width=128);
    ~OLEDHelper();

    /**
     * Sets up the display for writing.
     * @returns True if successful, false otherwise.
     */
    bool setup();

    /**
     * Write a given header and message to the screen.
     * The header will be center aligned. The message will be left justified.
     * @param header The header string.
     * @param msg The body string.
     */
    void write(String header, String msg);
    /**
     * Write the given string at the specified x and y coordinates.
     * @param msg The message to print.
     * @param x The X position.
     * @param y The Y position.
     */
    void write(String msg, int16_t x, int16_t y);

    /**
     * Get the X position that would center the text on the x plane.
     * @param s The string to center.
     * @param offset The offset to be applied.
     * @returns The calulated X position.
     */
    int16_t getCenteredX(String s, int16_t offset=0);
    /**
     * Get the Y position that would center the text on the Y plane.
     * @param s The string to center.
     * @param offset The offset to be applied.
     * @returns The calulated Y position.
     */
    int16_t getCenteredY(String s, int16_t offset=0);
    /**
     * Get the X position that would align the text to the right of the screen.
     * @param s The string to align.
     * @param offset The offset to be applied.
     * @returns The calulated X position.
     */
    int16_t getRightAlignedX(String s, int16_t offset=0);
    /**
     * Get the Y position that would align the text to the bottom of the screen.
     * @param s The string to align.
     * @param offset The offset to be applied.
     * @returns The calulated Y position.
     */
    int16_t getBottomAlignedY(String s, int16_t offset=0);

    /**
     * Get the internal display object.
     * @returns The Adafruit_SSD1306 object.
     */
    Adafruit_SSD1306& getDisplay();
};

#endif
