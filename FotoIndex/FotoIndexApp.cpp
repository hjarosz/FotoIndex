/***************************************************************
 * Name:      FotoIndexApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2019-05-19
 * Copyright:  ()
 * License:
 **************************************************************/

#include "FotoIndexApp.h"

//(*AppHeaders
#include "FotoIndexMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(FotoIndexApp);

bool FotoIndexApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	FotoIndexFrame* Frame = new FotoIndexFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
