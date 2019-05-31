#ifndef SWMAIN_H_
#define SWMAIN_H_

#include "model.h"

void SendPrefix();  
void SendSuffix(); 

void GenChan(int nchannels); 
Component MakeComponent(Ident name, String path);
// Process MakeProcess(Model, Ident name, Component comp, ListArgument la);  
Port MakePort(int n, Ident id) ;
Stream MakeStream(KINDOF k, Process src, Process snk, int bufsz, Model m) ;
Model MakeModel(Stream f);
#endif  // SWMAIN_H_
