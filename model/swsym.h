#ifndef SWSYM_H_
#define SWSYM_H_

#include "model.h"

int getPath(char *key);
// int addPath(char *key);
Process getProc(char *key);
Process addProc(char *key, Process p);
Component getComponent(char *name, char *path);
Component addComponent(char *name, char *path, Component c);
void    tabinit(int nvar);
void free_symtab();
#endif

