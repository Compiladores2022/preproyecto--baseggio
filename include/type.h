#ifndef TYPE_H
#define TYPE_H

typedef enum type {
    TYPE_INT,
    TYPE_BOOL,
    TYPE_VOID
} Type;

/* The 'typeToString' function returns a string representing the type. */
char* typeToString(Type type);
#endif
