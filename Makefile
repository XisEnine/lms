# Compiler and flags
CC = gcc-14
CFLAGS = -Wall -I./src/headerfile

# Source files
SRCS = src/lib/hashTableAdmin.c src/lib/hashTableGuest.c src/main/main.c
OBJS = $(SRCS:.c=.o)  # Create object files from source files

# Output executable name
TARGET = libraryApp

# Default target: compile the executable
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Clean build files
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all run clean
