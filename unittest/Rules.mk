sp             := $(sp).x
dirstack_$(sp) := $(d)
d              := $(dir)

# local variables
OBJS_ASM_$(d)   := $(d)/bitshift2.o               \

OBJS_$(d)       := $(OBJS_ASM_$(d))               \
                   $(d)/fixedpoint.o              \
                   $(d)/bitshift.o                \
                   $(d)/unittest.o                \

DEPS_$(d)       := $(OBJS_$(d):%.o=%.d)
LST_$(d)        := $(OBJS_ASM_$(d):%.o=%.lst)
CLEAN           := $(CLEAN) $(OBJS_$(d)) $(DEPS_$(d)) $(LST_$(d))

-include $(DEPS_$(d))

d              := $(dirstack_$(sp))
sp             := $(basename $(sp))
