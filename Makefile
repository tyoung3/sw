
SUBDIRS = bnfc model

.PHONY : all $(SUBDIRS)

all : $(SUBDIRS) 
	
$(SUBDIRS) :
	$(MAKE) -C $@
