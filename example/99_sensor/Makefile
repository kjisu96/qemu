SUBDIRS = \
	ADXL345

all:
	for DIRS in $(SUBDIRS); do \
		$(MAKE) -C $$DIRS; \
	done

clean:
	for DIRS in $(SUBDIRS); do \
		$(MAKE) -C $$DIRS clean; \
	done	
