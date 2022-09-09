#ifndef TYPE_H
#define TYPE_H

typedef enum type {
    TYPE_INT,
    TYPE_BOOL
} Type;

char* typeToString(Type type);
#endif
