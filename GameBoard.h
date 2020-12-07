#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "Shape.h"
#include <wx/wx.h>

class GameBoard : public wxPanel
{

public:
    GameBoard(wxFrame *parent);
    void Start();
    void Pause();


protected:
    void OnPaint(wxPaintEvent& event);
    void OnKeyDown(wxKeyEvent& event);
    void OnTimer(wxCommandEvent& event);

private:
    enum { BoardWidth = 10, BoardHeight = 22 };

    wxTimer *timer;
	bool isStarted;
	bool isPaused;
	bool isFallingFinished;
	Shape currentPiece;
	int curX;
	int curY;
	int numLinesRemoved;
	Tetrominoes board[BoardWidth * BoardHeight];

	wxStatusBar *GameStatusBar;

    Tetrominoes & ShapeAt(int x, int y) { return board[(y * BoardWidth) + x]; }

    void ClearBoard();
	void DropDown();
	void OneLineDown();

    int SquareWidth() { return GetClientSize().GetWidth() / BoardWidth; }
    int SquareHeight() { return GetClientSize().GetHeight() / BoardHeight; }

    void PieceDropped();
    void RemoveFullLines();
    void NewPiece();
    bool canRotate(const Shape& newPiece, int newX, int newY);
    void DrawSquare(wxPaintDC &dc, int x, int y, Tetrominoes shape);


};

#endif
