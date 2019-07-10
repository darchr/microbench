DIRS = $(sort $(dir $(wildcard */)))

.PHONY: all $(DIRS)

all: $(DIRS)

$(DIRS):
	$(MAKE) -C $@

clean:
	rm -f */bench.X86
	rm -f */bench.ARM
	rm -f */bench.RISCV
	rm -f */randArr.h 
