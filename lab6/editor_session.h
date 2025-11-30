#ifndef EDITOR_SESSION_H
#define EDITOR_SESSION_H

#include "app.h"
#include "editor.h"

const int EDIT_VIEW_ROWS = 18;
const int EDIT_TOP = 0;
const int EDIT_LEFT = 0;
const int LINE_NUMBER_WIDTH = 3;
const int SEPARATOR_WIDTH = 3; // " | "
const int TEXT_START = EDIT_LEFT + LINE_NUMBER_WIDTH + SEPARATOR_WIDTH;
const int CURSOR_Y_OFFSET = 0;
const const char BLANK_LINE[] = "                                                                                ";

struct EditorSession {
    EditorBuffer* buffer;
    int cursorRow;
    int cursorCol;
    int scrollRow;
};

EditorSession* editorSessionCreate(int initialLines);
void editorSessionDestroy(EditorSession* session);

void editorSessionAdjustScroll(EditorSession* session);
void editorSessionDraw(const EditorSession* session);
bool editorSessionHandleEvent(EditorSession* session, const InputEvent* evt);

bool editorSessionHasUnsavedChanges(const EditorSession* session);
bool editorSessionSave(EditorSession* session, const char* path);
void editorSessionPromptToSave(EditorSession* session, const char* path);

#endif
