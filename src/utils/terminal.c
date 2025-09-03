#include <utils/terminal.h>

/// @brief Check if the local is UTF-8.
/// @return true/false
int terminal_supports_utf8(void){
    const char * loc = setlocale(LC_CTYPE, "");
    if (!loc) return 0;

    #if defined(_WIN32)
    return strstr(loc, ".65001") != NULL;
    #else
    return strstr(loc, "UTF-8") != NULL || strstr(loc, "utf8") != NULL;
    #endif
}