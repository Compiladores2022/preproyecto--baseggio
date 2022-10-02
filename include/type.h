#ifndef TYPE_H
#define TYPE_H

typedef enum type {
    TYPE_INT,
    TYPE_BOOL,
    TYPE_VOID
} Type;

char* typeToString(Type type);
#endif
