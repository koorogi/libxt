# subdirectories
dir := $(d)/libxt
include $(dir)/Rules.mk

dir := $(d)/tests
include $(dir)/Rules.mk

dir := $(d)/unittest
include $(dir)/Rules.mk

# local variables
TGT_BIN_$(d)    := $(d)/bench.exe                 \
                   $(d)/tests.exe                 \
                   $(d)/unittest.exe              \

OBJS_$(d)       := $(d)/bench.o                   \
                   $(d)/tests.o                   \
                   $(d)/unittest.o                \

DEPS_$(d)       := $(OBJS_$(d):%.o=%.d)
TGT_BIN         := $(TGT_BIN) $(TGT_BIN_$(d))
CLEAN           := $(CLEAN)   $(TGT_BIN_$(d)) $(OBJS_$(d)) $(DEPS_$(d))

# local rules
$(d)/bench.exe:    $(d)/libxt/xt.lib              \
                   tests/clear.o                  \
                   tests/clear2.o                 \
                   tests/cube.o                   \
                   tests/fixedpoint.o             \
                   tests/fixedpoint2.o            \
                   tests/helpers.o                \
                   tests/lines.o                  \
                   tests/nop.o                    \
                   tests/quaternion.o             \
                   tests/quaternion2.o            \

$(d)/tests.exe:    $(d)/libxt/xt.lib              \
                   tests/cardinfo.o               \
                   tests/cube.o                   \
                   tests/fixedpoint.o             \
                   tests/fixedpoint2.o            \
                   tests/helpers.o                \
                   tests/lines.o                  \

$(d)/unittest.exe: $(d)/libxt/xt.lib              \
                   unittest/bitshift.o            \
                   unittest/bitshift2.o           \
                   unittest/fixedpoint.o          \
                   unittest/unittest.o            \
