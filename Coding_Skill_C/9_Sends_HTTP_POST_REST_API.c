#include <stdio.h>
#include <stdlib.h>

int main() {
    // ✅ Correct: must end with .json
    const char *firebase_url = ".............................................................................";

    const char *student_data = "{\"age\": 24, \"Course\": \"Computer Science\",\"name\": \"Farhan\"}";

    char command[1024];
    snprintf(command, sizeof(command),
             "curl -s -X POST -H \"Content-Type: application/json\" -d '%s' \"%s\"",
             student_data, firebase_url);

    printf("📤 Sending student data to Firebase...\n");
    system(command);
    printf("\n✅ Data sent successfully.\n");

    return 0;
}
