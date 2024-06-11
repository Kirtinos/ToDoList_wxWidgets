#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	void CreateControls();
	void bindEventHandlers();
	void OnAddButtonClicked(wxCommandEvent& evt);
	void OnInputEnter(wxCommandEvent& evt);
	void OnClearButtonClicked(wxCommandEvent& evt);
	void AddTaskFromInput();
	void OnListKeyDown(wxKeyEvent& evt);
	void DeleteSelectedTask();
	void MoveSelectedTask(int offset);
	void SwapTasks(int i, int j);
	void OnWindowClosed(wxCloseEvent& evt);
	void AddSavedTasks();

	wxPanel* panel;
	wxStaticText* headlinetext;
	wxTextCtrl* inputField;
	wxButton* addButton;
	wxCheckListBox* checklistbox;
	wxButton* taskClear;
};

