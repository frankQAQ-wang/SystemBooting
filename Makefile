CUR_DIR := $(shell pwd)
SRC_DIR := $(CUR_DIR)/src
LIB_DIR := $(CUR_DIR)/lib
INCLUDE_DIR := $(CUR_DIR)/include
TOOLS_DIR := $(CUR_DIR)/tools
BUILD_DIR := $(CUR_DIR)/build
TOOLS_DIR := $(CUR_DIR)/tools
OBJ_DIR := $(BUILD_DIR)/obj
BOOT_OBJ := $(BUILD_DIR)/obj/boot.o
CC := gcc
LD := ld
OBJCOPY := objcopy
LD_FILE := $(CUR_DIR)/boot.ld
ELF_FILE := $(BUILD_DIR)/boot.elf
BIN_FILE := $(BUILD_DIR)/boot.bin
IMG_FILE := $(CUR_DIR)/boot.img
FILE_SIZE := 24576

CFLAGS := -fno-asynchronous-unwind-tables -nostdinc -isystem $(shell $(CC) -print-file-name=include) -m32 -g -Os -march=i386 -mregparm=3 -fno-strict-aliasing -fomit-frame-pointer -fno-pic -mno-mmx -mno-sse -ffreestanding -fno-toplevel-reorder -fno-stack-protector -I$(INCLUDE_DIR)
SFLAGS := $(CFLAGS) -D__ASSEMBLY__
LFLAGS := -m elf_x86_64 -T $(LD_FILE)
OFLAGS := -O binary

SRCS := $(wildcard $(SRC_DIR)/*.c $(LIB_DIR)/*.c $(SRC_DIR)/*.S $(LIB_DIR)/*.S)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS := $(OBJS:$(LIB_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS := $(OBJS:$(SRC_DIR)/%.S=$(OBJ_DIR)/%.o)
OBJS := $(OBJS:$(LIB_DIR)/%.S=$(OBJ_DIR)/%.o)

all:start_compile $(OBJS) $(ELF_FILE) $(BIN_FILE) $(IMG_FILE) end_compile
start_compile:
	@echo '##################################################'
	@echo '                   start compile'
	@echo '##################################################'
	@echo
	@mkdir -p $(OBJ_DIR)
end_compile:
	@echo
	@echo '##################################################'
	@echo '                   end compile'
	@echo '##################################################'

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(wildcard $(INCLUDE_DIR)/*.h)
	@echo CC $<
	@$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ_DIR)/%.o: $(LIB_DIR)/%.c $(wildcard $(INCLUDE_DIR)/*.h)
	@echo CC $<
	@$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.S $(wildcard $(INCLUDE_DIR)/*.h)
	@echo CC $<
	@$(CC) $(SFLAGS) -c -o $@ $<
$(OBJ_DIR)/%.o: $(LIB_DIR)/%.S $(wildcard $(INCLUDE_DIR)/*.h)
	@echo CC $<
	@$(CC) $(SFLAGS) -c -o $@ $<

$(ELF_FILE): $(OBJS) $(LD_FILE)
	@echo LD $@
	@$(LD) $(LFLAGS) $(filter %.o,$^) -o $@
$(BIN_FILE): $(ELF_FILE)
	@echo OBJCOPY $<
	@$(OBJCOPY) $(OFLAGS) $< $@
$(IMG_FILE): $(BIN_FILE)
	@$(MAKE) -C $(TOOLS_DIR) BIN_FILE=$(BIN_FILE) IMG_FILE=$(IMG_FILE) FILE_SIZE=$(FILE_SIZE)
run: all
	qemu-system-x86_64 $(IMG_FILE)
debug: all
	qemu-system-x86_64 $(IMG_FILE) -s -S
clean:
	@$(MAKE) -C $(TOOLS_DIR) clean
	rm -rf $(BUILD_DIR)
disclean:
	@$(MAKE) -C $(TOOLS_DIR) clean
	rm -rf $(BUILD_DIR) $(IMG_FILE)
.PHONY: all clean disclean run debug
