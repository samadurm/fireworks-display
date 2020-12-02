LIBGLUT=/usr/lib/x86_64-linux-gnu/libglut.so

all:		main.cpp
		g++ -o main  main.cpp  -lGL  -lGLU $(LIBGLUT) -lm