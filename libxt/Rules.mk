sp             := $(sp).x
dirstack_$(sp) := $(d)
d              := $(dir)

# subdirectories
dir := $(d)/video
include $(dir)/Rules.mk

# local variables
TGT_LIB_$(d)   := $(d)/xt.lib                            \

TGT_LIB        := $(TGT_LIB_$(d)) $(TGT_LIB)
CLEAN          := $(TGT_LIB_$(d)) $(CLEAN)

# local rules
$(d)/xt.lib:      $(d)/video/hercules/misc.o             \

-include $(DEPS_$(d))

d              := $(dirstack_$(sp))
sp             := $(basename $(sp))
