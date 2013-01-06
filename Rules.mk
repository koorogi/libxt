# subdirectories
dir := $(d)/libxt
include $(dir)/Rules.mk

dir := $(d)/hercules
include $(dir)/Rules.mk

dir := $(d)/bench
include $(dir)/Rules.mk

# local variables
TGT_BIN_$(d)    := $(d)/bench.exe                 \
                   $(d)/hercules.exe              \

OBJS_$(d)       := $(d)/bench.o                   \
                   $(d)/hercules.o                \

DEPS_$(d)       := $(OBJS_$(d):%.o=%.d)
TGT_BIN         := $(TGT_BIN) $(TGT_BIN_$(d))
CLEAN           := $(CLEAN)   $(TGT_BIN_$(d)) $(OBJS_$(d)) $(DEPS_$(d))

# local rules
$(d)/bench.exe:    $(d)/libxt/xt.lib              \
                   bench/hercules.o               \
                   bench/nop.o                    \

$(d)/hercules.exe: $(d)/libxt/xt.lib              \
                   hercules/cardinfo.o            \
                   hercules/lines.o               \
