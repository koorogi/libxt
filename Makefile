CF_ALL    = -0 -za99 -we -q -d3 -bt=dos -i=libxt/include
LIBF_ALL  = -n -q
LDF_ALL   = $(CF_ALL)

CC        = wcc
LIB       = wlib
LD        = wcl
COMP      = $(CC) $(CF_ALL) $(CF_TGT) -ad=$(patsubst %.c,%.d,$<) $< -fo=$@
MKLIB     = $(LIB) $(LIBF_ALL) $(LIBF_TGT) $@ $(patsubst %,+%,$^)
LINK      = $(LD) $(LDF_ALL) $^ -fo=$(patsubst %.exe,%,$@)

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
