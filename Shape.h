/*
 * Shape.h
 */

#include "Rotate.h"
#include "Tetrominoes.h"
#ifndef SHAPE_H
#define SHAPE_H


class Shape
{
public:

    Shape() { SetTetrominoesShape(NoShape); }
    void SetRandomShape();
    Tetrominoes GetTetrominoesShape() const { return pieceShape; }

    void SetTetrominoesShape(Tetrominoes shape);

    //Getters for x and y coordinates so that they can be encapsulated

    int xcoords(int index) const { return coordinates[index][0]; }
    int ycoords(int index) const { return coordinates[index][1]; }

    int MinXcoord() const;
    int MaxXcoord() const;
    int MinYcoord() const;
    int MaxYcoord() const;

    Shape RotateLeft() const;
    Shape RotateRight() const;

private:
    Tetrominoes pieceShape;
    int coordinates[4][2];

    //Private setters for coordinates so that only public functions of this class can access coordinates
    void SetXcoords(int index, int x) { coordinates[index][0] = x; }
    void SetYcoords(int index, int y) { coordinates[index][1] = y; }

};

#endif
