
SUBDIRS = model bnfc 

.PHONY : all $(SUBDIRS)

all : $(SUBDIRS) 
	
$(SUBDIRS) :
	$(MAKE) check -C $@
