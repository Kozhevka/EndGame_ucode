# Define source files directory
SRC_DIR := src



# List all source files
SRCS := $(wildcard $(SRC_DIR)/*.c)

# List all header files
HEADERS := $(wildcard $(SRC_DIR)/*.h)

# Specify compiler
CC := gcc

# Specify compiler flags
CFLAGS := -I$(SRC_DIR) -I/SDL2 -L/SDL2/lib -lSDL2 -lSDL2_image -lSDL2_ttf

# Specify target
TARGET := mygame

# Compile target
$(TARGET): $(SRCS) $(HEADERS)
	$(CC) -o $@ $(SRCS) $(CFLAGS)

# Clean
clean:
	rm -f $(TARGET)