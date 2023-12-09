sdcc -mmcs51 test.c || exit
packihx test.ihx > test.hex
