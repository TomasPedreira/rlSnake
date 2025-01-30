# Compiler and flags
CC = gcc

RAYLIB_PATH = C:/vcpkg/installed/x64-windows/
CFLAGS = -I$(RAYLIB_PATH)include -I./
LDFLAGS = -L$(RAYLIB_PATH)lib -lraylib -lopengl32 -lgdi32 -lwinmm

# Target and source files
TARGET = main
SRC = main.c

# Default rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS) $(LDFLAGS)

# Clean rule
clean:
	del $(TARGET).exe
