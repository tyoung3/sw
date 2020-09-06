#ifndef SWSYM_H_
#define SWSYM_H_

#include "model.h"

int getPath(char *key);
// int addPath(char *key);
Process getProc(char *key);
Process addProc(char *key, Process p);
Component getComponent(char *name, char *path);
Component addComponent(char *name, char *path, Component c);
String addStringVar(String name, String val);
String getSymVar(String name);
String addSymVar(String name, String val);
void    tabinit();
void free_symtab();
#endif

