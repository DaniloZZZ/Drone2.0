avr-gcc  -mmcu=atmega328p -c simtest.c -Wall -g -Os 

avr-gcc  -mmcu=atmega328p -o simtest.elf simtest.o

avr-objcopy  -I ihex blink.elf blink.hex   

avrdude -p atmega328p -c Usbasp -U flash:w:blink.hex  -v

