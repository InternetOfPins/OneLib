/* -*- C++ -*- */

#include <OneLib.h>
using namespace OneLib;

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// typedef Hook<PinCap<VoidPin>> NA;

template<typename API>
class LCD {
public:
  LCD(OnePin& rs,OnePin& rw,OnePin& en,
    OnePin& d0,OnePin& d1,OnePin& d2,OnePin& d3,
    OnePin& d4,OnePin& d5,OnePin& d6,OnePin& d7)
    :_rs_pin(rs),_rw_pin(rw),_enable_pin(en),displayFunction(LCD_8BITMODE | LCD_1LINE | LCD_5x8DOTS) {
      _data_pins[0]=&d0;
      _data_pins[1]=&d1;
      _data_pins[2]=&d2;
      _data_pins[3]=&d3;
      _data_pins[4]=&d4;
      _data_pins[5]=&d5;
      _data_pins[6]=&d6;
      _data_pins[7]=&d7;
    }
  void begin(unsigned char cols, unsigned char rows, unsigned char charsize = LCD_5x8DOTS);

  void clear();
//   void home();

//   void noDisplay();
  void display();
//   void noBlink();
//   void blink();
//   void noCursor();
//   void cursor();
//   void scrollDisplayLeft();
//   void scrollDisplayRight();
//   void leftToRight();
//   void rightToLeft();
//   void autoscroll();
//   void noAutoscroll();

  void setRowOffsets(int row1, int row2, int row3, int row4);
//   void createChar(unsigned char, unsigned char[]);
//   void setCursor(unsigned char, unsigned char);
//   virtual size_t write(unsigned char);
  void command(unsigned char);

//   using Print::write;
private:
  void send(unsigned char, unsigned char);
//   void write4bits(unsigned char);
  void write8bits(unsigned char);
  void pulseEnable();
//
  OnePin& _rs_pin; // LOW: command.  HIGH: character.
  OnePin& _rw_pin; // LOW: write to LCD.  HIGH: read from LCD.
  OnePin& _enable_pin; // activated by a HIGH pulse.
  OnePin* _data_pins[8];
//
  unsigned char displayFunction;
  unsigned char _displaycontrol;
  unsigned char _displaymode;
//
//   unsigned char _initialized;
//
  unsigned char numLines;
  unsigned char _row_offsets[4];
};
