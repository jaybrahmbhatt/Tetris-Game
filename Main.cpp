#include "Main.h"
#include "Tetris.h"


IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    srand(time(NULL));
    Tetris *tetrisFrame = new Tetris(wxT("Tetris")); 	//setting the game title
    tetrisFrame->Center();			//Setting the window in the center
    tetrisFrame->Show(true);

    return true;
}
