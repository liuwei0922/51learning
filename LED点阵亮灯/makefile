mustclean = *.rel *.lst *.rst *.rsm *.sym *.asm *.map *.mem *.lk *.ihx
all:main.hex

main.hex:main.ihx
	packihx main.ihx > main.hex 

main.ihx:main.rel hc595.rel 
	sdcc main.rel 

main.rel:main.c 
	sdcc -c main.c
hc595.rel: hc595.c
	sdcc -c hc595.c 

.PHONY: clean
clean: 
	-rm -f $(mustclean)