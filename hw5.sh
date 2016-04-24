#!/bin/sh

make 

if [ $? -ne 0 ] ; then
	exit 1
fi

echo "Plot the function y = e^(-0.2x) sin(3x)"
echo "  using GL_POINTS..."
./plot2d -w 1024 -h 768 -m points -d 75
echo "  using GL_LINES..."
./plot2d -w 1024 -h 768 -m lines -d 200
echo "DONE"

echo "Plot the function z = 5cos(2x + 3sin(2y)) e^(-n(x^2 + y^2))"
echo "  using GL_QUADS..."
./plot3d -w 1024 -h 768 -m quads -d 50 -o
./plot3d -w 1024 -h 768 -m quads -d 200
echo "  using GL_TRIANGLES..."
./plot3d -w 1024 -h 768 -m triangles -d 50 -o
./plot3d -w 1024 -h 768 -m triangles -d 200
echo "DONE"

echo "Render a Rubik's cube"
echo "  without gaps..."
./rubik -w 1024 -h 768 -g 0.0 -o
./rubik -w 1024 -h 768 -g 0.0
echo "  with gaps..."
./rubik -w 1024 -h 768 -g 0.1 -o
./rubik -w 1024 -h 768 -g 0.1
echo "DONE"

echo "Render a 20x20x20 grid of Rubik's cubes"
./rubik20 -w 1024 -h 768 -g 0.1 -o
./rubik20 -w 1024 -h 768 -g 0.1
echo "DONE"
