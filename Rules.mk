# subdirectories
dir := $(d)/libxt
include $(dir)/Rules.mk

# local variables
TGT_BIN_$(d)    := $(d)/hercinfo.exe              \

TGT_BIN         := $(TGT_BIN) $(TGT_BIN_$(d))
CLEAN           := $(CLEAN)   $(TGT_BIN_$(d))

# local rules
$(d)/hercinfo.exe: $(d)/libxt/xt.lib

