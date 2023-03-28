CC = g++
CFLAGS  = -g -Wall
TARGET = HuffmanCoding

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp
	
clean:
	$(RM) $(TARGET)

run:	${TARGET}
		./${TARGET} ${ARGS}
