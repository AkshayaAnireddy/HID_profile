#include <gio/gio.h>
#include <stdio.h>
#include "hid_service.h"
#include "hid_adv.h"

static GMainLoop *main_loop = NULL;

static void on_name_acquired(GDBusConnection *connection, const gchar *name, gpointer user_data) {
    g_print("Bus acquired: %s\n", name);

    // Register HID Service on D-Bus
    register_hid_service(connection);

    // Register Advertisement
    advertisement_register(connection);

    g_print("HID service registered on /org/example/HIDService\n");
}

static void on_name_lost(GDBusConnection *connection, const gchar *name, gpointer user_data) {
    g_print("Name lost: %s\n", name);
    // Stop main loop if name is lost
    if (main_loop != NULL) {
        g_main_loop_quit(main_loop);
    }
}

int main(int argc, char *argv[]) {
    g_print("Starting the HID service...\n");

    guint owner_id = g_bus_own_name(
        G_BUS_TYPE_SYSTEM,
        "org.example.HIDService",
        G_BUS_NAME_OWNER_FLAGS_NONE,
        NULL,
        on_name_acquired,
        on_name_lost,
        NULL,
        NULL
    );

    // 🧠 Start main loop so the program won't exit
    main_loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(main_loop);

    // Cleanup on exit
    g_bus_unown_name(owner_id);
    g_main_loop_unref(main_loop);

    return 0;
}

