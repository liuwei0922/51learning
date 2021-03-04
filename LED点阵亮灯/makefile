mustclean = *.rel *.lst *.rst *.rsm *.sym *.asm *.map *.mem *.lk *.ihx
all:main.hex

main.hex:main.ihx
	packihx main.ihx > main.hex 

main.ihx:main.rel 
	sdcc main.rel 

main.rel:main.c 
	sdcc -c main.c


.PHONY: clean
clean: 
	-rm -f $(mustclean)