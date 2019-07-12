DIRS = $(dir $(wildcard */))

.PHONY: default all $(DIRS)

default: PARENT = default
default: $(DIRS) 

all: PARENT = all
all: $(DIRS)

X86: PARENT = X86
X86: $(DIRS)

ARM: PARENT = ARM
ARM: $(DIRS)

RISCV: PARENT = RISCV
RISCV: $(DIRS)

$(DIRS):
	$(MAKE) $(PARENT) -C $@

clean:
	rm -f */bench.X86
	rm -f */bench.ARM
	rm -f */bench.RISCV
	rm -f */randArr.h 
