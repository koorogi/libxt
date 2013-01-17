sp             := $(sp).x
dirstack_$(sp) := $(d)
d              := $(dir)

# subdirectories

# local variables
OBJS_$(d) := $(d)/misc.o       \

DEPS_$(d) := $(OBJS_$(d):%.o=%.d)
CLEAN     := $(CLEAN) $(OBJS_$(d)) $(DEPS_$(d))

# local rules
$(OBJS_$(d)): CF_TGT := -i=$(d)

-include $(DEPS_$(d))

d       := $(dirstack_$(sp))
sp      := $(basename $(sp))
