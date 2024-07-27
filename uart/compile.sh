mkdir -p build/
rm -vrf build/uart.*
(cd build && sdcc -mmcs51 ../uart.c || exit)
packihx build/uart.ihx >uart.hex
