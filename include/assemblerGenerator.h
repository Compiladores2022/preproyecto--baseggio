#ifndef ASSEMBLERGENERATOR_H
#define ASSEMBLERGENERATOR_H

#include "threeAddressCode.h"

extern char* filename;

/* The 'generateAssembler' generates assembler code from three address code. */
void generateAssembler(ThreeAddressCode threeAddressCode);

#endif
