# HID over GATT Profile - Mouse

This project implements a Bluetooth HID over GATT Profile (HOGP) for a mouse device on Linux using BlueZ, GLib, and D-Bus.

## Features
- Registers HID Service, Report Map, Input Report, and Report Reference Descriptor.
- Registers LE Advertisement using `LEAdvertisingManager1` interface.
- Follows the HID over GATT (HOGP) specification.

## Build

```bash
sudo apt-get install libglib2.0-dev libgio2.0-dev libdbus-1-dev
make

