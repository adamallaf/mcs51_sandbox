mkdir -p build/
rm -vrf build/adc.*
(cd build && sdcc -mmcs51 ../cap_touch_key.c || exit)
packihx build/cap_touch_key.ihx > cap_touch_key.hex
