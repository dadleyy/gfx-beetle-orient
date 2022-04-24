#include <Arduino.h>
#include <tft_spi.hpp>
#include <gfx.hpp>

#include "ili9341v.hpp"
#include "jellee-bold.hpp"

#define LCD_SS_PIN    17
#define PIN_NUM_DC    16
#define PIN_NUM_RST   4
#define PIN_NUM_BCKL  13
#define LCD_ROTATION 0
#define LCD_BACKLIGHT_HIGH true

using bus_type = arduino::tft_spi_ex<3, 17, 23, -1, 18>;
using lcd_type = arduino::ili9341v<
  PIN_NUM_DC,
  PIN_NUM_RST,
  PIN_NUM_BCKL,
  bus_type,
  LCD_ROTATION,
  LCD_BACKLIGHT_HIGH
>;
using lcd_color = gfx::color<typename lcd_type::pixel_type>;

lcd_type lcd;
unsigned char frame = 0;

void setup(void) {
  pinMode(PIN_NUM_RST, OUTPUT);
  pinMode(PIN_NUM_DC, OUTPUT);
  pinMode(LCD_SS_PIN, OUTPUT);
  pinMode(PIN_NUM_BCKL, OUTPUT);

  digitalWrite(PIN_NUM_RST, HIGH);
  delay(10);
  digitalWrite(PIN_NUM_RST, LOW);
  delay(100);
  digitalWrite(PIN_NUM_RST, HIGH);
  delay(50);

  gfx::draw::filled_rectangle(lcd, (gfx::srect16) lcd.bounds(), lcd_color::black);
}

void loop(void) {
  const gfx::open_font & f = Jellee_Bold_ttf;
  float scale = f.scale(20);

  switch (frame) {
    case 0: {
      const char * text = "1: the quick brown";
      gfx::srect16 text_rect = f.measure_text((gfx::ssize16) lcd.dimensions(), {0, 0}, text, scale).bounds();
      gfx::draw::filled_rectangle(lcd, (gfx::srect16) lcd.bounds(), lcd_color::black);
      gfx::draw::text(lcd, text_rect, {0, 0}, text, f, scale, lcd_color::white, lcd_color::black, false);
      frame = frame + 1;
      break;
    }
    case 1: {
      const char * text = "2: fox jumps over";
      gfx::srect16 text_rect = f.measure_text((gfx::ssize16) lcd.dimensions(), {0, 0}, text, scale).bounds();
      gfx::draw::filled_rectangle(lcd, (gfx::srect16) lcd.bounds(), lcd_color::black);
      gfx::draw::text(lcd, text_rect, {0, 0}, text, f, scale, lcd_color::white, lcd_color::black, false);
      frame = frame + 1;
      break;
    }
    case 2: {
      const char * text = "3: the lazy dog";
      gfx::srect16 text_rect = f.measure_text((gfx::ssize16) lcd.dimensions(), {0, 0}, text, scale).bounds();
      gfx::draw::filled_rectangle(lcd, (gfx::srect16) lcd.bounds(), lcd_color::black);
      gfx::draw::text(lcd, text_rect, {0, 0}, text, f, scale, lcd_color::white, lcd_color::black, false);
      frame = frame + 1;
      break;
    }
    default:
      frame = 0;
  }

  delay(2000);
}
