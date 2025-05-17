#include <stdlib.h>
#include <stdio.h>
#include "swww.h"

void run_swww_command(const char *path, const char *transition, const char *duration) {
    if (!path || !transition || !duration) return;

    char command[1024];
    snprintf(command, sizeof(command),
             "swww img '%s' --transition-type %s --transition-duration %s",
             path, transition, duration);

    system(command);
}
