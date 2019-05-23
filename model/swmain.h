#ifndef SWMAIN_H_
#define SWMAIN_H_

#include "nemod.h"

void SendPrefix();  
void SendSuffix(); 

void GenChan(int nchannels); 
Component MakeComponent(Ident name, String path);
Process MakeProcess(Ident name, Component comp) ;
Port MakePort(int n) ;
Flow MakeFlow(Process src, Process snk) ;
Model MakeModel(Flow f);
#endif  // SWMAIN_H_
