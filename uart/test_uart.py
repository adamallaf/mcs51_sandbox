"""
A simple uart test, the MCU must send back what it recieves.
../stcgal-pyenv/bin/python test_uart.py
"""

from time import sleep

from serial import Serial

if __name__ == "__main__":
    print("Press ctrl+c to close")
    s = Serial(port="/dev/ttyUSB0", baudrate=115200, timeout=1)
    try:
        while True:
            s.write(b"Hello")
            b = s.read(5)
            if b:
                assert b == b"Hello"
                print(f"sent and received {b.decode()[:-1]}", end="\r")
                time.sleep(1)
            else:
                print("didn't receive a response!")
                break
    finally:
        s.close()
        print()
        print("closed")
