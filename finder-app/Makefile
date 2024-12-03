# Cross compile is done by just concatenating compilers
# Source: https://stackoverflow.com/questions/37866783/how-to-modify-makefile-to-support-cross-compilation
CC = $(CROSS_COMPILE)gcc
CFLAGS = -Wall -Wextra -g
# Default target which builds writer application
TARGET = writer

# Default target to build the application
all: $(TARGET)

# Build the writer application
$(TARGET): writer.o
	$(CC) $(CFLAGS) -o $(TARGET) writer.o

# Compile the writer.o object file
writer.o: writer.c
	$(CC) $(CFLAGS) -c writer.c -o writer.o

# Clean target to remove binaries and object files
clean:
	rm -f $(TARGET) *.o
