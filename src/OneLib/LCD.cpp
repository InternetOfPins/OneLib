#include <OneLib.h>
using namespace OneLib;
#include "LCD.h"

template<typename API>
void LCD<API>::begin(unsigned char cols, unsigned char lines, unsigned char dotsize) {
  if (lines > 1) {
    displayFunction |= LCD_2LINE;
  }
  numLines = lines;

  setRowOffsets(0x00, 0x40, 0x00 + cols, 0x40 + cols);

  // for some 1 line displays you can select a 10 pixel high font
  if ((dotsize != LCD_5x8DOTS) && (lines == 1)) {
    displayFunction |= LCD_5x10DOTS;
  }

  _rs_pin.begin();
  _rw_pin.begin();
  _enable_pin.begin();

  // Do these once, instead of every time a character is drawn for speed reasons.
  for (int i=0; i< 8; ++i)
    _data_pins[i]->begin();

  // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
  // according to datasheet, we need at least 40ms after power rises above 2.7V
  // before sending commands. Arduino can turn on way before 4.5V so we'll wait 50
  API::delay_us(50000);
  // Now we pull both RS and R/W low to begin commands
  // digitalWrite(_rs_pin, LOW);
  _rs_pin.off();
  // digitalWrite(_enable_pin, LOW);
  _enable_pin.off();
  // if (_rw_pin != 255) {
  //   digitalWrite(_rw_pin, LOW);
  // }
  _rw_pin.off();

  //put the LCD into 4 bit or 8 bit mode
  // if (! (displayFunction & LCD_8BITMODE)) {
  //   // this is according to the hitachi HD44780 datasheet
  //   // figure 24, pg 46
  //
  //   // we start in 8bit mode, try to set 4 bit mode
  //   write4bits(0x03);
  //   delay_us(4500); // wait min 4.1ms
  //
  //   // second try
  //   write4bits(0x03);
  //   delay_us(4500); // wait min 4.1ms
  //
  //   // third go!
  //   write4bits(0x03);
  //   delay_us(150);
  //
  //   // finally, set to 4-bit interface
  //   write4bits(0x02);
  // } else {
    // this is according to the hitachi HD44780 datasheet
    // page 45 figure 23

    // Send function set command sequence
    command(LCD_FUNCTIONSET | displayFunction);
    API::delay_us(4500);  // wait more than 4.1ms TODO change this

    // second try
    command(LCD_FUNCTIONSET | displayFunction);
    API::delay_us(150);

    // third go
    command(LCD_FUNCTIONSET | displayFunction);
  // }

  // finally, set # lines, font size, etc.
  command(LCD_FUNCTIONSET | displayFunction);

  // turn the display on with no cursor or blinking default
  _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
  display();

  // clear it off
  clear();

  // Initialize to default text direction (for romance languages)
  _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
  // set the entry mode
  command(LCD_ENTRYMODESET | _displaymode);

}

template<typename API>
void LCD<API>::setRowOffsets(int row0, int row1, int row2, int row3)
{
  _row_offsets[0] = row0;
  _row_offsets[1] = row1;
  _row_offsets[2] = row2;
  _row_offsets[3] = row3;
}

/********** high level commands, for the user! */
template<typename API>
void LCD<API>::clear()
{
  command(LCD_CLEARDISPLAY);  // clear display, set cursor position to zero
  API::delay_us(2000);  // this command takes a long time!
}

template<typename API>
inline void LCD<API>::command(unsigned char value) {
  send(value, LOW);
}

template<typename API>
void LCD<API>::display() {
  _displaycontrol |= LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

/************ low level data pushing commands **********/

// write either command or data, with automatic 4/8-bit selection
template<typename API>
void LCD<API>::send(unsigned char value, unsigned char mode) {
  // digitalWrite(_rs_pin, mode);
  _rs_pin.set(mode);

  _rw_pin.off();
  // if there is a RW pin indicated, set it low to Write
  // if (_rw_pin != 255) {
  //   digitalWrite(_rw_pin, LOW);
  // }

  // if (_displayfunction & LCD_8BITMODE) {
    write8bits(value);
  // } else {
  //   write4bits(value>>4);
  //   write4bits(value);
  // }
}

template<typename API>
void LCD<API>::pulseEnable(void) {
  _enable_pin.off();
  API::delay_us(1);
  _enable_pin.on();
  API::delay_us(1);    // enable pulse must be >450ns
  _enable_pin.off();
  delay_us(100);   // commands need > 37us to settle TODO: change this
}

template<typename API>
void LCD<API>::write8bits(unsigned char value) {
  for (int i = 0; i < 8; i++)
    _data_pins[i]->set(value>>i);

    // digitalWrite(_data_pins[i], (value >> i) & 0x01);

  pulseEnable();
}
