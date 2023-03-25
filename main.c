static void orgit() __naked {
  __asm
  org     0x140D
    nop
    nop
    nop
    __endasm;
}

void main2();

void main() {

  main2();
}

#include "../NABULIB/NABU-LIB.h"


void main2() {

  // Put the graphics into text mode with the text color 0x01 and background color 0x03
  vdp_initTextMode(0x01, 0x03);

  // Enable only the Tone Generator on Channel A
  ayWrite(0x7, 0b00111110);

  // Set the amplitude (volume) to maximum on Channel A
  ayWrite(0x8, 0b00001111);

  const uint8_t song[] = { 200, 100, 50, 100, 150, 200, 100, 50, 230, 90, 20, 80, 20, 20, 20, 80, 50, 50, 20, 80, 20, 80 };
  
  struct {
    uint8_t x;
    uint8_t y;
  } newPosition;

  struct {
    uint8_t x;
    uint8_t y;
  } lastPosition;

  bool    xDir = true;
  bool    yDir = true;
  uint8_t songPos = 0;
  
  uint8_t value_0;
  uint8_t value_1;
  uint8_t value_2;
  uint8_t value_3;
  uint8_t value_4;
  uint8_t value_5;
  uint8_t value_6;
  uint8_t value_7;
  uint8_t char_cnt = 0;
  uint8_t value_final[] = "00000000"; 
  int8_t name[66] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789~!@#$%^&*()-_=+[{]}\|;:'<>.?,/";
  int8_t * msg_ptr = name;  
  
  lastPosition.x = 0;
  lastPosition.y = 0;

  while (true) {

    // Have we hit the X axis limits? If so, reverse directions
    if (lastPosition.x >= 29)
      xDir = false;
    else if (lastPosition.x == 0)
      xDir = true;

    // What direction are we moving
    /* if (xDir)
      newPosition.x = lastPosition.x + 1;
    else
      newPosition.x = lastPosition.x - 1; */

    // Have we hit the Y axis limits? If so, reverse directions
    if (lastPosition.y >= 23)
      yDir = false;
    else if (lastPosition.y == 0)
      yDir = true;

    // What direction are we moving
/*     if (yDir)
      newPosition.y = lastPosition.y + 1;
    else
      newPosition.y = lastPosition.y - 1; */

    // Move the cursor to the last position that we were and erase what was there
    vdp_setCursor2(lastPosition.x, lastPosition.y);
    vdp_print("          ");

    // Write the text in the new position
    vdp_setCursor2(newPosition.x, newPosition.y);
    //vdp_print("NABU");
	
 	if(*msg_ptr != '\0')
	{
		if((0x04 && IO_KEYBOARD_STATUS) == 0x01)
		{
		IO_KEYBOARD = *msg_ptr;
		IO_KEYBOARD_STATUS = 0x05;
		msg_ptr++;
		}
	}
	else
	{
		if((0x04 && IO_KEYBOARD_STATUS) == 0x01)
		{
			IO_KEYBOARD = 0x0D;	//carriage return
			IO_KEYBOARD_STATUS = 0x05;
			z80_delay_ms(1);
		}
		if((0x04 && IO_KEYBOARD_STATUS) == 0x01)
		{
			IO_KEYBOARD = 0x0A; //line feed
			IO_KEYBOARD_STATUS = 0x05;
			msg_ptr = name;
		}
	}
	
	if(IO_KEYBOARD_STATUS & 0x01) {value_final[7] = '1';} else {value_final[7] = '0';}
	if(IO_KEYBOARD_STATUS & 0x02) {value_final[6] = '1';} else {value_final[6] = '0';}
	if(IO_KEYBOARD_STATUS & 0x04) {value_final[5] = '1';} else {value_final[5] = '0';}
	if(IO_KEYBOARD_STATUS & 0x08) {value_final[4] = '1';} else {value_final[4] = '0';}
	if(IO_KEYBOARD_STATUS & 0x10) {value_final[3] = '1';} else {value_final[3] = '0';}
	if(IO_KEYBOARD_STATUS & 0x20) {value_final[2] = '1';} else {value_final[2] = '0';}
	if(IO_KEYBOARD_STATUS & 0x40) {value_final[1] = '1';} else {value_final[1] = '0';}
	if(IO_KEYBOARD_STATUS & 0x80) {value_final[0] = '1';} else {value_final[0] = '0';}

	vdp_print((char *)value_final);

    // Save the new position into the last position
    lastPosition.x = newPosition.x;
    lastPosition.y = newPosition.y;

    ayWrite(0, song[songPos++ % sizeof(song)]);
    ayWrite(1, 1);
    //z80_delay_ms(1);
  }
}

