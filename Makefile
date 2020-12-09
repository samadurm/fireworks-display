LIBGLUT=/usr/lib/x86_64-linux-gnu/libglut.so

all:		src/main.cpp src/mjbcone.cpp src/lighting.cpp src/texture_mapping.cpp
		g++ -o main  src/main.cpp src/mjbcone.cpp src/lighting.cpp src/texture_mapping.cpp -I./include -lGL  -lGLU $(LIBGLUT) -lm