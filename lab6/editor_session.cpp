#include "editor_session.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <new>
#include "../lab1/terminal.h"
#include "../lab4/stringlib.h"

using namespace std;

static void showPromptLine(const char* message, int y) {
    goToXY(EDIT_LEFT, y);
    cout << BLANK_LINE;
    goToXY(EDIT_LEFT, y);
    if (message != nullptr)
        cout << message;
    cout.flush();
}

EditorSession* editorSessionCreate(int initialLines) {
    EditorBuffer* buffer = editorCreate(initialLines);
    if (buffer == nullptr)
        return nullptr;

    EditorSession* session = new (std::nothrow) EditorSession;
    if (session == nullptr) {
        editorDestroy(buffer);
        return nullptr;
    }

    session->buffer = buffer;
    session->cursorRow = 0;
    session->cursorCol = 0;
    session->scrollRow = 0;
    return session;
}

void editorSessionDestroy(EditorSession* session) {
    if (session == nullptr)
        return;
    editorDestroy(session->buffer);
    delete session;
}

void editorSessionAdjustScroll(EditorSession* session) {
    if (session == nullptr || session->buffer == nullptr)
        return;
    if (session->cursorRow < session->scrollRow)
        session->scrollRow = session->cursorRow;
    else if (session->cursorRow >= session->scrollRow + EDIT_VIEW_ROWS)
        session->scrollRow = session->cursorRow - EDIT_VIEW_ROWS + 1;
    if (session->scrollRow < 0)
        session->scrollRow = 0;
}

void editorSessionDraw(const EditorSession* session) {
    if (session == nullptr || session->buffer == nullptr)
        return;

    clearScreen();

    int totalLines = editorLineCount(session->buffer);
    for (int i = 0; i < EDIT_VIEW_ROWS; ++i) {
        int y = EDIT_TOP + i;
        goToXY(EDIT_LEFT, y);
        cout << BLANK_LINE;
        goToXY(EDIT_LEFT, y);
        int lineIndex = session->scrollRow + i;
        if (lineIndex < totalLines) {
            int label = lineIndex + 1;
            char number[12];
            snprintf(number, sizeof(number), "%3d", label);
            cout << number << " | " << editorLineText(session->buffer, lineIndex);
        }
    }

    int statusRow = EDIT_TOP + EDIT_VIEW_ROWS + 1;
    goToXY(EDIT_LEFT, statusRow);
    cout << BLANK_LINE;
    goToXY(EDIT_LEFT, statusRow);
    cout << "Lines: " << totalLines << "  Cursor: " << session->cursorRow + 1 << "," << session->cursorCol + 1;

    int cursorScreenRow = EDIT_TOP + (session->cursorRow - session->scrollRow) + CURSOR_Y_OFFSET;
    int minCursorRow = EDIT_TOP + CURSOR_Y_OFFSET;
    int maxCursorRow = EDIT_TOP + EDIT_VIEW_ROWS - 1 + CURSOR_Y_OFFSET;
    if (cursorScreenRow < minCursorRow)
        cursorScreenRow = minCursorRow;
    else if (cursorScreenRow > maxCursorRow)
        cursorScreenRow = maxCursorRow;
    goToXY(TEXT_START + session->cursorCol, cursorScreenRow);
    cout.flush();
}

static void handleCharacterInput(EditorSession* session, char value) {
    if (value < 32 || value > 126)
        return;
    if (editorInsertChar(session->buffer, session->cursorRow, session->cursorCol, value))
        session->cursorCol++;
}

bool editorSessionHandleEvent(EditorSession* session, const InputEvent* evt) {
    if (session == nullptr || evt == nullptr)
        return true;
    if (evt->isCharacter) {
        handleCharacterInput(session, evt->value);
        return true;
    }
    switch (evt->key) {
        case KEY_LEFT:
            editorMoveCursorLeft(session->buffer, &session->cursorRow, &session->cursorCol);
            break;
        case KEY_RIGHT:
            editorMoveCursorRight(session->buffer, &session->cursorRow, &session->cursorCol);
            break;
        case KEY_UP:
            editorMoveCursorUp(session->buffer, &session->cursorRow, &session->cursorCol);
            break;
        case KEY_DOWN:
            editorMoveCursorDown(session->buffer, &session->cursorRow, &session->cursorCol);
            break;
        case KEY_HOME:
            session->cursorCol = 0;
            break;
        case KEY_END:
            session->cursorCol = editorLineLength(session->buffer, session->cursorRow);
            break;
        case KEY_BACKSPACE:
            editorBackspace(session->buffer, &session->cursorRow, &session->cursorCol);
            break;
        case KEY_ENTER:
            if (editorInsertNewLine(session->buffer, &session->cursorRow, &session->cursorCol))
                session->cursorCol = 0;
            break;
        case KEY_ESC:
            return false;
        default:
            break;
    }
    return true;
}

bool editorSessionHasUnsavedChanges(const EditorSession* session) {
    if (session == nullptr || session->buffer == nullptr)
        return false;
    return editorIsDirty(session->buffer);
}

bool editorSessionSave(EditorSession* session, const char* path) {
    if (session == nullptr || session->buffer == nullptr || path == nullptr)
        return false;
    bool saved = editorSaveToFile(session->buffer, path);
    if (saved)
        editorMarkClean(session->buffer);
    return saved;
}

void editorSessionPromptToSave(EditorSession* session, const char* path) {
    if (session == nullptr || path == nullptr)
        return;

    int promptRow = EDIT_TOP + EDIT_VIEW_ROWS + 1;
    showPromptLine("Save changes? (s = save, d = discard)", promptRow);

    while (true) {
        InputEvent evt = readInputEvent();
        if (!evt.isCharacter)
            continue;
        char c = evt.value;
        if (c == 's' || c == 'S' || c == 'y' || c == 'Y') {
            bool saved = editorSessionSave(session, path);
            showPromptLine(saved ? "Saved successfully." : "Failed to save.", promptRow + 1);
            delay(1200);
            return;
        }
        if (c == 'd' || c == 'D' || c == 'n' || c == 'N') {
            showPromptLine("Changes discarded.", promptRow + 1);
            delay(800);
            return;
        }
    }
}
