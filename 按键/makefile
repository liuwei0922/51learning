mustclean = *.rel *.lst *.rst *.rsm *.sym *.asm *.map *.mem *.lk *.ihx
target = ../.hex/key_control.hex 

all: key_control.hex

key_control.hex: main.ihx
	packihx main.ihx > $(target)
main.ihx:main.c
	sdcc main.c

.PHONY:clean
clean: 
	-rm -rf $(mustclean)