#include <stdlib.h>
#include <algorithm>
#include "Shape.h"

using namespace std;

void Shape::SetTetrominoesShape(Tetrominoes shape)
{
    static const int coordsTable[8][4][2] = {
        { { 0, 0 },   { 0, 0 },   { 0, 0 },   { 0, 0 } },
        { { 0, -1 },  { 0, 0 },   { -1, 0 },  { -1, 1 } },
        { { 0, -1 },  { 0, 0 },   { 1, 0 },   { 1, 1 } },
        { { 0, -1 },  { 0, 0 },   { 0, 1 },   { 0, 2 } },
        { { -1, 0 },  { 0, 0 },   { 1, 0 },   { 0, 1 } },
        { { 0, 0 },   { 1, 0 },   { 0, 1 },   { 1, 1 } },
        { { -1, -1 }, { 0, -1 },  { 0, 0 },   { 0, 1 } },
        { { 1, -1 },  { 0, -1 },  { 0, 0 },   { 0, 1 } }
    };

    for (int i = 0; i < 4 ; i++) {
        for (int j = 0; j < 2; ++j)
            coordinates[i][j] = coordsTable[shape][i][j];
    }
    pieceShape = shape;
}


void Shape::SetRandomShape()
{
  int s = rand() % 7 + 1;
  SetTetrominoesShape(Tetrominoes(s));
}

int Shape::MinXcoord() const
{
  int m = coordinates[0][0];
  for (int i=0; i<4; i++) {
      m = min(m, coordinates[i][0]);
  }
  return m;
}

int Shape::MaxXcoord() const
{
  int m = coordinates[0][0];
  for (int i=0; i<4; i++) {
      m = max(m, coordinates[i][0]);
  }
  return m;
}

int Shape::MinYcoord() const
{
  int m = coordinates[0][1];
  for (int i=0; i<4; i++) {
      m = min(m, coordinates[i][1]);
  }
  return m;
}

int Shape::MaxYcoord() const
{
  int m = coordinates[0][1];
  for (int i=0; i<4; i++) {
      m = max(m, coordinates[i][1]);
  }
  return m;
}

Shape Shape::RotateLeft() const
{
    if (pieceShape == SquareShape)
        return *this;

    Shape afterRRotate;
    afterRRotate.pieceShape = pieceShape;
    for (int i = 0; i < 4; ++i) {
    	afterRRotate.SetXcoords(i, ycoords(i));
    	afterRRotate.SetYcoords(i, -xcoords(i));
    }
    return afterRRotate;
}

Shape Shape::RotateRight() const
{
    if (pieceShape == SquareShape)
        return *this;

    Shape afterLRotate;
    afterLRotate.pieceShape = pieceShape;
    for (int i = 0; i < 4; ++i) {
    	afterLRotate.SetXcoords(i, -ycoords(i));
    	afterLRotate.SetYcoords(i, xcoords(i));
    }
    return afterLRotate;
}
