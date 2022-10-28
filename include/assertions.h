#ifndef ASSERTIONS_H
#define ASSERTIONS_H

void assertTrue(int expression);

void assertFalse(int expression);

void assertEquals(void* expected, void* value, int (*equals) (void*, void*), char* (*toString) (void*));

#endif
