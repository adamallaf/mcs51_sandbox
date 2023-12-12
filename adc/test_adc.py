"""
Reads the ADC value sent by the MCU via UART,
connect a 10kOhm potentiometer on ADC input.
../stcgal-pyenv/bin/python test_adc.py
"""
from serial import Serial
from time import sleep


if __name__ == "__main__":
    print("Press ctrl+c to close")
    s = Serial(port="/dev/ttyUSB0", baudrate=115200, timeout=1)
    try:
        while True:
            b = s.readline()
            if b:
                print(b.decode()[:-1], end='\r')
    finally:
        s.close()
        print()
        print("closed")
