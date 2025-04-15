#include "hid_service.h"
#include <gio/gio.h>
#include <glib.h>

static void on_method_call(GDBusConnection *connection,
                           const gchar *sender,
                           const gchar *object_path,
                           const gchar *interface_name,
                           const gchar *method_name,
                           GVariant *parameters,
                           GDBusMethodInvocation *invocation,
                           gpointer user_data) {

    g_print("Method call received: %s\n", method_name);
    g_dbus_method_invocation_return_value(invocation, NULL);
}

static const GDBusInterfaceVTable interface_vtable = {
    .method_call = on_method_call,
    .get_property = NULL,
    .set_property = NULL
};

void register_hid_service(GDBusConnection *connection) {
    GError *error = NULL;

    const gchar *interface_xml =
        "<node>"
        "  <interface name='org.example.HIDService'>"
        "    <method name='TestMethod'/>"
        "  </interface>"
        "</node>";

    GDBusNodeInfo *introspection_data = g_dbus_node_info_new_for_xml(interface_xml, &error);

    if (error) {
        g_printerr("Error parsing introspection XML: %s\n", error->message);
        g_error_free(error);
        return;
    }

    guint registration_id = g_dbus_connection_register_object(
        connection,
        "/org/example/HIDService",
        introspection_data->interfaces[0],
        &interface_vtable,
        NULL, NULL, NULL
    );

    if (registration_id == 0) {
        g_printerr("Failed to register object.\n");
    } else {
        g_print("HID service registered on /org/example/HIDService\n");
    }

    g_dbus_node_info_unref(introspection_data);
}

