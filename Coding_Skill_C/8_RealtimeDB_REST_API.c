#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

// Structure to hold the response data
struct MemoryStruct {
    char *memory;
    size_t size;
};

// Callback function for curl to write data into memory
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (ptr == NULL) {
        printf("❌ Not enough memory!\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

int main() {
    CURL *curl;
    CURLcode res;

    struct MemoryStruct chunk;
    chunk.memory = malloc(1);  // initial allocation
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {
        // 🌐 Replace this with your actual Firebase Realtime Database URL + .json
        const char *url = "............................................................";

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        printf("📥 Fetching student data from Firebase...\n");

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "❌ curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            // ✅ Parse JSON response
            cJSON *json = cJSON_Parse(chunk.memory);
            if (!cJSON_IsObject(json)) {
                printf("❌ Failed to parse JSON or unexpected format\n");
            } else {
                printf("\n✅ Student List:\n");

                cJSON *student = NULL;
                cJSON_ArrayForEach(student, json) {
                    cJSON *name = cJSON_GetObjectItem(student, "name");
                    cJSON *age = cJSON_GetObjectItem(student, "age");
                    cJSON *course = cJSON_GetObjectItem(student, "course");

                    if (name && age) {
                        printf("👤 Name: %s\n", name->valuestring);
                        printf("🎂 Age: %d\n", age->valueint);
                        if (course && course->valuestring)
                            printf("📚 Course: %s\n", course->valuestring);
                        else
                            printf("📚 Course: N/A\n");
                        printf("------------------------\n");
                    }
                }

                cJSON_Delete(json);
            }
        }

        curl_easy_cleanup(curl);
    }

    free(chunk.memory);
    curl_global_cleanup();

    return 0;
}
