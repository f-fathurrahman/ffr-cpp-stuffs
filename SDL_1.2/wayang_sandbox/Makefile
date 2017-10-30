#include make.inc
CXX = g++
CXX_FLAGS = -O3
CXX_INCLUDES = -I/usr/include/SDL

LIBS = -lSDL

SRC = \
sprig/SPG_extended.c  sprig/SPG_polygon.c     sprig/SPG_rotation.c \
sprig/SPG_misc.c  sprig/SPG_primitives.c  sprig/SPG_surface.c \
wayang/list.cpp  wayang/wayang.cpp

OBJS = \
sprig/SPG_extended.o  sprig/SPG_polygon.o     sprig/SPG_rotation.o \
sprig/SPG_misc.o  sprig/SPG_primitives.o  sprig/SPG_surface.o \
wayang/list.o  wayang/wayang.o

lib: $(OBJS)
	ar rcs libmain.a $(OBJS)

sprig/SPG_extended.o:
	$(CXX) $(CXX_FLAGS) $(CXX_INCLUDES) sprig/SPG_extended.c -c -o sprig/SPG_extended.o

sprig/SPG_polygon.o:
	$(CXX) $(CXX_FLAGS) $(CXX_INCLUDES) sprig/SPG_polygon.c -c -o sprig/SPG_polygon.o

sprig/SPG_rotation.o:
	$(CXX) $(CXX_FLAGS) $(CXX_INCLUDES) sprig/SPG_rotation.c -c -o sprig/SPG_rotation.o

sprig/SPG_misc.o:
	$(CXX) $(CXX_FLAGS) $(CXX_INCLUDES) sprig/SPG_misc.c -c -o sprig/SPG_misc.o

sprig/SPG_primitives.o:
	$(CXX) $(CXX_FLAGS) $(CXX_INCLUDES) sprig/SPG_primitives.c -c -o sprig/SPG_primitives.o

sprig/SPG_surface.o:
	$(CXX) $(CXX_FLAGS) $(CXX_INCLUDES) sprig/SPG_surface.c -c -o sprig/SPG_surface.o

wayang/list.o:
	$(CXX) $(CXX_FLAGS) $(CXX_INCLUDES) wayang/list.cpp -c -o wayang/list.o

wayang/wayang.o:
	$(CXX) $(CXX_FLAGS) $(CXX_INCLUDES) wayang/wayang.cpp -c -o wayang/wayang.o
