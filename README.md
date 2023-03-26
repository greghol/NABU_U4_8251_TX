# NABU_U4_8251_TX

The NABU's U4 8251A is a UART to receive keyboard/Joystick data stock. The Tx
related signals of the UART is not used and available by the user. One use is
mirroing the VDP characters to a serial terminal device. i.e. TeraTerm. Uses
include 80 column support and debug messages as an example.

### License

MIT

### Support code

DJ Sures's NABU-LIB is used to compile against using z88dk Z80 C Compiler.
The Hello World C under NABU_LIB is the base code for NABU_U4_8251_TX code.

### Theroy of Operation

The keyboard's Rx side of the 8251A is running at xxxx baud. The RxC is feed
from a clock that is 16 times or 16x the required baud. The Tx side is similar
but both sides have to be the same baud multiplier. i.e. 16x. A 1.79 MHz signal
is feed into the TxC to produce 111875 baud. This is close enough for 115200 baud
and most receivers will receive data just fine 115200 baud. The system clock is
tied to the TxC input. The Txd (Tx Data) is feed into a USB serial dongle or a +5/+3
RS232 dogle.

### HW Mods for Tx Connection

TxC (pin 9) is connected to CLK (pin 20) with a jumper.
TxD (pin 19) is connected to the TX input of the serial USB or RS232 dongle.
GND (pin 4) or another digital ground can be connected to the ground of the
            serial/RS232 converter.

### Demo Software

Load the 000001.nabu pak with your IA software to the NABU. This produce a
string of characters with line feed and carriage returns in a loop.





