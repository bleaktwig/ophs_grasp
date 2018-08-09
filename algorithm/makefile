# target executable
TARGET_EXEC ?= ophs_grasp.out

# working directories
BUILD_DIR ?= ./bin
SRC_DIRS ?= ./src

# compiler flags:
#   -g		  adds debugging information
#   -std=c11  uses the 2011 C standard for compiling
#   -Wall	  turns on most compiler warnings
#	-lm		  links the math library
CC = gcc
CFLAGS = -g -std=c11 -Wall
LDFLAGS = -lm

SRCS := $(shell find $(SRC_DIRS) -name *.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
