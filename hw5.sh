#!/bin/sh

echo "Plot the function y = e^(-0.2x) sin(3x)"
echo "  using GL_POINTS..."
./plot2d -w 1024 -h 768 -m points -d 75
echo "  using GL_LINES..."
./plot2d -w 1024 -h 768 -m lines -d 200
echo "DONE"

echo "Plot the function z = 5cos(2x + 3sin(2y)) e^(-n(x^2 + y^2))"
echo "  using GL_QUADS..."
echo "  not implemented"
echo "  using GL_TRIANGLES..."
echo "  not implemented"
echo "DONE"

echo "Render a Rubik's cube"
echo "  without gaps..."
echo "  not implemented"
echo "  with gaps..."
echo "  not implemented"
echo "DONE"

echo "Render a 20x20x20 grid of Rubik's cubes"
echo "  not implemented"
echo "DONE"
