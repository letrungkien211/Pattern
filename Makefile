CC = g++
RM = rm -f


CFLAGS	= -Wall -g -O2
INCLUDES= -I/usr/include/eigen3 

TARGET	= 2
all:	$(TARGET)


$(TARGET): % :  %.o
	$(CC) $(CFLAGS) -o $@ $^

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $< 
clean:
	$(RM)  $(TARGET) *.o *~



