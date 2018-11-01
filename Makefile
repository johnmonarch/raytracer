# Makefile for ray3
#

OBJS = 	main.o     \
	model.o       \
	environment.o \
	object.o      \
	sceneobj.o    \
	triple.o      \
	list.o        \
	getnum.o      \
	plane.o       \
	light.o       \
	illuminate.o  \
	sphere.o      \
	polygon.o     \
	polytest.o    \
	rectangle.o   \
	triangle.o    \
	ray.o         \
	image.o

CFLAGS = -Wall -g -O2

all: main

main: ${OBJS}
	gcc -o ray3 -g ${OBJS} -lm

${OBJS}: ray.h rayhdrs.h triple.h list.h Makefile

clean:
	rm *.o

test:
	./ray3 world.txt output.ppm 400 8
