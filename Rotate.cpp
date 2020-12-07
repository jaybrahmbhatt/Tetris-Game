

//#include "Rotate.h"
//Shape Shape::RotateLeft() const{
//	    if (pieceShape == SquareShape)
//	        return *this;
//
//	    Shape result;
//	    result.pieceShape = pieceShape;
//	    for (int i = 0; i < 4; ++i) {
//	        result.SetX(i, y(i));
//	        result.SetY(i, -x(i));
//	    }
//	    return result;
//	}
//
//Shape Shape::RotateRight() const
//	{
//	    if (pieceShape == SquareShape)
//	        return *this;
//
//	    Shape result;
//	    result.pieceShape = pieceShape;
//	    for (int i = 0; i < 4; ++i) {
//	        result.SetX(i, -y(i));
//	        result.SetY(i, x(i));
//	    }
//	    return result;
//	}
