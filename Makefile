LIBGLUT=/usr/lib/x86_64-linux-gnu/libglut.so

all:		src/main.cpp src/mjbcone.cpp
		g++ -o main  src/main.cpp src/mjbcone.cpp -I./include -lGL  -lGLU $(LIBGLUT) -lm