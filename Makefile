# environment variables
ARDUINO_ROOT=/Applications/Arduino.app/Contents/Java/hardware/tools/avr
DEVICE_PATH=/dev/cu.usbmodem1421

SKETCH=main
OBJ_DEPS=button-pin2.o button-pin3.o buzzer.o notes.o players.o timer0.o uart.o
CFLAGS=-Wall -Os -mmcu=atmega328

# you probably shouldn't change these variables
GCC=$(ARDUINO_ROOT)/bin/avr-gcc
OBJCOPY=$(ARDUINO_ROOT)/bin/avr-objcopy
AVRDUDE=$(ARDUINO_ROOT)/bin/avrdude
AVRDUDE_CONF=$(ARDUINO_ROOT)/etc/avrdude.conf

.PHONY: upload clean
.PRECIOUS: %.o

upload: $(SKETCH).hex $(AVRDUDE_CONF) $(DEVICE_PATH)
	$(AVRDUDE) -C$(AVRDUDE_CONF) -v -patmega328p -carduino -P$(DEVICE_PATH) -b115200 -D -Uflash:w:$<:i

%.hex: %.x
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

%.x: $(OBJ_DEPS) %.c
	$(GCC) $(CFLAGS) -o $@ $^

%.o: %.c %.h
	$(GCC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) *.o *.x *.hex
