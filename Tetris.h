#include <wx/wx.h>

class Tetris : public wxFrame
{
public:
    Tetris(const wxString& gameName);

    /**
	 * Event handler for the About menu item.
	 * @param event the item selection event.
	 */
	void on_about(wxCommandEvent& event);

	/**
	 * Event handler for the Quit menu item.
	 * @param event the item selection event.
	 */
	void on_quit(wxCommandEvent& event);

};

enum
{
	RPS_About = wxID_ABOUT,
	RPS_Quit  = wxID_EXIT
};
