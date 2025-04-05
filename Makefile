# Target and sources directories
TARGET 			:= hash_table
BUILD_DIR 		:= ./build
SRC_DIRS 		:= ./src

# Compilations flags
CFLAGS 			:= -Wall -Wextra -pedantic -g
LDFLAGS         := 

# Find all the C files we want to compile
SRCS 		:= $(shell find $(SRC_DIRS) -name '*.c')
SRCS		+= main.c

# Prepends BUILD_DIR and appends .o to every src file
# As an example, ./your_dir/hello.c turns into ./build/./your_dir/hello.o
OBJS 		:= $(SRCS:%.c=$(BUILD_DIR)/%.o)

# String substitution (suffix version without %).
# As an example, ./build/hello.o turns into ./build/hello.d
DEPS 		:= $(OBJS:.o=.d)

# Every folder in ./src will need to be passed to GCC so that it can find header files
INC_DIRS 	:= $(shell find $(SRC_DIRS) -type d)
# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA. GCC understands this -I flag
INC_FLAGS 	:= $(addprefix -I,$(INC_DIRS))

# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the output.
CPPFLAGS 	:= $(INC_FLAGS) -MMD -MP

# The final build step.
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Build step for C source
$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	rm -f -r $(BUILD_DIR)
	rm -f $(TARGET)

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
-include $(DEPS)
