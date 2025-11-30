#include "app.h"
#ifdef __linux__
#include <termios.h>
#include <unistd.h>
#endif

struct RawState {
#ifdef __linux__
    termios original;
#endif
    bool ready;
    bool active;
};

static RawState rawState = {};

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

static bool readByte(unsigned char* byte) {
#ifdef __linux__
    if (read(STDIN_FILENO, byte, 1) == 1)
        return true;
    return false;
#else
    (void)byte;
    return false;
#endif
}

static InputEvent makeEvent(Key key) {
    InputEvent evt;
    evt.isCharacter = false;
    evt.value = 0;
    evt.key = key;
    return evt;
}

InputEvent readInputEvent() {
    enableRawInput();
    InputEvent evt = makeEvent(KEY_NONE);
#ifdef __linux__
    unsigned char c;
    while (true) {
        if (!readByte(&c))
            continue;

        if (c == 27) {
            unsigned char seq[2];
            if (!readByte(&seq[0]))
                return makeEvent(KEY_ESC);
            if (!readByte(&seq[1]))
                return makeEvent(KEY_ESC);
            if (seq[0] == '[') {
                switch (seq[1]) {
                    case 'A': return makeEvent(KEY_UP);
                    case 'B': return makeEvent(KEY_DOWN);
                    case 'C': return makeEvent(KEY_RIGHT);
                    case 'D': return makeEvent(KEY_LEFT);
                    case 'H': return makeEvent(KEY_HOME);
                    case 'F': return makeEvent(KEY_END);
                    default: return makeEvent(KEY_OTHER);
                }
            }
            return makeEvent(KEY_ESC);
        }

        if (c == 127 || c == 8)
            return makeEvent(KEY_BACKSPACE);
        if (c == '\r' || c == '\n')
            return makeEvent(KEY_ENTER);

        evt.isCharacter = true;
        evt.value = static_cast<char>(c);
        evt.key = KEY_NONE;
        return evt;
    }
#else
    return evt;
#endif
}

Key getKey() {
    while (true) {
        InputEvent evt = readInputEvent();
        if (!evt.isCharacter)
            return evt.key;
        return KEY_OTHER;
    }
}
