CC      = wcc
CFLAGS  = -0 -za99 -we -q -bt=dos -i=include
LD      = wlib
LDFLAGS = -n -q

TARGET  = xt.lib

OBJECTS = hercules.o              \

.PHONY: all clean

all: $(TARGET)

clean:
	rm -f $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) $@ $(patsubst %,+%,$^)

$(OBJECTS): %.o: %.c
	$(CC) $(CFLAGS) $^ -fo=$@
