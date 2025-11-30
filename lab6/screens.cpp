#include "screens.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "editor_session.h"
#include "../lab1/terminal.h"
#include "../lab4/stringlib.h"

using namespace std;

static const char* OUTPUT_FILE = "output.text";

static void drawButton(int y, const char* label, bool selected) {
    goToXY(20, y);
    if (selected) {
        setColor(COLOR_YELLOW);
        cout << "->" << "{ " << label << " }";
        resetColor();
    } else {
        cout << "{ " << label << " }";
    }
}

void drawMenu(MenuItem current) {
    clearScreen();
    goToXY(20, 5);
    cout << "Main Menu";
    drawButton(7, "New", current == MENU_NEW);
    drawButton(9, "Display", current == MENU_DISPLAY);
    drawButton(11, "Exit", current == MENU_EXIT);
    goToXY(0, 20);
}

void exitScreen() {
    clearScreen();
    goToXY(20, 5);
    cout << "Bye Bye!";
    goToXY(28, 5);
    delay(1500);
    disableRawInput();
    clearScreen();
    exit(0);
}

void screenNew() {
    EditorSession* session = editorSessionCreate(32);
    if (session == nullptr) {
        clearScreen();
        goToXY(10, 5);
        cout << "Unable to start editor (no memory).";
        delay(1500);
        return;
    }

    bool editing = true;

    while (editing) {
        editorSessionAdjustScroll(session);
        editorSessionDraw(session);
        InputEvent evt = readInputEvent();
        editing = editorSessionHandleEvent(session, &evt);
    }

    if (editorSessionHasUnsavedChanges(session)) {
        editorSessionAdjustScroll(session);
        editorSessionDraw(session);
        editorSessionPromptToSave(session, OUTPUT_FILE);
    } else {
        editorSessionAdjustScroll(session);
        editorSessionDraw(session);
        int messageRow = EDIT_TOP + EDIT_VIEW_ROWS + 1;
        goToXY(EDIT_LEFT, messageRow);
        cout << BLANK_LINE;
        goToXY(EDIT_LEFT, messageRow);
        cout << "No changes to save.";
        cout.flush();
        delay(800);
    }

    editorSessionDestroy(session);
}

void screenDisplay() {
    bool fileOpened = false;
    vector<string> lines;
    FILE* file = fopen(OUTPUT_FILE, "r");
    if (file != nullptr) {
        fileOpened = true;
        char line[512];
        while (fgets(line, sizeof(line), file) != nullptr) {
            int len = str_len(line);
            while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
                line[len - 1] = '\0';
                len--;
            }
            lines.emplace_back(line);
        }
        fclose(file);
    }

    int totalLines = static_cast<int>(lines.size());
    int scrollRow = 0;

    auto drawDisplay = [&](void) {
        clearScreen();
        for (int i = 0; i < EDIT_VIEW_ROWS; ++i) {
            int y = EDIT_TOP + i;
            goToXY(EDIT_LEFT, y);
            cout << BLANK_LINE;
            goToXY(EDIT_LEFT, y);
            int lineIndex = scrollRow + i;
            if (lineIndex < totalLines) {
                int label = lineIndex + 1;
                char number[12];
                snprintf(number, sizeof(number), "%3d", label);
                cout << number << " | " << lines[lineIndex];
            }
        }

        int statusRow = EDIT_TOP + EDIT_VIEW_ROWS + 1;
        goToXY(EDIT_LEFT, statusRow);
        cout << BLANK_LINE;
        goToXY(EDIT_LEFT, statusRow);
        if (!fileOpened)
            cout << "Unable to open " << OUTPUT_FILE;
        else if (totalLines == 0)
            cout << OUTPUT_FILE << " is empty.";
        else {
            int endLine = scrollRow + EDIT_VIEW_ROWS;
            if (endLine > totalLines)
                endLine = totalLines;
            cout << "Lines: " << totalLines << "  Showing " << scrollRow + 1 << "-" << endLine;
        }

        goToXY(EDIT_LEFT, statusRow + 2);
        cout << BLANK_LINE;
        goToXY(EDIT_LEFT, statusRow + 2);
        if (!fileOpened)
            cout << "Press ESC to return to main menu.";
        else
            cout << "Use UP/DOWN to scroll, ESC to return.";
    };

    drawDisplay();

    while (true) {
        Key k = getKey();
        if (k == KEY_ESC || k == KEY_LEFT)
            break;
        if (!fileOpened || totalLines <= EDIT_VIEW_ROWS)
            continue;
        if (k == KEY_UP && scrollRow > 0) {
            scrollRow--;
            drawDisplay();
        } else if (k == KEY_DOWN && scrollRow + EDIT_VIEW_ROWS < totalLines) {
            scrollRow++;
            drawDisplay();
        } else if (k == KEY_END) {
            int newScroll = totalLines - EDIT_VIEW_ROWS;
            if (newScroll < 0)
                newScroll = 0;
            if (newScroll != scrollRow) {
                scrollRow = newScroll;
                drawDisplay();
            }
        } else if (k == KEY_HOME) {
            if (scrollRow != 0) {
                scrollRow = 0;
                drawDisplay();
            }
        }
    }
}
