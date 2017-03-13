build:
	mkdir build
	avr-gcc -Os -mmcu=attiny2313 src/hw_layer.c src/protocol_layer.c src/uart.c src/main.c -o build/output.elf
	avr-objcopy -j .text -O ihex build/output.elf build/output.hex
clean:
	rm -r build
burn:
	avrdude -c usbasp -p t2313 -U flash:w:build/output.hex
all:
	make clean
	make build
	make burn
