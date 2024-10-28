CC = gcc
CFLAGS = -Wall -g

TARGET = program

SRC = main.c  

ifdef FILE
    SRC = $(FILE)
endif

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)
	
.PHONY: all run clean
