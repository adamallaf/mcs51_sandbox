mkdir -p build/
rm -vrf build/hello.*
(cd build && sdcc -mmcs51 ../hello.c || exit)
packihx build/hello.ihx >hello.hex
