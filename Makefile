
SRCS := Reusable/Bevel.cpp DSystemInfo.cpp DSystemInfoView.cpp DSystemInfoWindow.cpp main.cpp
OBJS := $(SRCS:%.cpp=%.o)
EXE_NAME := DSystemInfo

LIB_INCLUDE_DIR := /boot/system/lib
LINKER_LIBS := -lstdc++ -lroot -lbe

all: binary

%.o: %.cpp
	gcc -c $< -o $@

binary: $(OBJS)
	gcc -I$(LIB_INCLUDE_DIR) $(LINKER_LIBS) -o $(EXE_NAME) $(OBJS)

.PHONY: all clean

clean:
	rm -f $(OBJS) $(EXE_NAME)
