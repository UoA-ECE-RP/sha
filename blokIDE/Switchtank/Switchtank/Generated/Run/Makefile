CC = gcc 
CFLAGS = -w 
INCLUDES = 
LDFLAGS = 
LIBS = 

TARGET = Switchtank
C_SOURCES =  \
            Switchtankrun.c  \
            Switchtank.c  \
            Plant.c  \
            Controller.c 
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
