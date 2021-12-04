/** \file swmain.h

 ** Streamwork swmain includes

*/
 
#ifndef SWMAIN_H_
#define SWMAIN_H_

#include "model.h"

void SendPrefix();  
void SendSuffix(); 

void GenChan(int nchannels); 

int eqs (char *s1, char *s2);
#endif 
