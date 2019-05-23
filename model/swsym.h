#ifndef SWSYM_H_
#define SWSYM_H_

#include "nemod.h"

int getPath(char *key);
// int addPath(char *key);
Process getProc(char *key);
Process addProc(char *key, Process p);
void    tabinit(int nvar);
void free_symtab();
#endif

