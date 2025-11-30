#include "editor.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

struct EditorBuffer {
    char** lines;
    int lineCount;
    int lineCapacity;
    bool dirty;
};

static int safeLength(const char* text) {
    if (text == nullptr)
        return 0;
    return static_cast<int>(strlen(text));
}

static char* makeText(const char* src, int length) {
    if (length < 0)
        length = 0;
    char* text = static_cast<char*>(malloc(static_cast<size_t>(length + 1)));
    if (text == nullptr)
        return nullptr;
    if (src != nullptr && length > 0)
        memcpy(text, src, static_cast<size_t>(length));
    text[length] = '\0';
    return text;
}

static bool ensureLineCapacity(EditorBuffer* buffer, int required) {
    if (buffer == nullptr)
        return false;
    if (required <= buffer->lineCapacity)
        return true;
    int newCapacity = buffer->lineCapacity > 0 ? buffer->lineCapacity : 4;
    while (newCapacity < required)
        newCapacity *= 2;
    char** resized = static_cast<char**>(realloc(buffer->lines, static_cast<size_t>(newCapacity) * sizeof(char*)));
    if (resized == nullptr)
        return false;
    buffer->lines = resized;
    buffer->lineCapacity = newCapacity;
    return true;
}

static bool appendEmptyLine(EditorBuffer* buffer) {
    if (!ensureLineCapacity(buffer, buffer->lineCount + 1))
        return false;
    buffer->lines[buffer->lineCount] = makeText("", 0);
    if (buffer->lines[buffer->lineCount] == nullptr)
        return false;
    buffer->lineCount++;
    return true;
}

static bool insertLine(EditorBuffer* buffer, int index, char* text) {
    if (buffer == nullptr || text == nullptr)
        return false;
    if (index < 0 || index > buffer->lineCount) {
        free(text);
        return false;
    }
    if (!ensureLineCapacity(buffer, buffer->lineCount + 1)) {
        free(text);
        return false;
    }
    for (int i = buffer->lineCount; i > index; --i)
        buffer->lines[i] = buffer->lines[i - 1];
    buffer->lines[index] = text;
    buffer->lineCount++;
    return true;
}

static void removeLine(EditorBuffer* buffer, int index) {
    if (buffer == nullptr)
        return;
    if (buffer->lineCount <= 1)
        return;
    if (index < 0 || index >= buffer->lineCount)
        return;
    free(buffer->lines[index]);
    for (int i = index; i < buffer->lineCount - 1; ++i)
        buffer->lines[i] = buffer->lines[i + 1];
    buffer->lineCount--;
}

static char* getLine(EditorBuffer* buffer, int row) {
    if (buffer == nullptr)
        return nullptr;
    if (row < 0 || row >= buffer->lineCount)
        return nullptr;
    return buffer->lines[row];
}

static const char* getLine(const EditorBuffer* buffer, int row) {
    if (buffer == nullptr)
        return nullptr;
    if (row < 0 || row >= buffer->lineCount)
        return nullptr;
    return buffer->lines[row];
}

EditorBuffer* editorCreate(int initialLines) {
    if (initialLines <= 0)
        initialLines = 4;
    EditorBuffer* buffer = static_cast<EditorBuffer*>(malloc(sizeof(EditorBuffer)));
    if (buffer == nullptr)
        return nullptr;
    buffer->lines = nullptr;
    buffer->lineCount = 0;
    buffer->lineCapacity = 0;
    buffer->dirty = false;
    if (!ensureLineCapacity(buffer, initialLines)) {
        free(buffer);
        return nullptr;
    }
    if (!appendEmptyLine(buffer)) {
        free(buffer->lines);
        free(buffer);
        return nullptr;
    }
    return buffer;
}

void editorDestroy(EditorBuffer* buffer) {
    if (buffer == nullptr)
        return;
    if (buffer->lines != nullptr) {
        for (int i = 0; i < buffer->lineCount; ++i)
            free(buffer->lines[i]);
        free(buffer->lines);
    }
    free(buffer);
}

void editorReset(EditorBuffer* buffer) {
    if (buffer == nullptr)
        return;
    for (int i = 0; i < buffer->lineCount; ++i)
        free(buffer->lines[i]);
    buffer->lineCount = 0;
    appendEmptyLine(buffer);
    buffer->dirty = false;
}

int editorLineLength(const EditorBuffer* buffer, int row) {
    const char* line = getLine(buffer, row);
    return safeLength(line);
}

const char* editorLineText(const EditorBuffer* buffer, int row) {
    const char* line = getLine(buffer, row);
    if (line == nullptr)
        return "";
    return line;
}

int editorLineCount(const EditorBuffer* buffer) {
    if (buffer == nullptr)
        return 0;
    return buffer->lineCount;
}

