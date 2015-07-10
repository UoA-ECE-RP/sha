CC = gcc 
CFLAGS = -w 
INCLUDES = 
LDFLAGS = 
LIBS = 

TARGET = Watertank
C_SOURCES =  \
            Watertankrun.c  \
            Controler.c  \
            Watertank.c  \
            Plant.c 
RM = rm -f

.PHONY: all clean cleanall

all: $(TARGET)

$(TARGET): $(C_SOURCES) Makefile
	$(CC) $(CFLAGS) $(INCLUDES) $(C_SOURCES) $(LDFLAGS) $(LIBS) -o $(TARGET)

clean:
	$(RM) *.o

cleanall:
	$(RM) *.o
	$(RM) $(TARGET)
	$(RM) $(TARGET).exe
