all:main.hex

main.hex:main.ihx
	packihx main.ihx > main.hex 

main.ihx:main.rel delay.rel nixietube.rel
	sdcc main.rel delay.rel nixietube.rel

main.rel:main.c delay.h nixietube.h 
	sdcc -c main.c
delay.rel: delay.c
	sdcc -c delay.c
nixietube.rel: nixietube.c
	sdcc -c nixietube.c

.PHONY: clean
clean: 
	rm -f *.rel *.lst *.rst *.rsm *.sym *.asm *.map *.mem *.lk *.ihx
