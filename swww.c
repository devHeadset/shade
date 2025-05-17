#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void run_swww_command(const char *path, const char *transition, const char *duration) {
    if (!path || !transition || !duration) return;

    char fullpath[1024];

    if (path[0] == '~') {
        const char *home = getenv("HOME");
        if (!home) home = "";
        snprintf(fullpath, sizeof(fullpath), "%s%s", home, path + 1);
    } else {
        snprintf(fullpath, sizeof(fullpath), "%s", path);
    }

    char command[2048];
    snprintf(command, sizeof(command),
             "swww img '%s' --transition-type %s --transition-duration %s",
             fullpath, transition, duration);

    system(command);
}
