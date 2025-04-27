# Compiler variables - #
COMPILER = g++
CPP_VERSION = -std=c++2b
COMPILER_FLAGS = $(CPP_VERSION) -MMD -MP -I $(INCLUDES_DIR)
LINKER_FLAGS =
LINKER_LIBRARIES = -pthread -lssl -lcrypto

dbg = 0
DEBUG_OPTION =
# -------------------- #

# Application -------- #
APPLICATION_NAME = clancats-server
APPLICATION_TARGET = $(BINARIES_DIR)/$(APPLICATION_NAME)
# -------------------- #

# Files and folders -- #
INCLUDES_DIR = inc
SOURCES_DIR = src
SOURCES_SUBDIRS = $(shell find '$(SOURCES_DIR)' -type d)
OBJECTS_DIR = obj
BINARIES_DIR = bin
INSTALL_DIR = /usr/local/bin

SOURCE_FILES = $(shell find '$(SOURCES_DIR)' -name '*.cpp')
OBJECT_FILES = $(patsubst $(SOURCES_DIR)/%.cpp, $(OBJECTS_DIR)/%.o, $(SOURCE_FILES))
GENERAL_INCLUDE_FILES = $(shell find '$(INCLUDES_DIR)/General' -name '*.hpp')
DEPENDENCY_FILES = $(OBJECT_FILES:.o=.d)
# -------------------- #

# Check for debug option #
ifeq ($(dbg),1)
	DEBUG_OPTION = -g
else
	DEBUG_OPTION =
endif
# ---------------------- #

# Building ----------- #
.PHONY: all initialize print_creation clean run install uninstall debug

all: initialize print_creation $(APPLICATION_TARGET)

initialize:
	@echo "Initialize folder structure..."
	mkdir -p $(BINARIES_DIR)
	mkdir -p $(OBJECTS_DIR)
	mkdir -p $(subst $(SOURCES_DIR),$(OBJECTS_DIR),$(foreach folders, $(SOURCES_SUBDIRS), $(folders)))
	rm -f $(DEPENDENCY_FILES)

print_creation:
	@echo "Creating $(APPLICATION_NAME)..."

clean:
	@echo "Cleaning up project..."
	rm -rf $(BINARIES_DIR)
	rm -rf $(OBJECTS_DIR)

run: all
	@echo "Starting $(APPLICATION_NAME)..."
	$(APPLICATION_TARGET)

install: all
	@echo "Installing by moving $(APPLICATION_NAME) to $(INSTALL_DIR)..."
	cp $(APPLICATION_TARGET) $(INSTALL_DIR) 

uninstall:
	@echo "Uninstalling by removing $(APPLICATION_NAME) in $(INSTALL_DIR)..."
	rm $(INSTALL_DIR)/$(APPLICATION_NAME)

debug: all
	@echo "Starting gdb..."
	gdb $(APPLICATION_TARGET)

# Build the binary from the object files
$(APPLICATION_TARGET): $(OBJECT_FILES)
	$(COMPILER) $(LINKER_FLAGS) $^ -o $@ $(LINKER_LIBRARIES)

# Build all object files from the source
$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.cpp $(INCLUDES_DIR)/%.h $(GENERAL_INCLUDE_FILES)
	$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@ $(DEBUG_OPTION) 

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.cpp $(GENERAL_INCLUDE_FILES)
	$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@ $(DEBUG_OPTION) 

# Include dependency files
-include $(DEPENDENCY_FILES)
# -------------------- #
