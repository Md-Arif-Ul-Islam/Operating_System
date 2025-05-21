#include <stdio.h>
#include <stdlib.h>

int main() {
    // 🔐 Your Firebase Server Key (replace with actual key)
    const char *server_key = "AAAA...your-server-key...";

    // 📱 Your device token (replace with real token)
    const char *device_token = "eK0...your-device-token...";

    // ✅ JSON message with format specifier for token
    char final_msg[2048];
    snprintf(final_msg, sizeof(final_msg),
        "{"
            "\"to\":\"%s\","
            "\"notification\":{"
                "\"title\":\"HELLO!\","
                "\"body\":\"This is a test notification from C.\""
            "}"
        "}", device_token);

    // 🔧 Build the curl command
    char command[4096];
    snprintf(command, sizeof(command),
        "curl -s -X POST https://fcm.googleapis.com/fcm/send "
        "-H \"Authorization: key=%s\" "
        "-H \"Content-Type: application/json\" "
        "-d '%s'",
        server_key, final_msg
    );

    printf("🚀 Sending Push Notification via Firebase Cloud Messaging...\n");
    system(command);
    printf("\n✅ Notification sent.\n");

    return 0;
}
