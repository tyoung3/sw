#ifndef SKELETON_HEADER
#define SKELETON_HEADER
/* You might want to change the above name. */

#include "Absyn.h"


void visitValide(Valide p);
void visitValidSW(ValidSW p);
void visitStm(Stm p);
void visitListStm(ListStm p);
void visitSubdef(Subdef p);
void visitSubnet(Subnet p);
void visitListSubnet(ListSubnet p);
void visitExtPortIn(ExtPortIn p);
void visitExtPortOut(ExtPortOut p);
void visitTab(Tab p);
void visitDataFlow(DataFlow p);
void visitLarrow(Larrow p);
void visitRarrow(Rarrow p);
void visitLSarrow(LSarrow p);
void visitRSarrow(RSarrow p);
void visitTypeDef(TypeDef p);
void visitBuffsize(Buffsize p);
void visitHermt(Hermt p);
void visitSymvalu(Symvalu p);
void visitProc(Proc p);
void visitAttributes(Attributes p);
void visitAttr(Attr p);
void visitListAttr(ListAttr p);
void visitPrt(Prt p);
void visitComp(Comp p);
void visitModPath(ModPath p);
void visitRemPath(RemPath p);
void visitArgument(Argument p);
void visitListArgument(ListArgument p);
void visitNumassgn(Numassgn p);
void visitStrassgn(Strassgn p);
void visitSymAssgn(SymAssgn p);
void visitNumval(Numval p);
void visitStringval(Stringval p);
void visitSymval(Symval p);
void visitInclude(Include p);
void visitPrefix(Prefix p);
void visitValidConfig(ValidConfig p);
void visitCentry(Centry p);
void visitListCentry(ListCentry p);
void visitEntry(Entry p);
void visitListEntry(ListEntry p);
void visitKeyVal(KeyVal p);
void visitKeyName(KeyName p);

void visitNumvar(Numvar p);void visitStringvar(Stringvar p);void visitEnvar(Envar p);void visitSymvar(Symvar p);void visitSubId(SubId p);void visitId(Id p);void visitValidImport(ValidImport p);void visitDate(Date p);
void visitIdent(Ident i);
void visitInteger(Integer i);
void visitDouble(Double d);
void visitChar(Char c);
void visitString(String s);

#endif

