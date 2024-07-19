SRC_DIR := ./src
BUILD_DIR := ./build

# find all source files in src directory that end with .cpp
SRCS := $(shell find $(SRC_DIR) -name '*.cpp')

# string substitution for object files. ex: ./src/main.cpp => ./build/obj/main.o
OBJS := $(patsubst $(SRC_DIR)%.cpp,$(BUILD_DIR)/obj%.o,$(SRCS))

# header file dependencies for source files
DEPS := $(patsubst %.o,%.d,$(OBJS))

# name of executable
TARGET_EXEC := graphics

# libraries that need to be linked with object files to create executable
LIBS := -l SDL2 -l SDL2_image -l GL -l fmt

# --std is the version of c++. -Wall is include all warnings. -g is for debugging info. -MD creates header dependency files
CPPFLAGS := --std=c++20 -Wall -g -MD

# default video driver is to wayland but can be changed if set in command line
DRIVER := wayland

.SILENT:

all: $(BUILD_DIR)/$(TARGET_EXEC)

# clean the build directory
clean: $(BUILD_DIR)
	rm -r $(BUILD_DIR)
	echo "Cleaned the build directory and its contents."

$(BUILD_DIR):
	mkdir $(BUILD_DIR)
	mkdir $(BUILD_DIR)/obj
	echo "Created the build directory."

# create the object files
$(OBJS): $(BUILD_DIR)/obj%.o: $(SRC_DIR)%.cpp
	# compile and assemble source files
	g++ $(CPPFLAGS) -c $< -o $@
	echo "Compiled '$<' into '$@'..."

# create executable
$(BUILD_DIR)/$(TARGET_EXEC): $(BUILD_DIR) $(OBJS)
	echo "Finished compiling source files."
	g++ $(OBJS) -o $(BUILD_DIR)/$(TARGET_EXEC) $(LIBS)
	echo "Linked object files into executable."

run:
	SDL_VIDEODRIVER=$(DRIVER) $(BUILD_DIR)/$(TARGET_EXEC)

-include $(DEPS)
