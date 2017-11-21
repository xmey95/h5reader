INC_DIR = HDF5_HOME/include
LIB_DIR = HDF5_HOME/lib
# compiler flags:
#  -Std defines compiler version
CXXFLAGS  = -std=c++11 -I$(INC_DIR)
DEPS = h5reader.h

LDFLAGS  =  -L$(LIB_DIR)

LIBS = -lhdf5_hl -lhdf5 -lz -lm -ldl

# the build target executable:
TARGET = h5reader
OBJS = $(TARGET).o

LINK.o = $(LINK.cpp)

run: $(TARGET)
	./$(TARGET) dset.h5

$(TARGET).o: $(TARGET).cpp h5reader.h

$(TARGET): $(OBJS) $(LIBS)

clean:
	$(RM) $(TARGET) $(OBJS)

.PHONY: run clean
