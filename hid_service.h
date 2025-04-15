#ifndef HID_SERVICE_H
#define HID_SERVICE_H

#include <gio/gio.h>

void register_hid_service(GDBusConnection *connection);

#endif

