mustclean = *.rel *.lst *.rst *.rsm *.sym *.asm *.map *.mem *.lk *.ihx
romote = ../.hex/LedsToLight.hex 
all:LedsToLight.hex

LedsToLight.hex:main.ihx
	packihx main.ihx > $(romote)

main.ihx:main.rel hc595.rel 
	sdcc main.rel hc595.rel 

main.rel:main.c hc595.h 
	sdcc -c main.c
hc595.rel: hc595.c
	sdcc -c hc595.c 

.PHONY: clean
clean: 
	-rm -f $(mustclean)