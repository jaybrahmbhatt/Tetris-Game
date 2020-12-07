#include "GameBoard.h"

GameBoard::GameBoard(wxFrame *parent)
       : wxPanel(parent, wxID_ANY, wxDefaultPosition,
             wxDefaultSize, wxBORDER_NONE)
{
    timer = new wxTimer(this, 1);

    GameStatusBar = parent->GetStatusBar();
    isStarted = false;
    isPaused = false;
    isFallingFinished = false;

    numLinesRemoved = 0;
    curX = 0;
    curY = 0;

    ClearBoard();

    Connect(wxEVT_PAINT, wxPaintEventHandler(GameBoard::OnPaint));
    Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(GameBoard::OnKeyDown));
    Connect(wxEVT_TIMER, wxCommandEventHandler(GameBoard::OnTimer));
}


void GameBoard::Start()
{
    if (isPaused)
        return;

    isStarted = true;
    isFallingFinished = false;
    numLinesRemoved = 0;
    ClearBoard();

    NewPiece();
    timer->Start(300);
}

void GameBoard::ClearBoard()
{
    for (int i = 0; i < BoardHeight * BoardWidth; ++i)
        board[i] = NoShape;
}

void GameBoard::Pause()
{
    if (!isStarted)
        return;

    isPaused = !isPaused;
    if (isPaused) {
        timer->Stop();
        GameStatusBar->SetStatusText(wxT("The Game is Paused"));
    } else {
        timer->Start(300);
        wxString str;
        str.Printf(wxT("%d"), numLinesRemoved);
        GameStatusBar->SetStatusText(str);
    }
    Refresh();
}


void GameBoard::OnKeyDown(wxKeyEvent& event)
{
    if (!isStarted || currentPiece.GetTetrominoesShape() == NoShape) {
        event.Skip();
        return;
    }

    int keycode = event.GetKeyCode();

    if (keycode == 'p' || keycode == 'P') {
	Pause();
        return;
    }

    if (isPaused)
        return;

    switch (keycode) {
    case WXK_LEFT:
        canRotate(currentPiece, curX - 1, curY);
        break;
    case WXK_RIGHT:
        canRotate(currentPiece, curX + 1, curY);
        break;
    case WXK_DOWN:
        canRotate(currentPiece.RotateRight(), curX, curY);
        break;
    case WXK_UP:
        canRotate(currentPiece.RotateLeft(), curX, curY);
        break;
    case WXK_SPACE:
        DropDown();
        break;
    case 'd':
        OneLineDown();
        break;
    case 'D':
        OneLineDown();
        break;
    default:
        event.Skip();
    }

}

void GameBoard::OnTimer(wxCommandEvent& event)
{
    if (isFallingFinished) {
        isFallingFinished = false;
        NewPiece();
    } else {
        OneLineDown();
    }
}



void GameBoard::DropDown()
{
    int newY = curY;
    while (newY > 0) {
        if (!canRotate(currentPiece, curX, newY - 1))
            break;
        --newY;
    }
    PieceDropped();
}

void GameBoard::OneLineDown()
{
    if (!canRotate(currentPiece, curX, curY - 1))
        PieceDropped();
}
void GameBoard::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);

    wxSize size = GetClientSize();
    int boardTop = size.GetHeight() - BoardHeight * SquareHeight();


    for (int i = 0; i < BoardHeight; ++i) {
        for (int j = 0; j < BoardWidth; ++j) {
            Tetrominoes shape = ShapeAt(j, BoardHeight - i - 1);
            if (shape != NoShape)
                DrawSquare(dc, 0 + j * SquareWidth(),
                           boardTop + i * SquareHeight(), shape);
        }
    }

    if (currentPiece.GetTetrominoesShape() != NoShape) {
        for (int i = 0; i < 4; ++i) {
            int x = curX + currentPiece.xcoords(i);
            int y = curY - currentPiece.ycoords(i);
            DrawSquare(dc, 0 + x * SquareWidth(),
                       boardTop + (BoardHeight - y - 1) * SquareHeight(),
                       currentPiece.GetTetrominoesShape());
        }
    }
}

