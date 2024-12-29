static const uint8_t System7x7[] PROGMEM = {
    // Fixed width; 
    // font data
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // (space)
0x00, 0x00, 0x00, 0x5F, 0x00, 0x00, 0x00,  // !
0x00, 0x00, 0x07, 0x00, 0x07, 0x00, 0x00,  // "
0x00, 0x14, 0x7F, 0x14, 0x7F, 0x14, 0x00,  // #
0x00, 0x24, 0x2A, 0x7F, 0x2A, 0x12, 0x00,  // $
0x00, 0x23, 0x13, 0x08, 0x64, 0x62, 0x00,  // %
0x00, 0x36, 0x49, 0x55, 0x22, 0x50, 0x00,  // &
0x00, 0x00, 0x05, 0x03, 0x00, 0x00, 0x00,  // '
0x00, 0x00, 0x1C, 0x22, 0x41, 0x00, 0x00,  // (
0x00, 0x00, 0x41, 0x22, 0x1C, 0x00, 0x00,  // )
0x00, 0x08, 0x2A, 0x1C, 0x2A, 0x08, 0x00,  // *
0x00, 0x08, 0x08, 0x3E, 0x08, 0x08, 0x00,  // +
0x00, 0x00, 0x50, 0x30, 0x00, 0x00, 0x00,  // ,
0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00,  // -
0x00, 0x00, 0x60, 0x60, 0x00, 0x00, 0x00,  // .
0x00, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00,  // /

  0b00000000,
  0b00111110, // 0
  0b01111111,
  0b01100011,
  0b01100011,
  0b01111111,
  0b00111110,

  0b00000000,
  0b00000000, // 1 (modified)
  0b00000100,
  0b00000110,
  0b01111111,
  0b01111111,
  0b00000000,

  0b00000000,
  0b01100010, // 2
  0b01110011,
  0b01111011,
  0b01101011,
  0b01101111,
  0b01100110,

  0b00000000,
  0b00100011, // 3 (modified)
  0b01100011,
  0b01101011,
  0b01101011,
  0b01111111,
  0b00110111,

  0b00000000,
  0b00000111, // 4
  0b00001111,
  0b00001100,
  0b00001100,
  0b01111111,
  0b01111111,

  0b00000000,
  0b01101111, // 5
  0b01101111,
  0b01101011,
  0b01101011,
  0b01111011,
  0b00110011,

  0b00000000,
  0b00111110, // 6
  0b01111111,
  0b01101011,
  0b01101011,
  0b01111011,
  0b00110010,
  
  0b00000000,
  0b00000011, // 7
  0b00000011,
  0b01111011,
  0b01111111,
  0b00000111,
  0b00000011,
  
  0b00000000,
  0b00110110, // 8
  0b01111111,
  0b01101011,
  0b01101011,
  0b01111111,
  0b00110110,
  
  0b00000000,
  0b00100110, // 9
  0b01101111,
  0b01101011,
  0b01101011,
  0b01111111,
  0b00111110,
  
0x00, 0x00, 0x36, 0x36, 0x00, 0x00, 0x00,  // :
0x00, 0x00, 0x56, 0x36, 0x00, 0x00, 0x00,  // ;
0x00, 0x00, 0x08, 0x14, 0x22, 0x41, 0x00,  // <
0x00, 0x14, 0x14, 0x14, 0x14, 0x14, 0x00,  // =
0x00, 0x41, 0x22, 0x14, 0x08, 0x00, 0x00,  // >
0x00, 0x02, 0x01, 0x51, 0x09, 0x06, 0x00,  // ?
0x00, 0x32, 0x49, 0x79, 0x41, 0x3E, 0x00,  // @
0x00, 0x7E, 0x11, 0x11, 0x11, 0x7E, 0x00,  // A
0x00, 0x7F, 0x49, 0x49, 0x49, 0x36, 0x00,  // B
0x00, 0x3E, 0x41, 0x41, 0x41, 0x22, 0x00,  // C
0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C, 0x00,  // D
0x00, 0x7F, 0x49, 0x49, 0x49, 0x41, 0x00,  // E
0x00, 0x7F, 0x09, 0x09, 0x01, 0x01, 0x00,  // F
0x00, 0x3E, 0x41, 0x41, 0x51, 0x32, 0x00,  // G
0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00,  // H
0x00, 0x00, 0x41, 0x7F, 0x41, 0x00, 0x00,  // I
0x00, 0x20, 0x40, 0x41, 0x3F, 0x01, 0x00,  // J
0x00, 0x7F, 0x08, 0x14, 0x22, 0x41, 0x00,  // K
0x00, 0x7F, 0x40, 0x40, 0x40, 0x40, 0x00,  // L
0x00, 0x7F, 0x02, 0x04, 0x02, 0x7F, 0x00,  // M
0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F, 0x00,  // N
0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E, 0x00,  // O
0x00, 0x7F, 0x09, 0x09, 0x09, 0x06, 0x00,  // P
0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E, 0x00,  // Q
0x00, 0x7F, 0x09, 0x19, 0x29, 0x46, 0x00,  // R
0x00, 0x46, 0x49, 0x49, 0x49, 0x31, 0x00,  // S
//0x00, 0x01, 0x01, 0x7F, 0x01, 0x01, 0x00,  // T
  0b00000000,
  0b00000011, // T
  0b00000011,
  0b11111111,
  0b11111111,
  0b00000011,
  0b00000011,

//0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F, 0x00,  // U
  0b00000000,
  0b11111111, // U
  0b11111111,
  0b11000000,
  0b11000000,
  0b11111111,
  0b11111111,

  0b00011111, // V
  0b00111111,
  0b00100000,
  0b01000000,
  0b00100000,
  0b00111111,
  0b00011111,

0x00, 0x7F, 0x20, 0x18, 0x20, 0x7F, 0x00,  // W
0x00, 0x63, 0x14, 0x08, 0x14, 0x63, 0x00,  // X
0x00, 0x03, 0x04, 0x78, 0x04, 0x03, 0x00,  // Y
0x00, 0x61, 0x51, 0x49, 0x45, 0x43, 0x00,  // Z
0x00, 0x00, 0x00, 0x7F, 0x41, 0x41, 0x00,  // [
0x00, 0x02, 0x04, 0x08, 0x10, 0x20, 0x00,  // "\"
0x00, 0x41, 0x41, 0x7F, 0x00, 0x00, 0x00,  // ]
0x00, 0x04, 0x02, 0x01, 0x02, 0x04, 0x00,  // ^
0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00,  // _
0x00, 0x00, 0x01, 0x02, 0x04, 0x00, 0x00,  // `
0x00, 0x20, 0x54, 0x54, 0x54, 0x78, 0x00,  // a
0x00, 0x7F, 0x48, 0x44, 0x44, 0x38, 0x00,  // b
0x00, 0x38, 0x44, 0x44, 0x44, 0x20, 0x00,  // c
0x00, 0x38, 0x44, 0x44, 0x48, 0x7F, 0x00,  // d
0x00, 0x38, 0x54, 0x54, 0x54, 0x18, 0x00,  // e
0x00, 0x08, 0x7E, 0x09, 0x01, 0x02, 0x00,  // f
0x00, 0x08, 0x14, 0x54, 0x54, 0x3C, 0x00,  // g
0x00, 0x7F, 0x08, 0x04, 0x04, 0x78, 0x00,  // h
0x00, 0x00, 0x44, 0x7D, 0x40, 0x00, 0x00,  // i
0x00, 0x20, 0x40, 0x44, 0x3D, 0x00, 0x00,  // j
0x00, 0x00, 0x7F, 0x10, 0x28, 0x44, 0x00,  // k
0x00, 0x00, 0x41, 0x7F, 0x40, 0x00, 0x00,  // l
0x00, 0x7C, 0x04, 0x18, 0x04, 0x78, 0x00,  // m
0x00, 0x7C, 0x08, 0x04, 0x04, 0x78, 0x00,  // n
0x00, 0x38, 0x44, 0x44, 0x44, 0x38, 0x00,  // o
0x00, 0x7C, 0x14, 0x14, 0x14, 0x08, 0x00,  // p
0x00, 0x08, 0x14, 0x14, 0x18, 0x7C, 0x00,  // q
0x00, 0x7C, 0x08, 0x04, 0x04, 0x08, 0x00,  // r
0x00, 0x48, 0x54, 0x54, 0x54, 0x20, 0x00,  // s
0x00, 0x04, 0x3F, 0x44, 0x40, 0x20, 0x00,  // t
0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C, 0x00,  // u
  0b00011100, // v
  0b00111100,
  0b00100000,
  0b01000000,
  0b00100000,
  0b00111100,
  0b00011100,

0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C, 0x00,  // w
0x00, 0x44, 0x28, 0x10, 0x28, 0x44, 0x00,  // x
0x00, 0x0C, 0x50, 0x50, 0x50, 0x3C, 0x00,  // y
0x00, 0x44, 0x64, 0x54, 0x4C, 0x44, 0x00,  // z
0x00, 0x00, 0x08, 0x36, 0x41, 0x00, 0x00,  // {
0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00,  // |
0x00, 0x00, 0x41, 0x36, 0x08, 0x00, 0x00,  // }
0x00, 0x08, 0x08, 0x2A, 0x1C, 0x08, 0x00,  // ->
0x00, 0x08, 0x1C, 0x2A, 0x08, 0x08, 0x00  // <-
};
