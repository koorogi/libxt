# subdirectories
dir := $(d)/libxt
include $(dir)/Rules.mk

dir := $(d)/hercules
include $(dir)/Rules.mk

# local variables
TGT_BIN_$(d)    := $(d)/hercules.exe              \

OBJS_$(d)       := $(d)/hercules.o                \

DEPS_$(d)       := $(OBJS_$(d):%.o=%.d)
TGT_BIN         := $(TGT_BIN) $(TGT_BIN_$(d))
CLEAN           := $(CLEAN)   $(TGT_BIN_$(d)) $(OBJS_$(d)) $(DEPS_$(d))

# local rules
$(d)/hercules.exe: $(d)/libxt/xt.lib              \
                   hercules/cardinfo.o            \
                   hercules/lines.o               \
