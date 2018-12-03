
SRCS := Reusable/Bevel.cpp DSystemInfo.cpp DSystemInfoView.cpp DSystemInfoWindow.cpp main.cpp
OBJS := $(SRCS:%.cpp=%.o)
EXE_NAME := DSystemInfo

all: binary

%.o: %.cpp
	gcc -c $<

binary: $(OBJS)
	gcc -o $(EXE_NAME) $(OBJS)

.PHONY: all clean

clean:
	rm -f *.o $(EXE_NAME)
