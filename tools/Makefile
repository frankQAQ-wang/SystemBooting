CC := gcc
CFLAGS := -g
PACKAGE := $(shell pwd)/package

all:package
package: $(PACKAGE) $(BIN_FILE)
	@echo PACKAGE $(BIN_FILE)
	@$(PACKAGE) $(IMG_FILE) $(FILE_SIZE) $(BIN_FILE)
$(PACKAGE): $(PACKAGE).c
	@echo CC $^
	@$(CC) $(CFLAGS) $^ -o $@
clean:
	rm -rf $(PACKAGE)
.PHONY: all clean
