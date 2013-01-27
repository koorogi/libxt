sp             := $(sp).x
dirstack_$(sp) := $(d)
d              := $(dir)

# subdirectories

# local variables
OBJS_ASM_$(d)   := $(d)/line2.o             \

OBJS_$(d)       := OBJS_ASM_$(d)            \
                   $(d)/misc.o              \
                   $(d)/rect.o              \
                   $(d)/line.o              \

DEPS_$(d) := $(OBJS_$(d):%.o=%.d)
LST_$(d)  := $(OBJS_ASM_$(d):%.o=%.lst)
CLEAN     := $(CLEAN) $(OBJS_$(d)) $(DEPS_$(d)) $(LST_$(d))

# local rules
$(OBJS_$(d)): CF_TGT := -i=$(d)

-include $(DEPS_$(d))

d       := $(dirstack_$(sp))
sp      := $(basename $(sp))
