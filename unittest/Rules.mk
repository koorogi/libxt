sp             := $(sp).x
dirstack_$(sp) := $(d)
d              := $(dir)

# local variables
OBJS_$(d)       := $(d)/fixedpoint.o              \
                   $(d)/unittest.o                \

DEPS_$(d)       := $(OBJS_$(d):%.o=%.d)
CLEAN           := $(CLEAN) $(OBJS_$(d)) $(DEPS_$(d)) $(LST_$(d))

-include $(DEPS_$(d))

d              := $(dirstack_$(sp))
sp             := $(basename $(sp))
