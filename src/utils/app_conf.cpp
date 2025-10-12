#include "app_conf.hpp"
#include <cstdio>

char app::Ver::buffer[64] ;

const char *app::Ver::string() {
    snprintf(buffer, sizeof(buffer), "%d.%d.%d%s", MAIN, MAJOR, MINOR, SNAPSHOT ? " SNAPSHOT" : "") ;
    return buffer ;
}