sp             := $(sp).x
dirstack_$(sp) := $(d)
d              := $(dir)

# local variables
OBJS_ASM_$(d)   := $(d)/clear2.o                  \
                   $(d)/fixedpoint2.o             \
                   $(d)/quaternion2.o             \

OBJS_$(d)       := $(OBJS_ASM_$(d))               \
                   $(d)/cardinfo.o                \
                   $(d)/clear.o                   \
                   $(d)/cube.o                    \
                   $(d)/fixedpoint.o              \
                   $(d)/helpers.o                 \
                   $(d)/lines.o                   \
                   $(d)/nop.o                     \
                   $(d)/quaternion.o              \

DEPS_$(d)       := $(OBJS_$(d):%.o=%.d)
LST_$(d)        := $(OBJS_ASM_$(d):%.o=%.lst)
CLEAN           := $(CLEAN) $(OBJS_$(d)) $(DEPS_$(d)) $(LST_$(d))

-include $(DEPS_$(d))

d              := $(dirstack_$(sp))
sp             := $(basename $(sp))
