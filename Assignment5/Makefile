# DPLKYL002
# Makefile in ./Assignment5 project folder

TARGET = samp
CC = g++
CCFLAGS =-c -std=c++11
LDFLAGS =-lm
OBJECTS = Driver.o

$(TARGET):	$(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(TARGET)
	mv $(OBJECTS) bin

Driver.o: Driver.cpp Driver.h
	$(CC) $(CCFLAGS) Driver.cpp

clean:
	@rm bin/*.o
	@rm $(TARGET)
