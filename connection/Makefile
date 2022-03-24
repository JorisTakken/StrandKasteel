CXX= g++
CXXFLAGS = -I/usr/local/include/opencv4/ -Wall -std=c++1z
LDFLAGS=-ljack -L/usr/local/lib/ -lopencv_calib3d -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_video -lopencv_videoio -lopencv_videostab
# the cpp files from the current project to include
SRC_PROJECT = mapEffects.cpp 
# the directory to the folder with the shared modules
SHAREDCODE_PATH = ../sharedCode/
# the modules to include
MODULES = oscillators utilities effects
TARGET=example

# append shared code path prefix to modules
MODULE_PATHS = $(addprefix $(SHAREDCODE_PATH),$(MODULES))
# module .mk files
MODULE_MK = $(patsubst %,%/module.mk,$(MODULE_PATHS))
# include the description for each module
SRC_MODULES =
include $(MODULE_MK)
# create src list for all .cpp files
SRC = $(addprefix $(SHAREDCODE_PATH),$(SRC_MODULES))
SRC+= $(SRC_PROJECT)
# look for include files in
# each of the modules
CXXFLAGS += $(patsubst %,-I%,./$(MODULE_PATHS))
# determine the object files --> replace all .cpp in SRC with .o
OBJ := $(patsubst %.cpp,%.o, $(filter %.cpp,$(SRC)))
# log OBJ
$(info $$OBJ is [${OBJ}])

# link the program
$(TARGET):$(OBJ)
	$(CXX) -o $@ $(OBJ) $(LDFLAGS)

# -o $*.o --> write .o file to the directory of the current target
.cpp.o:
	$(CXX) -c $< $(CXXFLAGS) $(LIBS) -o $*.o

# plot:
# 	python3 $(SHAREDCODE_PATH)stereoutils/plot.py

clean:
	rm $(TARGET)
	rm $(OBJ)
