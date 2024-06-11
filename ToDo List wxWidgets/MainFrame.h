#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	void CreateControls();
	wxPanel* panel;
	wxStaticText* headlinetext;
	wxTextCtrl inputField;
	wxButton addButton;
	wxCheckListBox checklistbox;
	wxButton taskClear;
};

