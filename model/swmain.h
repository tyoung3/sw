#ifndef SWMAIN_H_
#define SWMAIN_H_

#include "model.h"

void SendPrefix();  
void SendSuffix(); 

void GenChan(int nchannels); 
Component MakeComponent(Ident name, String path);
Process MakeProcess(Ident name, Component comp, ListArgument la);  
Port MakePort(int n, Ident id) ;
Flow MakeFlow(Process src, Process snk, int bufsz) ;
Model MakeModel(Flow f);
#endif  // SWMAIN_H_
