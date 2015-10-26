# Call 'make -B' if you need to rebuild the targets.

MKDIR_P = mkdir -p
SUBDIRS := ./utils ./data_structures ./sorting

all: $(SUBDIRS)
$(SUBDIRS):
	$(MKDIR_P) shared
	$(MAKE) -C $@

.PHONY: all $(SUBDIRS)