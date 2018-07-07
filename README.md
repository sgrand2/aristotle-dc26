# aristotle-dc26
Simple Badge for Defcon 26 Ethics Village using Attiny85
Badge has Momentary Switch, Coin Cell, 2 LEDS


###############################################################################
# ATTINY85 Pin Out for BusPirate Programming
###############################################################################
       ____ 
1.CS -|    |-8. VCC (3.3-5VDC)
2.NC -|    |-7. CLK   
3.NC -|    |-6. MISO   
4.GND-|____|-5. MOSI


###############################################################################
# TOD0: Actual Circuit
###############################################################################



###############################################################################
# Programming
###############################################################################
Environment: 
1. sudo apt-get -s install gcc-avr binutils-avr gdb-avr avr-libc avrdude
2. make
3. Flashing Chip Example:
   avrdude -c buspirate -P /dev/ttyUSB0 -p attiny85 -v -e -U flash:w:main.hex:i
