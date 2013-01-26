sp             := $(sp).x
dirstack_$(sp) := $(d)
d              := $(dir)

# local variables
COM_$(d)       := $(d)/dec64.com                  \

LST_$(d)        := $(COM_$(d):%.com=%.lst)
CLEAN           := $(CLEAN) $(COM_$(d)) $(LST_$(d))
TGT_BIN         := $(TGT_BIN) $(COM_$(d))

# local rules
$(d)/dec64.com:    $(d)/dec64.asm

d              := $(dirstack_$(sp))
sp             := $(basename $(sp))
