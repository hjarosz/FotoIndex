/***************************************************************
 * Name:      FotoIndexMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2019-05-19
 * Copyright:  ()
 * License:
 **************************************************************/

#include "FotoIndexMain.h"
#include <wx/msgdlg.h>
#include <sstream>
#include <string>
#include <wx/dcmemory.h>


//(*InternalHeaders(FotoIndexFrame)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(FotoIndexFrame)
const long FotoIndexFrame::ID_BUTTON1 = wxNewId();
const long FotoIndexFrame::ID_STATICTEXT1 = wxNewId();
const long FotoIndexFrame::ID_STATICTEXT2 = wxNewId();
const long FotoIndexFrame::ID_DIRPICKERCTRL1 = wxNewId();
const long FotoIndexFrame::ID_DIRPICKERCTRL2 = wxNewId();
const long FotoIndexFrame::ID_PANEL1 = wxNewId();
const long FotoIndexFrame::idMenuQuit = wxNewId();
const long FotoIndexFrame::idMenuAbout = wxNewId();
const long FotoIndexFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(FotoIndexFrame,wxFrame)
    //(*EventTable(FotoIndexFrame)
    //*)
END_EVENT_TABLE()

FotoIndexFrame::FotoIndexFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(FotoIndexFrame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(267,191));
    SetMinSize(wxSize(344,240));
    SetMaxSize(wxSize(344,240));
    Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(160,88), wxSize(344,240), wxSTATIC_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    Panel1->SetMinSize(wxSize(344,240));
    Panel1->SetMaxSize(wxSize(344,240));
    submit = new wxButton(Panel1, ID_BUTTON1, _("Submit"), wxPoint(104,112), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    sourceText = new wxStaticText(Panel1, ID_STATICTEXT1, _("Source"), wxPoint(24,24), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    wxFont sourceTextFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    sourceText->SetFont(sourceTextFont);
    targetText = new wxStaticText(Panel1, ID_STATICTEXT2, _("Target"), wxPoint(24,72), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    wxFont targetTextFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    targetText->SetFont(targetTextFont);
    sourcePicker = new wxDirPickerCtrl(Panel1, ID_DIRPICKERCTRL1, wxEmptyString, _("Choose source folder"), wxPoint(104,24), wxDefaultSize, wxDIRP_DIR_MUST_EXIST|wxDIRP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_DIRPICKERCTRL1"));
    targetPicker = new wxDirPickerCtrl(Panel1, ID_DIRPICKERCTRL2, wxEmptyString, _("Choose destination folder"), wxPoint(104,72), wxDefaultSize, wxDIRP_DIR_MUST_EXIST|wxDIRP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_DIRPICKERCTRL2"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FotoIndexFrame::OnsubmitClick);
    Connect(ID_DIRPICKERCTRL1,wxEVT_COMMAND_DIRPICKER_CHANGED,(wxObjectEventFunction)&FotoIndexFrame::OnsourcePickerDirChanged);
    Connect(ID_DIRPICKERCTRL2,wxEVT_COMMAND_DIRPICKER_CHANGED,(wxObjectEventFunction)&FotoIndexFrame::OntargetPickerDirChanged);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FotoIndexFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FotoIndexFrame::OnAbout);
    //*)
}
//returning pointer to array with all images paths
wxArrayString* fetchFileNames(const wxString sourcePath){
    wxArrayString* filesArray = new wxArrayString(); //keeps all files paths
    size_t count = wxDir::GetAllFiles(sourcePath, filesArray);
    std::stringstream stream;
    stream << "Found " <<count << " files!";
    const wxString message = wxString(stream.str());
    wxMessageBox(message);
    return filesArray;
}

wxString createNewFilePath(const wxString targetPath, size_t counter){
    std::stringstream sstm;
    sstm << targetPath << "\\miniaturka_" << counter << ".bmp" ;
    return wxString(sstm.str());
}

//////////////////////////////////////////////////////////
//W SUMIE TO G£ÓWNA FUNKCJA, TU WARTO SPOJRZEC
//////////////////////////////////////////////////////////
void processPathArray(wxArrayString* pathArray, const wxString& targetPath){
    wxCoord posX = 0;
    wxCoord posY = 0;
    int totalFiles = (int) ceil(pathArray->GetCount() / 20.0);
    wxImage resultPic = wxImage(800, 600);

    wxBitmap txtBitmap = wxBitmap(100, 30);
    wxMemoryDC memdc;
    memdc.SelectObject(txtBitmap);
    memdc.SetBackgroundMode( wxPENSTYLE_SOLID );
    memdc.SetTextForeground( *wxWHITE );
    memdc.SetTextBackground( *wxBLACK );

    wxString txt = wxString("chuj");

    memdc.DrawText(txt, 0, 0);

    wxBitmap outBmp = memdc.GetAsBitmap();
    memdc.SelectObject(wxNullBitmap);

    for(size_t i=0; i<pathArray->GetCount(); ++i){
        const wxString filePath = pathArray->Item(i);

        wxImage orginalPic =  wxImage();
        orginalPic.LoadFile(filePath);
        wxImage scaledPic = orginalPic.Scale(150,120);
        resultPic.Paste(scaledPic, posX, posY);
        resultPic.Paste(outBmp.ConvertToImage(),posX+75, posY+120);
        posX += 160;
        if(posX == 800){
            posX = 0;
            posY += 150;
        }

        //GWIAZDKA KURWA - zrobione po to aby w ka¿dym pliku by³o max 20 miniaturek
        if((i % 19) == 0 && i != 0){
            resultPic.SaveFile(createNewFilePath(targetPath,((i+1)/20)),wxBITMAP_TYPE_BMP);
            resultPic.Destroy();
            resultPic = wxImage(800, 600);
            posX = 0;
            posY = 0;
            wxMessageBox("chuj");
        }
    }
    //GWIAZDKA KURWA - ¿eby zapisa³o ostatni plik z miniaturkami (jezeli jest podzielne przez 20 to zrobi sie to w if'ie wyzej)
    if((totalFiles % 20) != 0){
        resultPic.SaveFile(createNewFilePath(targetPath,(int) ceil(totalFiles/20.0)+1),wxBITMAP_TYPE_JPEG);
    }
}
//GWIAZDKA KURWA -- jak macie checi to mo¿na to ubraæ w jakieœ pêtle zamiast takich if'ów

FotoIndexFrame::~FotoIndexFrame()
{
    //(*Destroy(FotoIndexFrame)
    //*)
}

void FotoIndexFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void FotoIndexFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}
//////////////////////////////////////////////////////////
//TO SIE WYKONUJE PO KLIKNIÊCIU SUBMIT
//////////////////////////////////////////////////////////
void FotoIndexFrame::OnsubmitClick(wxCommandEvent& event)
{
    const wxString sourcePath = sourcePicker->GetPath();
    const wxString targetPath = targetPicker->GetPath();
    const wxString emptyPath = wxString("");

    if(sourcePath == emptyPath || targetPath == emptyPath){
        wxMessageBox("Select BOTH ditectories!");
    }
    else {
        wxArrayString* pathArray = fetchFileNames(sourcePath); //keeps all files paths (ALL FILES NOT ONLY IMAGES!!!!!!!!!!!)
        if(pathArray->GetCount() > 0){
            processPathArray(pathArray, targetPath);
        }
        else{
            wxMessageBox("Found 0 files!");
        }
    }
}

void FotoIndexFrame::OnsourcePickerDirChanged(wxFileDirPickerEvent& event)
{
}

void FotoIndexFrame::OntargetPickerDirChanged(wxFileDirPickerEvent& event)
{
}
