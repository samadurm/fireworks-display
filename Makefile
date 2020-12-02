LIBGLUT=/usr/lib/x86_64-linux-gnu/libglut.so

all:		src/main.cpp
		g++ -o main  src/main.cpp -I./include -lGL  -lGLU $(LIBGLUT) -lm