CC=avr-gcc
LD=avr-gcc
OBJCOPY=avr-objcopy
AVRDUDE=avrdude
CCFLAGS=-pedantic -std=c99 -Os -mmcu=attiny24
LDFLAGS=-mmcu=attiny24
OBJS=main.o
TARGET=gameport2amiga
SERIALPORT=/dev/ttyS0

# all target... Builds elf binary
all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(TARGET)

main.o: main.c
	$(CC) $(CCFLAGS) main.c -c


$(TARGET).hex: $(TARGET)
	$(OBJCOPY) -O ihex -R .eeprom $(TARGET) $(TARGET).hex

# flashes project to device
flash: $(TARGET).hex
	$(AVRDUDE) -p t24 -c siprog -P $(SERIALPORT) -U flash:w:$(TARGET).hex
#	$(AVRDUDE) -p t24 -c siprog -C /etc/avrdude/avrdude.conf -P $(SERIALPORT) -U flash:w:$(TARGET).hex

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).hex
