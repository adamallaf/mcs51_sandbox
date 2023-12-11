sdcc -mmcs51 adc.c || exit
packihx adc.ihx > adc.hex
