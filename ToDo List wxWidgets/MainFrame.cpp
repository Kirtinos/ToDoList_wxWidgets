#include "MainFrame.h"
#include <wx/wx.h>
#include <vector>
#include <string>
#include "Task.h"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	CreateControls();
}

void MainFrame::CreateControls()
{
	wxFont headlineFont(wxFontInfo(wxSize(0, 36)).Bold());
	wxFont mainFont(wxFontInfo(wxSize(0, 24)).Bold());

	panel = new wxPanel(this);
	panel->SetFont(mainFont);

	headlinetext = new wxStaticText(panel, wxID_ANY, "To-DO List", wxPoint(0, 22), wxSize(800, -1),
		wxALIGN_CENTER_HORIZONTAL);
	headlinetext->SetFont(headlineFont);


	inputField = new wxTextCtrl(panel, wxID_ANY, " ", wxPoint(100, 80), wxSize(495, 35));

}
