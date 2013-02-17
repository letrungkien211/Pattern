CC = g++
RM = rm -f


CFLAGS	= -Wall -g -O2
INCLUDES= -I/usr/include/eigen3 

TARGET	= 2 3 4
OBJS = common.o
all:	$(TARGET)


$(TARGET): % : $(OBJS) %.o
	$(CC) $(CFLAGS) -o $@ $^

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $< 
clean:
	$(RM)  $(TARGET) $(OBJS) *.o *~ *#*
