#ifndef EDITOR_H
#define EDITOR_H

#include <stdbool.h>

struct EditorBuffer;
typedef struct EditorBuffer EditorBuffer;

EditorBuffer* editorCreate(int initialLines);
void editorDestroy(EditorBuffer* buffer);
void editorReset(EditorBuffer* buffer);
bool editorInsertChar(EditorBuffer* buffer, int row, int col, char ch);
bool editorInsertNewLine(EditorBuffer* buffer, int* row, int* col);
bool editorBackspace(EditorBuffer* buffer, int* row, int* col);
int editorLineLength(const EditorBuffer* buffer, int row);
const char* editorLineText(const EditorBuffer* buffer, int row);
int editorLineCount(const EditorBuffer* buffer);
void editorMoveCursorLeft(const EditorBuffer* buffer, int* row, int* col);
void editorMoveCursorRight(const EditorBuffer* buffer, int* row, int* col);
void editorMoveCursorUp(const EditorBuffer* buffer, int* row, int* col);
void editorMoveCursorDown(const EditorBuffer* buffer, int* row, int* col);
bool editorSaveToFile(const EditorBuffer* buffer, const char* path);
bool editorIsDirty(const EditorBuffer* buffer);
void editorMarkClean(EditorBuffer* buffer);

#endif
