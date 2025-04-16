#ifndef HID_ADV_H
#define HID_ADV_H

#include <gio/gio.h>

// Function declarations for advertisement registration/unregistration
void advertisement_register(GDBusConnection *connection);
void advertisement_unregister(GDBusConnection *connection);

// Function declarations for starting and stopping advertisements
static void start_advertisement(GDBusConnection *connection);
static void stop_advertisement(GDBusConnection *connection);

#endif