bool editorInsertChar(EditorBuffer* buffer, int row, int col, char ch) {
    char* line = getLine(buffer, row);
    if (line == nullptr)
        return false;
    int len = safeLength(line);
    if (col < 0)
        col = 0;
    if (col > len)
        col = len;
    char* grown = static_cast<char*>(realloc(line, static_cast<size_t>(len + 2)));
    if (grown == nullptr)
        return false;
    buffer->lines[row] = grown;
    line = grown;
    memmove(line + col + 1, line + col, static_cast<size_t>(len - col + 1));
    line[col] = ch;
    buffer->dirty = true;
    return true;
}

bool editorInsertNewLine(EditorBuffer* buffer, int* row, int* col) {
    if (buffer == nullptr || row == nullptr || col == nullptr)
        return false;
    char* line = getLine(buffer, *row);
    if (line == nullptr)
        return false;
    int len = safeLength(line);
    if (*col < 0)
        *col = 0;
    if (*col > len)
        *col = len;
    int headLen = *col;
    int tailLen = len - headLen;
    char* tail = makeText(line + headLen, tailLen);
    if (tail == nullptr)
        return false;
    char* head = makeText(line, headLen);
    if (head == nullptr) {
        free(tail);
        return false;
    }
    if (!insertLine(buffer, *row + 1, tail)) {
        free(tail);
        free(head);
        return false;
    }
    free(buffer->lines[*row]);
    buffer->lines[*row] = head;
    (*row)++;
    *col = 0;
    buffer->dirty = true;
    return true;
}

bool editorBackspace(EditorBuffer* buffer, int* row, int* col) {
    if (buffer == nullptr || row == nullptr || col == nullptr)
        return false;
    if (*row < 0 || *row >= editorLineCount(buffer))
        return false;
    char* line = getLine(buffer, *row);
    if (line == nullptr)
        return false;
    int len = safeLength(line);
    if (*col > len)
        *col = len;
    if (*col > 0) {
        memmove(line + *col - 1, line + *col, static_cast<size_t>(len - *col + 1));
        (*col)--;
        buffer->dirty = true;
        return true;
    }
    if (*col == 0 && *row > 0) {
        char* prev = getLine(buffer, *row - 1);
        if (prev == nullptr)
            return false;
        int prevLen = safeLength(prev);
        char* merged = static_cast<char*>(realloc(prev, static_cast<size_t>(prevLen + len + 1)));
        if (merged == nullptr)
            return false;
        memcpy(merged + prevLen, line, static_cast<size_t>(len + 1));
        buffer->lines[*row - 1] = merged;
        removeLine(buffer, *row);
        (*row)--;
        *col = prevLen;
        buffer->dirty = true;
        return true;
    }
    return false;
}

void editorMoveCursorLeft(const EditorBuffer* buffer, int* row, int* col) {
    if (buffer == nullptr || row == nullptr || col == nullptr)
        return;
    if (*col > 0) {
        (*col)--;
        return;
    }
    if (*row > 0) {
        (*row)--;
        *col = editorLineLength(buffer, *row);
    }
}

void editorMoveCursorRight(const EditorBuffer* buffer, int* row, int* col) {
    if (buffer == nullptr || row == nullptr || col == nullptr)
        return;
    int len = editorLineLength(buffer, *row);
    if (*col < len) {
        (*col)++;
        return;
    }
    if (*row + 1 < editorLineCount(buffer)) {
        (*row)++;
        *col = 0;
    }
}

void editorMoveCursorUp(const EditorBuffer* buffer, int* row, int* col) {
    if (buffer == nullptr || row == nullptr || col == nullptr)
        return;
    if (*row > 0) {
        (*row)--;
        int len = editorLineLength(buffer, *row);
        if (*col > len)
            *col = len;
    }
}

void editorMoveCursorDown(const EditorBuffer* buffer, int* row, int* col) {
    if (buffer == nullptr || row == nullptr || col == nullptr)
        return;
    if (*row + 1 < editorLineCount(buffer)) {
        (*row)++;
        int len = editorLineLength(buffer, *row);
        if (*col > len)
            *col = len;
    }
}

bool editorSaveToFile(const EditorBuffer* buffer, const char* path) {
    if (buffer == nullptr || path == nullptr)
        return false;
    FILE* file = fopen(path, "w");
    if (file == nullptr)
        return false;
    for (int i = 0; i < buffer->lineCount; ++i) {
        const char* text = getLine(buffer, i);
        if (text != nullptr && *text != '\0')
            fwrite(text, sizeof(char), static_cast<size_t>(safeLength(text)), file);
        if (i < buffer->lineCount - 1)
            fputc('\n', file);
    }
    fclose(file);
    return true;
}

bool editorIsDirty(const EditorBuffer* buffer) {
    if (buffer == nullptr)
        return false;
    return buffer->dirty;
}

void editorMarkClean(EditorBuffer* buffer) {
    if (buffer == nullptr)
        return;
    buffer->dirty = false;
}
