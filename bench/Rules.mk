sp             := $(sp).x
dirstack_$(sp) := $(d)
d              := $(dir)

# local variables
OBJS_ASM_$(d)   := $(d)/hercules_asm.o            \

OBJS_$(d)       := $(OBJS_ASM_$(d))               \
                   $(d)/hercules.o                \
                   $(d)/nop.o                     \

DEPS_$(d)       := $(OBJS_$(d):%.o=%.d)
LST_$(d)        := $(OBJS_ASM_$(d):%.o=%.lst)
CLEAN           := $(CLEAN) $(OBJS_$(d)) $(DEPS_$(d)) $(LST_$(d))

-include $(DEPS_$(d))

d              := $(dirstack_$(sp))
sp             := $(basename $(sp))
