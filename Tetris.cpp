#include "Tetris.h"

#include "GameBoard.h"


void Tetris::on_about(wxCommandEvent& WXUNUSED(event))
{
	wxMessageBox(wxString::Format(
			"This is a Tetris Game\n"
			"built with %s\n"
			"and running under %s.",
			wxVERSION_STRING,
			wxGetOsDescription()
			),
			"About the Tetris Game",
			wxOK | wxICON_INFORMATION,
			this);
}

void Tetris::on_quit (wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}

Tetris::Tetris(const wxString& gameName)
       : wxFrame(NULL, wxID_ANY, gameName, wxDefaultPosition, wxSize(380, 470))
{
  wxStatusBar *statusbar = CreateStatusBar();
  statusbar->SetStatusText(wxT("Total Score: 0"));
  GameBoard *board = new GameBoard(this);
  board->SetFocus();
  board->Start();
}
