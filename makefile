CC = gcc
CFLAGS = -Wall -g `pkg-config --cflags glib-2.0 gio-2.0 dbus-1`
LIBS = `pkg-config --libs glib-2.0 gio-2.0 dbus-1`
TARGET = hogp_mouse
SRC = hid_main.c hid_service.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

