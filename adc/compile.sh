mkdir -p build/
rm -vrf build/adc.*
(cd build && sdcc -mmcs51 ../adc.c || exit)
packihx build/adc.ihx > adc.hex
