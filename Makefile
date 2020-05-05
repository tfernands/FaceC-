# Name of the project
PROJ_NAME=main

#project paths
CPP_PATH=./src
HPP_PATH=./include
BUILD_PATH=./build
XTL_PATH=./libs/xtensor
XTENSOR_PATH=./libs/xtl
TENSORFLOW_PATH=./../tensorflow-master

# .cpp files
CPP_SOURCE=$(wildcard $(CPP_PATH)/*.cpp)
 
# .hpp files
HPP_SOURCE=$(wildcard $(HPP_PATH)/*.hpp)
 
# Object files
OBJ=$(subst .cpp,.o,$(subst $(CPP_PATH),$(BUILD_PATH),$(CPP_SOURCE)))
 
# Compiler
CC=g++
 
# Flags for compiler
CC_FLAGS=-W\
         -I$(HPP_PATH)\
         -I$(XTL_PATH)/include/\
         -I$(XTENSOR_PATH)/include/\
         -I$(TENSORFLOW_PATH)/\
         -I$(TENSORFLOW_PATH)/tensorflow/lite/tools/make/downloads/absl/\
         -I$(TENSORFLOW_PATH)/tensorflow/lite/tools/make/downloads/flatbuffers/include/\
         -Bstatic -L$(TENSORFLOW_PATH)/tensorflow/lite/tools/make/gen/windows_x86_32/lib/\
         -ltensorflow-lite -Lbenchmark-lib.a -pthread

#
# Compilation and linking
#
all: buildFolder $(PROJ_NAME)
 
$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^ $(CC_FLAGS) 

$(BUILD_PATH)/%.o: $(CPP_PATH)/%.cpp $(HPP_PATH)/%.hpp
	$(CC) -c $(CC_FLAGS) -o $@ $<

$(BUILD_PATH)/main.o: $(CPP_PATH)/main.cpp $(HPP_SOURCE)
	$(CC) -c $(CC_FLAGS) -o $@ $<

clean:
	@ $(RM) $(BUILD_PATH)/*.o $(PROJ_NAME) *~
	@ $(RM) $(PROJ_NAME).exe
	@ rmdir $(BUILD_PATH)

buildFolder:
	@ mkdir -p $(BUILD_PATH)

run: all
	$(PROJ_NAME).exe

.PHONY: all clean run