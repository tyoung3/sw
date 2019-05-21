#ifndef SWSYM_H_
#define SWSYM_H_

#include "nemod.h"

Process getProc(char *key);
Process addProc(char *key, Process p);
void    tabinit(int nvar);
void free_symtab();
#endif

