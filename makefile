DIRECTORIES = $(addprefix -I./,$(shell ls -d ./src/*/))
TARGET_NAME = Splines

CXX_FLAGS = -isystem C:\MinGW\include -std=c++1y -O2 -msse2 -mfpmath=sse -g -pipe -I. -I./src $(DIRECTORIES) -DBT_USE_DOUBLE_PRECISION=ON -DUSE_BULLET
ADDITIONAL_FLAGS = \
-Werror=return-type
-Wswitch-enum \

CXX = C:\MinGw\bin\g++.exe
SRC = ./src
BIN = ./bin
OBJ_DIR = ./obj

LIBS = -lboost_system -lboost_filesystem -lboost_thread -lboost_date_time

TARGETS = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)

OBJS = $(TARGETS:%.cpp=$(OBJ_DIR)/%.o)

DEP = $(OBJS:%.o=%.d)

$(BIN)/$(TARGET_NAME): $(OBJS)
	@echo "Linking: $@"
	@$(CXX) $^ -o $@ $(LIBS)

-include $(DEP)

$(OBJ_DIR)/%.o : %.cpp
	@echo "Compiling: $< "
	@mkdir -p $(@D)
	@$(CXX) $(CXX_FLAGS) $(ADDITIONAL_FLAGS) -MMD -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o $(OBJ_DIR)/*.d
	rm $(BIN)/$(TARGET_NAME).exe

run: $(BIN)/$(TARGET_NAME)
	(cd $(BIN) && ./$(TARGET_NAME).exe)

debug: $(BIN)/$(TARGET_NAME)
	(cd $(BIN) && gdb $(TARGET_NAME).exe)

.PHONY: clean
