#ifndef PRINTER_HEADER
#define PRINTER_HEADER

#include "Absyn.h"

/* Certain applications may improve performance by changing the buffer size */
#define BUFFER_INITIAL 2000
/* You may wish to change _L_PAREN or _R_PAREN */
#define _L_PAREN '('
#define _R_PAREN ')'

/* The following are simple heuristics for rendering terminals */
/* You may wish to change them */
void renderCC(Char c);
void renderCS(String s);
void indent(void);
void backup(void);


char *printValide(Valide p);
char *printValidSW(ValidSW p);
char *printValidConfig(ValidConfig p);

void ppValide(Valide p, int i);
void ppValidSW(ValidSW p, int i);
void ppStm(Stm p, int i);
void ppListStm(ListStm p, int i);
void ppSubdef(Subdef p, int i);
void ppSubnet(Subnet p, int i);
void ppListSubnet(ListSubnet p, int i);
void ppExtPortIn(ExtPortIn p, int i);
void ppExtPortOut(ExtPortOut p, int i);
void ppTab(Tab p, int i);
void ppDataFlow(DataFlow p, int i);
void ppLarrow(Larrow p, int i);
void ppRarrow(Rarrow p, int i);
void ppLSarrow(LSarrow p, int i);
void ppRSarrow(RSarrow p, int i);
void ppTypeDef(TypeDef p, int i);
void ppBuffsize(Buffsize p, int i);
void ppHermt(Hermt p, int i);
void ppSymvalu(Symvalu p, int i);
void ppProc(Proc p, int i);
void ppAttributes(Attributes p, int i);
void ppAttr(Attr p, int i);
void ppListAttr(ListAttr p, int i);
void ppPrt(Prt p, int i);
void ppComp(Comp p, int i);
void ppModPath(ModPath p, int i);
void ppRemPath(RemPath p, int i);
void ppArgument(Argument p, int i);
void ppListArgument(ListArgument p, int i);
void ppNumassgn(Numassgn p, int i);
void ppStrassgn(Strassgn p, int i);
void ppSymAssgn(SymAssgn p, int i);
void ppNumval(Numval p, int i);
void ppStringval(Stringval p, int i);
void ppSymval(Symval p, int i);
void ppInclude(Include p, int i);
void ppPrefix(Prefix p, int i);
void ppValidConfig(ValidConfig p, int i);
void ppCentry(Centry p, int i);
void ppListCentry(ListCentry p, int i);
void ppEntry(Entry p, int i);
void ppListEntry(ListEntry p, int i);
void ppKeyVal(KeyVal p, int i);
void ppKeyName(KeyName p, int i);

char *showValide(Valide p);
char *showValidSW(ValidSW p);
char *showValidConfig(ValidConfig p);

void shValide(Valide p);
void shValidSW(ValidSW p);
void shStm(Stm p);
void shListStm(ListStm p);
void shSubdef(Subdef p);
void shSubnet(Subnet p);
void shListSubnet(ListSubnet p);
void shExtPortIn(ExtPortIn p);
void shExtPortOut(ExtPortOut p);
void shTab(Tab p);
void shDataFlow(DataFlow p);
void shLarrow(Larrow p);
void shRarrow(Rarrow p);
void shLSarrow(LSarrow p);
void shRSarrow(RSarrow p);
void shTypeDef(TypeDef p);
void shBuffsize(Buffsize p);
void shHermt(Hermt p);
void shSymvalu(Symvalu p);
void shProc(Proc p);
void shAttributes(Attributes p);
void shAttr(Attr p);
void shListAttr(ListAttr p);
void shPrt(Prt p);
void shComp(Comp p);
void shModPath(ModPath p);
void shRemPath(RemPath p);
void shArgument(Argument p);
void shListArgument(ListArgument p);
void shNumassgn(Numassgn p);
void shStrassgn(Strassgn p);
void shSymAssgn(SymAssgn p);
void shNumval(Numval p);
void shStringval(Stringval p);
void shSymval(Symval p);
void shInclude(Include p);
void shPrefix(Prefix p);
void shValidConfig(ValidConfig p);
void shCentry(Centry p);
void shListCentry(ListCentry p);
void shEntry(Entry p);
void shListEntry(ListEntry p);
void shKeyVal(KeyVal p);
void shKeyName(KeyName p);

void ppNumvar(String s, int i);
void ppStringvar(String s, int i);
void ppEnvar(String s, int i);
void ppSymvar(String s, int i);
void ppSubId(String s, int i);
void ppId(String s, int i);
void ppValidImport(String s, int i);
void ppDate(String s, int i);
void shNumvar(String s);
void shStringvar(String s);
void shEnvar(String s);
void shSymvar(String s);
void shSubId(String s);
void shId(String s);
void shValidImport(String s);
void shDate(String s);
void ppInteger(Integer n, int i);
void ppDouble(Double d, int i);
void ppChar(Char c, int i);
void ppString(String s, int i);
void ppIdent(String s, int i);
void shInteger(Integer n);
void shDouble(Double d);
void shChar(Char c);
void shString(String s);
void shIdent(String s);
void bufAppendS(const char *s);
void bufAppendC(const char c);
void bufReset(void);
void resizeBuffer(void);

#endif

