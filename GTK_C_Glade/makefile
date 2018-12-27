#change application name here (executable output name)
TARGET=hkspin
 
# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall
  
PTHREAD=-pthread
   
CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe

GTKLIB=`pkg-config --cflags --libs gtk+-3.0`

PICONF = -lwiringPi
    
# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) $(PICONF) -lm -export-dynamic

OBJS=main.o buttons.o


all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)

buttons.o: src/buttons.c src/buttons.h
	$(CC) -c $(CCFLAGS) src/buttons.c $(GTKLIB) $(PICONF)

main.o: src/main.c src/buttons.h
	$(CC) -c $(CCFLAGS) src/main.c $(GTKLIB) $(PICONF)

clean:
	rm -f *.o $(TARGET)



