
# Build Rules

CFLAGS += $(cflags-y)

all: force $(ELF) $(BIN) $(SREC)

$(ELF): $(obj-y)
	$(LD) -T $(LINKER_FILE) $(LDFLAGS) $(obj-y) -o $@

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $^ $@

$(SREC): $(ELF)
	$(OBJCOPY) -O srec $^ $@

clean:
	rm -rf $(obj-y) $(ELF) $(BIN) $(SREC)

run:
	qemu-system-arm -M versatilepb -m 128 -kernel $(ELF) -serial stdio

force:
