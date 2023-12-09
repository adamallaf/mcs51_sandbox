sdcc -mmcs51 uart.c || exit
packihx uart.ihx > uart.hex
