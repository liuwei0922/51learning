vpath %.c ../src
vpath %.h ../include
headers = nixietube.h
mustclean = *.rel *.lst *.rst *.rsm *.sym *.asm *.map *.mem *.lk *.ihx
targetname =URAT_communication.hex
CC = sdcc 
all:$(targetname)

$(targetname): main.ihx 
	packihx main.ihx  >  ../.hex/$(targetname)
main.ihx : $(subst .h,.rel,$(headers))  main.rel 
	$(CC)  main.rel $(subst .h,.rel,$(headers))  
%.rel: %.c 
	$(CC)  -c $<
main.rel : main.c $(headers)
	$(CC)  -c main.c
.PHONY:clean
clean: 
	-rm -rf $(mustclean)
