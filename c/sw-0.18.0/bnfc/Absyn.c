/* C Abstract Syntax Implementation generated by the BNF Converter. */

#include <stdio.h>
#include <stdlib.h>
#include "Absyn.h"


/********************   CFGvalid    ********************/
Valide make_CFGvalid(ValidConfig p1)
{
    Valide tmp = (Valide) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating CFGvalid!\n");
        exit(1);
    }
    tmp->kind = is_CFGvalid;
    tmp->u.cfgvalid_.validconfig_ = p1;
    return tmp;
}
/********************   SWvalid    ********************/
Valide make_SWvalid(ValidSW p1)
{
    Valide tmp = (Valide) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating SWvalid!\n");
        exit(1);
    }
    tmp->kind = is_SWvalid;
    tmp->u.swvalid_.validsw_ = p1;
    return tmp;
}/********************   Valid    ********************/
ValidSW make_Valid(ListStm p1)
{
    ValidSW tmp = (ValidSW) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Valid!\n");
        exit(1);
    }
    tmp->kind = is_Valid;
    tmp->u.valid_.liststm_ = p1;
    return tmp;
}/********************   StmPrefix    ********************/
Stm make_StmPrefix(Prefix p1, Stringval p2)
{
    Stm tmp = (Stm) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating StmPrefix!\n");
        exit(1);
    }
    tmp->kind = is_StmPrefix;
    tmp->u.stmprefix_.prefix_ = p1;
    tmp->u.stmprefix_.stringval_ = p2;
    return tmp;
}
/********************   Stminc    ********************/
Stm make_Stminc(Include p1, Stringval p2)
{
    Stm tmp = (Stm) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Stminc!\n");
        exit(1);
    }
    tmp->kind = is_Stminc;
    tmp->u.stminc_.include_ = p1;
    tmp->u.stminc_.stringval_ = p2;
    return tmp;
}
/********************   Stmx    ********************/
Stm make_Stmx(DataFlow p1)
{
    Stm tmp = (Stm) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Stmx!\n");
        exit(1);
    }
    tmp->kind = is_Stmx;
    tmp->u.stmx_.dataflow_ = p1;
    return tmp;
}
/********************   Stmn    ********************/
Stm make_Stmn(Numassgn p1)
{
    Stm tmp = (Stm) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Stmn!\n");
        exit(1);
    }
    tmp->kind = is_Stmn;
    tmp->u.stmn_.numassgn_ = p1;
    return tmp;
}
/********************   Stms    ********************/
Stm make_Stms(Strassgn p1)
{
    Stm tmp = (Stm) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Stms!\n");
        exit(1);
    }
    tmp->kind = is_Stms;
    tmp->u.stms_.strassgn_ = p1;
    return tmp;
}
/********************   Stmb    ********************/
Stm make_Stmb(SymAssgn p1)
{
    Stm tmp = (Stm) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Stmb!\n");
        exit(1);
    }
    tmp->kind = is_Stmb;
    tmp->u.stmb_.symassgn_ = p1;
    return tmp;
}
/********************   Stmh    ********************/
Stm make_Stmh(Hermt p1)
{
    Stm tmp = (Stm) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Stmh!\n");
        exit(1);
    }
    tmp->kind = is_Stmh;
    tmp->u.stmh_.hermt_ = p1;
    return tmp;
}
/********************   Stmnet    ********************/
Stm make_Stmnet(Subdef p1)
{
    Stm tmp = (Stm) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Stmnet!\n");
        exit(1);
    }
    tmp->kind = is_Stmnet;
    tmp->u.stmnet_.subdef_ = p1;
    return tmp;
}/********************   ListStm    ********************/
ListStm make_ListStm(Stm p1, ListStm p2)
{
    ListStm tmp = (ListStm) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating ListStm!\n");
        exit(1);
    }
    tmp->stm_ = p1;
    tmp->liststm_ = p2;
    return tmp;
}/********************   Snet    ********************/
Subdef make_Snet(SubId p1, ListSubnet p2)
{
    Subdef tmp = (Subdef) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Snet!\n");
        exit(1);
    }
    tmp->kind = is_Snet;
    tmp->u.snet_.subid_ = p1;
    tmp->u.snet_.listsubnet_ = p2;
    return tmp;
}/********************   Sneth    ********************/
Subnet make_Sneth(Hermt p1)
{
    Subnet tmp = (Subnet) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Sneth!\n");
        exit(1);
    }
    tmp->kind = is_Sneth;
    tmp->u.sneth_.hermt_ = p1;
    return tmp;
}
/********************   Snets    ********************/
Subnet make_Snets(DataFlow p1)
{
    Subnet tmp = (Subnet) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Snets!\n");
        exit(1);
    }
    tmp->kind = is_Snets;
    tmp->u.snets_.dataflow_ = p1;
    return tmp;
}
/********************   Snetin    ********************/
Subnet make_Snetin(ExtPortIn p1)
{
    Subnet tmp = (Subnet) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Snetin!\n");
        exit(1);
    }
    tmp->kind = is_Snetin;
    tmp->u.snetin_.extportin_ = p1;
    return tmp;
}
/********************   Snetout    ********************/
Subnet make_Snetout(ExtPortOut p1)
{
    Subnet tmp = (Subnet) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Snetout!\n");
        exit(1);
    }
    tmp->kind = is_Snetout;
    tmp->u.snetout_.extportout_ = p1;
    return tmp;
}/********************   ListSubnet    ********************/
ListSubnet make_ListSubnet(Subnet p1, ListSubnet p2)
{
    ListSubnet tmp = (ListSubnet) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating ListSubnet!\n");
        exit(1);
    }
    tmp->subnet_ = p1;
    tmp->listsubnet_ = p2;
    return tmp;
}/********************   Extin    ********************/
ExtPortIn make_Extin(Proc p1, Prt p2, Larrow p3, Tab p4)
{
    ExtPortIn tmp = (ExtPortIn) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Extin!\n");
        exit(1);
    }
    tmp->kind = is_Extin;
    tmp->u.extin_.proc_ = p1;
    tmp->u.extin_.prt_ = p2;
    tmp->u.extin_.larrow_ = p3;
    tmp->u.extin_.tab_ = p4;
    return tmp;
}
/********************   ExtinR    ********************/
ExtPortIn make_ExtinR(Tab p1, Rarrow p2, Prt p3, Proc p4)
{
    ExtPortIn tmp = (ExtPortIn) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating ExtinR!\n");
        exit(1);
    }
    tmp->kind = is_ExtinR;
    tmp->u.extinr_.tab_ = p1;
    tmp->u.extinr_.rarrow_ = p2;
    tmp->u.extinr_.prt_ = p3;
    tmp->u.extinr_.proc_ = p4;
    return tmp;
}/********************   Extout    ********************/
ExtPortOut make_Extout(Tab p1, Larrow p2, Prt p3, Proc p4)
{
    ExtPortOut tmp = (ExtPortOut) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Extout!\n");
        exit(1);
    }
    tmp->kind = is_Extout;
    tmp->u.extout_.tab_ = p1;
    tmp->u.extout_.larrow_ = p2;
    tmp->u.extout_.prt_ = p3;
    tmp->u.extout_.proc_ = p4;
    return tmp;
}
/********************   Extoutr    ********************/
ExtPortOut make_Extoutr(Proc p1, Prt p2, Rarrow p3, Tab p4)
{
    ExtPortOut tmp = (ExtPortOut) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Extoutr!\n");
        exit(1);
    }
    tmp->kind = is_Extoutr;
    tmp->u.extoutr_.proc_ = p1;
    tmp->u.extoutr_.prt_ = p2;
    tmp->u.extoutr_.rarrow_ = p3;
    tmp->u.extoutr_.tab_ = p4;
    return tmp;
}/********************   Tabn    ********************/
Tab make_Tabn(Numval p1)
{
    Tab tmp = (Tab) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Tabn!\n");
        exit(1);
    }
    tmp->kind = is_Tabn;
    tmp->u.tabn_.numval_ = p1;
    return tmp;
}
/********************   Tabs    ********************/
Tab make_Tabs(Symval p1)
{
    Tab tmp = (Tab) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Tabs!\n");
        exit(1);
    }
    tmp->kind = is_Tabs;
    tmp->u.tabs_.symval_ = p1;
    return tmp;
}/********************   Streamx    ********************/
DataFlow make_Streamx(Proc p1, Prt p2, Larrow p3, Prt p4, Proc p5)
{
    DataFlow tmp = (DataFlow) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Streamx!\n");
        exit(1);
    }
    tmp->kind = is_Streamx;
    tmp->u.streamx_.proc_1 = p1;
    tmp->u.streamx_.prt_1 = p2;
    tmp->u.streamx_.larrow_ = p3;
    tmp->u.streamx_.prt_2 = p4;
    tmp->u.streamx_.proc_2 = p5;
    return tmp;
}
/********************   Streamrx    ********************/
DataFlow make_Streamrx(Proc p1, Prt p2, Rarrow p3, Prt p4, Proc p5)
{
    DataFlow tmp = (DataFlow) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Streamrx!\n");
        exit(1);
    }
    tmp->kind = is_Streamrx;
    tmp->u.streamrx_.proc_1 = p1;
    tmp->u.streamrx_.prt_1 = p2;
    tmp->u.streamrx_.rarrow_ = p3;
    tmp->u.streamrx_.prt_2 = p4;
    tmp->u.streamrx_.proc_2 = p5;
    return tmp;
}
/********************   Streamy    ********************/
DataFlow make_Streamy(DataFlow p1, Prt p2, Larrow p3, Prt p4, Proc p5)
{
    DataFlow tmp = (DataFlow) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Streamy!\n");
        exit(1);
    }
    tmp->kind = is_Streamy;
    tmp->u.streamy_.dataflow_ = p1;
    tmp->u.streamy_.prt_1 = p2;
    tmp->u.streamy_.larrow_ = p3;
    tmp->u.streamy_.prt_2 = p4;
    tmp->u.streamy_.proc_ = p5;
    return tmp;
}
/********************   Streamry    ********************/
DataFlow make_Streamry(DataFlow p1, Prt p2, Rarrow p3, Prt p4, Proc p5)
{
    DataFlow tmp = (DataFlow) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Streamry!\n");
        exit(1);
    }
    tmp->kind = is_Streamry;
    tmp->u.streamry_.dataflow_ = p1;
    tmp->u.streamry_.prt_1 = p2;
    tmp->u.streamry_.rarrow_ = p3;
    tmp->u.streamry_.prt_2 = p4;
    tmp->u.streamry_.proc_ = p5;
    return tmp;
}/********************   Arrowx    ********************/
Larrow make_Arrowx(TypeDef p1, Buffsize p2)
{
    Larrow tmp = (Larrow) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Arrowx!\n");
        exit(1);
    }
    tmp->kind = is_Arrowx;
    tmp->u.arrowx_.typedef_ = p1;
    tmp->u.arrowx_.buffsize_ = p2;
    return tmp;
}/********************   Arrowr    ********************/
Rarrow make_Arrowr(TypeDef p1, Buffsize p2)
{
    Rarrow tmp = (Rarrow) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Arrowr!\n");
        exit(1);
    }
    tmp->kind = is_Arrowr;
    tmp->u.arrowr_.typedef_ = p1;
    tmp->u.arrowr_.buffsize_ = p2;
    return tmp;
}/********************   Typedefa    ********************/
TypeDef make_Typedefa(Symvalu p1)
{
    TypeDef tmp = (TypeDef) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Typedefa!\n");
        exit(1);
    }
    tmp->kind = is_Typedefa;
    tmp->u.typedefa_.symvalu_ = p1;
    return tmp;
}
/********************   Typedefnull    ********************/
TypeDef make_Typedefnull()
{
    TypeDef tmp = (TypeDef) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Typedefnull!\n");
        exit(1);
    }
    tmp->kind = is_Typedefnull;
    return tmp;
}/********************   Bufszi    ********************/
Buffsize make_Bufszi(Numval p1)
{
    Buffsize tmp = (Buffsize) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Bufszi!\n");
        exit(1);
    }
    tmp->kind = is_Bufszi;
    tmp->u.bufszi_.numval_ = p1;
    return tmp;
}
/********************   Bufsze    ********************/
Buffsize make_Bufsze()
{
    Buffsize tmp = (Buffsize) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Bufsze!\n");
        exit(1);
    }
    tmp->kind = is_Bufsze;
    return tmp;
}/********************   Hermtx    ********************/
Hermt make_Hermtx(Symvalu p1, Comp p2, ListArgument p3)
{
    Hermt tmp = (Hermt) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Hermtx!\n");
        exit(1);
    }
    tmp->kind = is_Hermtx;
    tmp->u.hermtx_.symvalu_ = p1;
    tmp->u.hermtx_.comp_ = p2;
    tmp->u.hermtx_.listargument_ = p3;
    return tmp;
}
/********************   Hermty    ********************/
Hermt make_Hermty(Symvalu p1, ListArgument p2)
{
    Hermt tmp = (Hermt) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Hermty!\n");
        exit(1);
    }
    tmp->kind = is_Hermty;
    tmp->u.hermty_.symvalu_ = p1;
    tmp->u.hermty_.listargument_ = p2;
    return tmp;
}/********************   Symvaluv    ********************/
Symvalu make_Symvaluv(Symval p1)
{
    Symvalu tmp = (Symvalu) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Symvaluv!\n");
        exit(1);
    }
    tmp->kind = is_Symvaluv;
    tmp->u.symvaluv_.symval_ = p1;
    return tmp;
}
/********************   Symvaluu    ********************/
Symvalu make_Symvaluu()
{
    Symvalu tmp = (Symvalu) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Symvaluu!\n");
        exit(1);
    }
    tmp->kind = is_Symvaluu;
    return tmp;
}/********************   Processx    ********************/
Proc make_Processx(Symvalu p1, Comp p2, ListArgument p3)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Processx!\n");
        exit(1);
    }
    tmp->kind = is_Processx;
    tmp->u.processx_.symvalu_ = p1;
    tmp->u.processx_.comp_ = p2;
    tmp->u.processx_.listargument_ = p3;
    return tmp;
}
/********************   Processy    ********************/
Proc make_Processy(Symvalu p1, ListArgument p2)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Processy!\n");
        exit(1);
    }
    tmp->kind = is_Processy;
    tmp->u.processy_.symvalu_ = p1;
    tmp->u.processy_.listargument_ = p2;
    return tmp;
}/********************   Portx    ********************/
Prt make_Portx(Numval p1)
{
    Prt tmp = (Prt) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Portx!\n");
        exit(1);
    }
    tmp->kind = is_Portx;
    tmp->u.portx_.numval_ = p1;
    return tmp;
}
/********************   Portni    ********************/
Prt make_Portni(Numval p1, Symval p2)
{
    Prt tmp = (Prt) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Portni!\n");
        exit(1);
    }
    tmp->kind = is_Portni;
    tmp->u.portni_.numval_ = p1;
    tmp->u.portni_.symval_ = p2;
    return tmp;
}
/********************   Portin    ********************/
Prt make_Portin(Symval p1, Numval p2)
{
    Prt tmp = (Prt) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Portin!\n");
        exit(1);
    }
    tmp->kind = is_Portin;
    tmp->u.portin_.symval_ = p1;
    tmp->u.portin_.numval_ = p2;
    return tmp;
}
/********************   Portn    ********************/
Prt make_Portn(Symval p1)
{
    Prt tmp = (Prt) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Portn!\n");
        exit(1);
    }
    tmp->kind = is_Portn;
    tmp->u.portn_.symval_ = p1;
    return tmp;
}
/********************   Porte    ********************/
Prt make_Porte()
{
    Prt tmp = (Prt) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Porte!\n");
        exit(1);
    }
    tmp->kind = is_Porte;
    return tmp;
}/********************   Compx    ********************/
Comp make_Compx(Symval p1)
{
    Comp tmp = (Comp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Compx!\n");
        exit(1);
    }
    tmp->kind = is_Compx;
    tmp->u.compx_.symval_ = p1;
    return tmp;
}
/********************   Compn    ********************/
Comp make_Compn(SubId p1)
{
    Comp tmp = (Comp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Compn!\n");
        exit(1);
    }
    tmp->kind = is_Compn;
    tmp->u.compn_.subid_ = p1;
    return tmp;
}
/********************   Compz    ********************/
Comp make_Compz(ModPath p1, Symval p2)
{
    Comp tmp = (Comp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Compz!\n");
        exit(1);
    }
    tmp->kind = is_Compz;
    tmp->u.compz_.modpath_ = p1;
    tmp->u.compz_.symval_ = p2;
    return tmp;
}
/********************   Compa    ********************/
Comp make_Compa(RemPath p1)
{
    Comp tmp = (Comp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Compa!\n");
        exit(1);
    }
    tmp->kind = is_Compa;
    tmp->u.compa_.rempath_ = p1;
    return tmp;
}/********************   Modpa    ********************/
ModPath make_Modpa(Symval p1)
{
    ModPath tmp = (ModPath) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Modpa!\n");
        exit(1);
    }
    tmp->kind = is_Modpa;
    tmp->u.modpa_.symval_ = p1;
    return tmp;
}
/********************   Modpx    ********************/
ModPath make_Modpx(Symval p1)
{
    ModPath tmp = (ModPath) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Modpx!\n");
        exit(1);
    }
    tmp->kind = is_Modpx;
    tmp->u.modpx_.symval_ = p1;
    return tmp;
}
/********************   Modpy    ********************/
ModPath make_Modpy(ModPath p1, Symval p2)
{
    ModPath tmp = (ModPath) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Modpy!\n");
        exit(1);
    }
    tmp->kind = is_Modpy;
    tmp->u.modpy_.modpath_ = p1;
    tmp->u.modpy_.symval_ = p2;
    return tmp;
}
/********************   Modps    ********************/
ModPath make_Modps(Stringvar p1)
{
    ModPath tmp = (ModPath) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Modps!\n");
        exit(1);
    }
    tmp->kind = is_Modps;
    tmp->u.modps_.stringvar_ = p1;
    return tmp;
}/********************   RemPatha    ********************/
RemPath make_RemPatha(ValidImport p1, Symval p2)
{
    RemPath tmp = (RemPath) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating RemPatha!\n");
        exit(1);
    }
    tmp->kind = is_RemPatha;
    tmp->u.rempatha_.validimport_ = p1;
    tmp->u.rempatha_.symval_ = p2;
    return tmp;
}/********************   Argumentx    ********************/
Argument make_Argumentx(Stringval p1)
{
    Argument tmp = (Argument) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Argumentx!\n");
        exit(1);
    }
    tmp->kind = is_Argumentx;
    tmp->u.argumentx_.stringval_ = p1;
    return tmp;
}/********************   ListArgument    ********************/
ListArgument make_ListArgument(Argument p1, ListArgument p2)
{
    ListArgument tmp = (ListArgument) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating ListArgument!\n");
        exit(1);
    }
    tmp->argument_ = p1;
    tmp->listargument_ = p2;
    return tmp;
}/********************   NumAssgnv    ********************/
Numassgn make_NumAssgnv(Numvar p1, Numval p2)
{
    Numassgn tmp = (Numassgn) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating NumAssgnv!\n");
        exit(1);
    }
    tmp->kind = is_NumAssgnv;
    tmp->u.numassgnv_.numvar_ = p1;
    tmp->u.numassgnv_.numval_ = p2;
    return tmp;
}/********************   StrAssgnv    ********************/
Strassgn make_StrAssgnv(Stringvar p1, Stringval p2)
{
    Strassgn tmp = (Strassgn) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating StrAssgnv!\n");
        exit(1);
    }
    tmp->kind = is_StrAssgnv;
    tmp->u.strassgnv_.stringvar_ = p1;
    tmp->u.strassgnv_.stringval_ = p2;
    return tmp;
}/********************   SymAssgni    ********************/
SymAssgn make_SymAssgni(Symvar p1, Symval p2)
{
    SymAssgn tmp = (SymAssgn) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating SymAssgni!\n");
        exit(1);
    }
    tmp->kind = is_SymAssgni;
    tmp->u.symassgni_.symvar_ = p1;
    tmp->u.symassgni_.symval_ = p2;
    return tmp;
}/********************   NumVali    ********************/
Numval make_NumVali(Integer p1)
{
    Numval tmp = (Numval) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating NumVali!\n");
        exit(1);
    }
    tmp->kind = is_NumVali;
    tmp->u.numvali_.integer_ = p1;
    return tmp;
}
/********************   NumValv    ********************/
Numval make_NumValv(Numvar p1)
{
    Numval tmp = (Numval) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating NumValv!\n");
        exit(1);
    }
    tmp->kind = is_NumValv;
    tmp->u.numvalv_.numvar_ = p1;
    return tmp;
}/********************   StringVals    ********************/
Stringval make_StringVals(String p1)
{
    Stringval tmp = (Stringval) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating StringVals!\n");
        exit(1);
    }
    tmp->kind = is_StringVals;
    tmp->u.stringvals_.string_ = p1;
    return tmp;
}
/********************   StringValv    ********************/
Stringval make_StringValv(Stringvar p1)
{
    Stringval tmp = (Stringval) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating StringValv!\n");
        exit(1);
    }
    tmp->kind = is_StringValv;
    tmp->u.stringvalv_.stringvar_ = p1;
    return tmp;
}
/********************   StringVale    ********************/
Stringval make_StringVale(Envar p1)
{
    Stringval tmp = (Stringval) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating StringVale!\n");
        exit(1);
    }
    tmp->kind = is_StringVale;
    tmp->u.stringvale_.envar_ = p1;
    return tmp;
}/********************   Symvalv    ********************/
Symval make_Symvalv(Symvar p1)
{
    Symval tmp = (Symval) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Symvalv!\n");
        exit(1);
    }
    tmp->kind = is_Symvalv;
    tmp->u.symvalv_.symvar_ = p1;
    return tmp;
}
/********************   Symvali    ********************/
Symval make_Symvali(Id p1)
{
    Symval tmp = (Symval) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Symvali!\n");
        exit(1);
    }
    tmp->kind = is_Symvali;
    tmp->u.symvali_.id_ = p1;
    return tmp;
}
/********************   SymVale    ********************/
Symval make_SymVale(Envar p1)
{
    Symval tmp = (Symval) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating SymVale!\n");
        exit(1);
    }
    tmp->kind = is_SymVale;
    tmp->u.symvale_.envar_ = p1;
    return tmp;
}/********************   Inc1    ********************/
Include make_Inc1()
{
    Include tmp = (Include) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Inc1!\n");
        exit(1);
    }
    tmp->kind = is_Inc1;
    return tmp;
}
/********************   Inc2    ********************/
Include make_Inc2()
{
    Include tmp = (Include) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Inc2!\n");
        exit(1);
    }
    tmp->kind = is_Inc2;
    return tmp;
}/********************   Prefu    ********************/
Prefix make_Prefu()
{
    Prefix tmp = (Prefix) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Prefu!\n");
        exit(1);
    }
    tmp->kind = is_Prefu;
    return tmp;
}
/********************   Prefl    ********************/
Prefix make_Prefl()
{
    Prefix tmp = (Prefix) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Prefl!\n");
        exit(1);
    }
    tmp->kind = is_Prefl;
    return tmp;
}/********************   Validcfg    ********************/
ValidConfig make_Validcfg(ListEntry p1)
{
    ValidConfig tmp = (ValidConfig) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Validcfg!\n");
        exit(1);
    }
    tmp->kind = is_Validcfg;
    tmp->u.validcfg_.listentry_ = p1;
    return tmp;
}
/********************   Validcfgd    ********************/
ValidConfig make_Validcfgd(ListCentry p1)
{
    ValidConfig tmp = (ValidConfig) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Validcfgd!\n");
        exit(1);
    }
    tmp->kind = is_Validcfgd;
    tmp->u.validcfgd_.listcentry_ = p1;
    return tmp;
}/********************   CfgcEntrya    ********************/
Centry make_CfgcEntrya(KeyVal p1)
{
    Centry tmp = (Centry) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating CfgcEntrya!\n");
        exit(1);
    }
    tmp->kind = is_CfgcEntrya;
    tmp->u.cfgcentrya_.keyval_ = p1;
    return tmp;
}
/********************   CfgcEntryb    ********************/
Centry make_CfgcEntryb(KeyName p1)
{
    Centry tmp = (Centry) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating CfgcEntryb!\n");
        exit(1);
    }
    tmp->kind = is_CfgcEntryb;
    tmp->u.cfgcentryb_.keyname_ = p1;
    return tmp;
}/********************   ListCentry    ********************/
ListCentry make_ListCentry(Centry p1, ListCentry p2)
{
    ListCentry tmp = (ListCentry) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating ListCentry!\n");
        exit(1);
    }
    tmp->centry_ = p1;
    tmp->listcentry_ = p2;
    return tmp;
}/********************   CfgEntrya    ********************/
Entry make_CfgEntrya(KeyVal p1)
{
    Entry tmp = (Entry) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating CfgEntrya!\n");
        exit(1);
    }
    tmp->kind = is_CfgEntrya;
    tmp->u.cfgentrya_.keyval_ = p1;
    return tmp;
}
/********************   CfgEntryb    ********************/
Entry make_CfgEntryb(KeyName p1)
{
    Entry tmp = (Entry) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating CfgEntryb!\n");
        exit(1);
    }
    tmp->kind = is_CfgEntryb;
    tmp->u.cfgentryb_.keyname_ = p1;
    return tmp;
}/********************   ListEntry    ********************/
ListEntry make_ListEntry(Entry p1, ListEntry p2)
{
    ListEntry tmp = (ListEntry) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating ListEntry!\n");
        exit(1);
    }
    tmp->entry_ = p1;
    tmp->listentry_ = p2;
    return tmp;
}/********************   CfgKeyvalint    ********************/
KeyVal make_CfgKeyvalint(KeyName p1, Integer p2)
{
    KeyVal tmp = (KeyVal) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating CfgKeyvalint!\n");
        exit(1);
    }
    tmp->kind = is_CfgKeyvalint;
    tmp->u.cfgkeyvalint_.keyname_ = p1;
    tmp->u.cfgkeyvalint_.integer_ = p2;
    return tmp;
}
/********************   CfgKeyvalstr    ********************/
KeyVal make_CfgKeyvalstr(KeyName p1, String p2)
{
    KeyVal tmp = (KeyVal) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating CfgKeyvalstr!\n");
        exit(1);
    }
    tmp->kind = is_CfgKeyvalstr;
    tmp->u.cfgkeyvalstr_.keyname_ = p1;
    tmp->u.cfgkeyvalstr_.string_ = p2;
    return tmp;
}
/********************   CfgKeyDate    ********************/
KeyVal make_CfgKeyDate(KeyName p1, Date p2)
{
    KeyVal tmp = (KeyVal) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating CfgKeyDate!\n");
        exit(1);
    }
    tmp->kind = is_CfgKeyDate;
    tmp->u.cfgkeydate_.keyname_ = p1;
    tmp->u.cfgkeydate_.date_ = p2;
    return tmp;
}/********************   KeynameS    ********************/
KeyName make_KeynameS(Symval p1)
{
    KeyName tmp = (KeyName) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating KeynameS!\n");
        exit(1);
    }
    tmp->kind = is_KeynameS;
    tmp->u.keynames_.symval_ = p1;
    return tmp;
}
/********************   KeynameM    ********************/
KeyName make_KeynameM(ModPath p1, Symval p2)
{
    KeyName tmp = (KeyName) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating KeynameM!\n");
        exit(1);
    }
    tmp->kind = is_KeynameM;
    tmp->u.keynamem_.modpath_ = p1;
    tmp->u.keynamem_.symval_ = p2;
    return tmp;
}