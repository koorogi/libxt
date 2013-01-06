CF_ALL    = -0 -za99 -we -q -d3 -bt=dos -ox -fpi87 -ms -i=libxt/include
LIBF_ALL  = -q -n
LDF_ALL   = -q -bcl=dos -lr clibs.lib
ASF_ALL   = -f obj -g

CC        = wcc
LIB       = wlib
LD        = wcl
AS        = nasm
COMP      = $(CC) $(CF_ALL) $(CF_TGT) -ad=$(patsubst %.c,%.d,$<) $< -fo=$@
MKLIB     = $(LIB) $(LIBF_ALL) $(LIBF_TGT) $@ $(patsubst %,+%,$^)
LINK      = $(LD) $(LDF_ALL) -fe=$@ $^
ASM       = $(AS) $(ASF_ALL) $< -o $@ -l $(patsubst %.asm,%.lst,$<)

d         = .
dir       = .

all: targets

include Rules.mk

# general rules
%.o: %.c
	$(COMP)

%.o: %.asm
	$(ASM)

%.exe: %.o
	$(LINK)

%.lib:
	$(MKLIB)

# phony rules
.PHONY: targets
targets: $(TGT_BIN) $(TGT_LIB)

.PHONY: clean
clean:
	rm -f $(CLEAN)
