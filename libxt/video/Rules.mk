sp             := $(sp).x
dirstack_$(sp) := $(d)
d              := $(dir)

# subdirectories
dir  := $(d)/hercules
include $(dir)/Rules.mk

-include $(DEPS_$(d))

d       := $(dirstack_$(sp))
sp      := $(basename $(sp))
