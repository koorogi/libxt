CF_ALL    = -0 -za99 -we -q -d3 -bt=dos -ox -fpi87 -ms -i=libxt/include
LIBF_ALL  = -q -n
LDF_ALL   = -q -bcl=dos -lr clibs.lib

CC        = wcc
LIB       = wlib
LD        = wcl
COMP      = $(CC) $(CF_ALL) $(CF_TGT) -ad=$(patsubst %.c,%.d,$<) $< -fo=$@
MKLIB     = $(LIB) $(LIBF_ALL) $(LIBF_TGT) $@ $(patsubst %,+%,$^)
LINK      = $(LD) $(LDF_ALL) -fe=$@ $^

d         = .
dir       = .

all: targets

include Rules.mk

# general rules
%.o: %.c
	$(COMP)

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