void GameBoard::PieceDropped()
{
    for (int i = 0; i < 4; ++i) {
        int x = curX + currentPiece.xcoords(i);
        int y = curY - currentPiece.ycoords(i);
        ShapeAt(x, y) = currentPiece.GetTetrominoesShape();
    }

    RemoveFullLines();

    if (!isFallingFinished)
        NewPiece();
}

void GameBoard::RemoveFullLines()
{
     int numFullLines = 0;

     for (int i = BoardHeight - 1; i >= 0; --i) {
         bool lineIsFull = true;

         for (int j = 0; j < BoardWidth; ++j) {
             if (ShapeAt(j, i) == NoShape) {
                 lineIsFull = false;
                 break;
             }
         }

         if (lineIsFull) {
             ++numFullLines;
             for (int k = i; k < BoardHeight - 1; ++k) {
                 for (int j = 0; j < BoardWidth; ++j)
                     ShapeAt(j, k) = ShapeAt(j, k + 1);
             }
         }
     }

     if (numFullLines > 0) {
         numLinesRemoved += numFullLines;
         wxString str;
	 str.Printf(wxT("Total score: %d"), numLinesRemoved);
         GameStatusBar->SetStatusText(str);

         isFallingFinished = true;
         currentPiece.SetTetrominoesShape(NoShape);
         Refresh();
     }
 }

void GameBoard::NewPiece()
{
    currentPiece.SetRandomShape();
    curX = BoardWidth / 2 + 1;
    curY = BoardHeight - 1 + currentPiece.MinYcoord();

    if (!canRotate(currentPiece, curX, curY)) {
        currentPiece.SetTetrominoesShape(NoShape);
        timer->Stop();
        isStarted = false;
        wxString str;
        str.Printf(wxT("Game Over!! Well Played...Your Score: %d"), numLinesRemoved);
        GameStatusBar->SetStatusText(str);
    }
}

bool GameBoard::canRotate(const Shape& newPiece, int newX, int newY)
{
    for (int i = 0; i < 4; ++i) {
        int x = newX + newPiece.xcoords(i);
        int y = newY - newPiece.ycoords(i);
        if (x < 0 || x >= BoardWidth || y < 0 || y >= BoardHeight)
            return false;
        if (ShapeAt(x, y) != NoShape)
            return false;
    }

    currentPiece = newPiece;
    curX = newX;
    curY = newY;
    Refresh();
    return true;
}

void GameBoard::DrawSquare(wxPaintDC& dc, int x, int y, Tetrominoes shape)
{
    static wxColour colors[] = { wxColour(0, 0, 0), wxColour(204, 102, 102),
             wxColour(102, 204, 102), wxColour(102, 102, 204),
             wxColour(204, 204, 102), wxColour(204, 102, 204),
             wxColour(102, 204, 204), wxColour(218, 170, 0) };

    static wxColour light[] = { wxColour(0, 0, 0), wxColour(248, 159, 171),
             wxColour(121, 252, 121), wxColour(121, 121, 252),
             wxColour(252, 252, 121), wxColour(252, 121, 252),
             wxColour(121, 252, 252), wxColour(252, 198, 0) };

    static wxColour dark[] = { wxColour(0, 0, 0), wxColour(128, 59, 59),
             wxColour(59, 128, 59), wxColour(59, 59, 128),
             wxColour(128, 128, 59), wxColour(128, 59, 128),
             wxColour(59, 128, 128), wxColour(128, 98, 0) };


    wxPen pen(light[int(shape)]);
    pen.SetCap(wxCAP_PROJECTING);
    dc.SetPen(pen);

    dc.DrawLine(x, y + SquareHeight() - 1, x, y);
    dc.DrawLine(x, y, x + SquareWidth() - 1, y);

    wxPen darkpen(dark[int(shape)]);
    darkpen.SetCap(wxCAP_PROJECTING);
    dc.SetPen(darkpen);

    dc.DrawLine(x + 1, y + SquareHeight() - 1,
        x + SquareWidth() - 1, y + SquareHeight() - 1);
    dc.DrawLine(x + SquareWidth() - 1,
        y + SquareHeight() - 1, x + SquareWidth() - 1, y + 1);

    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.SetBrush(wxBrush(colors[int(shape)]));
    dc.DrawRectangle(x + 1, y + 1, SquareWidth() - 2,
        SquareHeight() - 2);
}
