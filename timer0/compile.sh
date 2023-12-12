mkdir -p build/
rm -vrf build/timer0.*
(cd build && sdcc -mmcs51 ../timer0.c || exit)
packihx build/timer0.ihx > timer0.hex
