#include <gio/gio.h>
#include <glib.h>
#include "hid_service.h"

static void bus_acquired_handler(GDBusConnection *connection, const gchar *name, gpointer user_data) {
    g_print("Bus acquired: %s\n", name);
    register_hid_service(connection);  // Register your HID service
}

static void name_acquired_handler(GDBusConnection *connection, const gchar *name, gpointer user_data) {
    g_print("Name acquired: %s\n", name);
}

static void name_lost_handler(GDBusConnection *connection, const gchar *name, gpointer user_data) {
    g_print("Name lost: %s\n", name);
}

int main(int argc, char *argv[]) {
    guint owner_id;

    g_print("Starting the HID service...\n");

    owner_id = g_bus_own_name(
        G_BUS_TYPE_SYSTEM,
        "org.example.HIDService",
        G_BUS_NAME_OWNER_FLAGS_NONE,
        bus_acquired_handler,
        name_acquired_handler,
        name_lost_handler,
        NULL,
        NULL
    );

    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);

    g_bus_unown_name(owner_id);
    g_main_loop_unref(loop);

    return 0;
}

