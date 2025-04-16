# Specify the required packages for compiling and linking
PKG_CONFIG_PACKAGES = gio-2.0 glib-2.0 dbus-1 bluez

# Compiler flags and linking options based on pkg-config
CFLAGS = -g -Wall -std=c99 `pkg-config --cflags $(PKG_CONFIG_PACKAGES)`
LIBS = `pkg-config --libs $(PKG_CONFIG_PACKAGES)`

# The default target, which builds the executable
all: hid_program

# Build the executable using the object files
hid_program: hid_service.o hid_adv.o hid_main.o
	$(CC) -o $@ $^ $(LIBS)

# Build object files for each C source file
hid_service.o: hid_service.c
	$(CC) -c $< -o $@ $(CFLAGS)

hid_adv.o: hid_adv.c
	$(CC) -c $< -o $@ $(CFLAGS)

hid_main.o: hid_main.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Clean up generated files
clean:
	rm -f *.o hid_program

