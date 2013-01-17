sp             := $(sp).x
dirstack_$(sp) := $(d)
d              := $(dir)

# subdirectories
dir := $(d)/video
include $(dir)/Rules.mk

# local variables
OBJS_$(d)      := $(d)/cmdline.o                         \

TGT_LIB_$(d)   := $(d)/xt.lib                            \

DEPS_$(d)      := $(OBJS_$(d):%.o=%.d)
TGT_LIB        := $(TGT_LIB) $(TGT_LIB_$(d))
CLEAN          := $(CLEAN)   $(TGT_LIB_$(d)) $(OBJS_$(d)) $(DEPS_$(d))

# local rules
$(d)/xt.lib:      $(d)/video/hercules/misc.o             \
                  $(d)/video/hercules/rect.o             \
                  $(d)/video/hercules/line.o             \
                  $(d)/cmdline.o                         \

-include $(DEPS_$(d))

d              := $(dirstack_$(sp))
sp             := $(basename $(sp))
