/*
*   Filesystem and data parsing
*/

#include <stdlib.h>
#include <string.h>
#include <cJSON.h>
#include <cJSON.c>
#include <fstream>
#include <sstream>

#include <animations.hpp>

int read_file(char **data, const char *path) {
    std::ifstream file(path);
    if (file.good()) {
        std::stringstream ss;
        std::string tmp;
        while (std::getline(file, tmp)) {
            ss << tmp << std::endl;
        }

        tmp = ss.str();
        const char *str = tmp.c_str();
        asprintf(data, str);

        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}

Animation load_animation(const char *json_string) {
    Animation ret = {
        DEFAULT_FPS,
        {}
    };

    cJSON *data = cJSON_ParseWithLength(json_string, strlen(json_string));
    cJSON *item_fps = cJSON_GetObjectItem(data, "fps");
    cJSON *item_frames = cJSON_GetObjectItem(data, "frames");

    const int fps = cJSON_GetNumberValue(item_fps);
    if (fps > 0) {
        ret.framerate = fps;
    }

    int size = cJSON_GetArraySize(item_frames);
    cJSON *item_frame;
    for (int i=0; i<size; i++) {
        item_frame = cJSON_GetArrayItem(item_frames, i);
        if (item_frame != NULL) {
            ret.frames.push_back(cJSON_GetStringValue(item_frame));
        }
    }

    return ret;
}
