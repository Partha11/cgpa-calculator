CXX      := -g++
CXXFLAGS := -w
LDFLAGS  := -L/usr/lib -lstdc++ -lm
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/apps
TARGET   := program
INCLUDE  := -Iinclude/
SRC      :=                           \
	$(wildcard src/module1/*.cpp) \
	$(wildcard src/module2/*.cpp) \
	$(wildcard src/*.cpp)         \

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)
RUN := ./build/apps/program

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $(OBJECTS)
	$(RUN)

.PHONY: all build clean

build:
	-rm -rf $(BUILD)/*
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

clean:
	-rm -rf $(BUILD)/*
