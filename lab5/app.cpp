#include "app.h"
#ifdef __linux__
#include <termios.h>
#include <unistd.h>

struct RawState {
    termios original;
    bool ready;
    bool active;
};

static RawState rawState = {};
#endif

static void prepareRawMode() {
#ifdef __linux__
    if (!rawState.ready) {
        tcgetattr(STDIN_FILENO, &rawState.original);
        rawState.ready = true;
        rawState.active = false;
    }
#endif
}

void enableRawInput() {
#ifdef __linux__
    prepareRawMode();
    if (!rawState.active) {
        termios raw = rawState.original;
        raw.c_lflag &= ~(ICANON | ECHO);
        raw.c_cc[VMIN] = 0;
        raw.c_cc[VTIME] = 1;
        tcsetattr(STDIN_FILENO, TCSANOW, &raw);
        rawState.active = true;
    }
#endif
}

void disableRawInput() {
#ifdef __linux__
    if (rawState.ready && rawState.active) {
        tcsetattr(STDIN_FILENO, TCSANOW, &rawState.original);
        rawState.active = false;
    }
#endif
}

#ifdef __linux__
Key readLinuxKey() {
    unsigned char c;

    
    if (read(STDIN_FILENO, &c, 1) != 1)
        return KEY_NONE;

    // 27 is ESC
    if (c == 27) {
        
        unsigned char seq[2];

        // If no more bytes then input is an ESC
        if (read(STDIN_FILENO, &seq[0], 1) != 1)
            return KEY_ESC;

        if (read(STDIN_FILENO, &seq[1], 1) != 1)
            return KEY_ESC; 

        // If there is 2 bytes then the format is  ESC [ X
        if (seq[0] == '[') {
            switch (seq[1]) {
                case 'A': return KEY_UP;
                case 'B': return KEY_DOWN;
                case 'C': return KEY_RIGHT;
                case 'D': return KEY_LEFT;
                case 'H': return KEY_HOME;
                case 'F': return KEY_END;
                default: return KEY_OTHER;
            }
        }

        return KEY_OTHER;
    }

    return KEY_OTHER;
}
#endif

Key getKey() {
#ifdef __linux__
    enableRawInput();
    return readLinuxKey();
#else
    return KEY_NONE;
#endif
}
