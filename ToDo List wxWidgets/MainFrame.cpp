#include "MainFrame.h"
#include <wx/wx.h>
#include <vector>
#include <string>
#include "Task.h"

//main
MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, 
	wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	CreateControls();
	bindEventHandlers();
	AddSavedTasks();
}

//buttons and inputs
void MainFrame::CreateControls()
{
	wxFont headlineFont(wxFontInfo(wxSize(0, 36)).Bold());
	wxFont mainFont(wxFontInfo(wxSize(0, 24)).Bold());

	panel = new wxPanel(this);
	panel->SetFont(mainFont);

	headlinetext = new wxStaticText(panel, wxID_ANY, "TO-DO List", wxPoint(0, 22), wxSize(800, -1),
		wxALIGN_CENTER_HORIZONTAL);
	headlinetext->SetFont(headlineFont);


	inputField = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(100, 80), wxSize(495, 35), wxTE_PROCESS_ENTER);
	addButton = new wxButton(panel, wxID_ANY, "ADD", wxPoint(600, 80), wxSize(100, 35));
	checklistbox = new wxCheckListBox(panel, wxID_ANY, wxPoint(100, 120), wxSize(600, 400));
	taskClear = new wxButton(panel, wxID_ANY, "Clear", wxPoint(100, 525), wxSize(100, 35));

}


//event central
void MainFrame::bindEventHandlers()
{
	addButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddButtonClicked, this);
	inputField->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnInputEnter, this);
	checklistbox->Bind(wxEVT_KEY_DOWN, &MainFrame::OnListKeyDown, this);
	taskClear->Bind(wxEVT_BUTTON, &MainFrame::OnClearButtonClicked, this);
	this->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnWindowClosed, this);
}



void MainFrame::OnAddButtonClicked(wxCommandEvent& evt)
{
	AddTaskFromInput();
}
//taking inputs with "ENTER"
void MainFrame::OnInputEnter(wxCommandEvent& evt)
{
	AddTaskFromInput();
}

//clears all tasks
void MainFrame::OnClearButtonClicked(wxCommandEvent& evt)
{
	if (checklistbox->IsEmpty())
	{
		return;
	}

	wxMessageDialog dialog(this, "Are you sure you want to Clear all tasks?",
		" Clear ", wxYES_NO);
	int result = dialog.ShowModal();

	if (result == wxID_YES)
	{
		checklistbox->Clear();
	}
}


//after task addition clear input field and refocus it
void MainFrame::AddTaskFromInput()
{
	wxString description = inputField->GetValue();
	
	if (!description.IsEmpty())
	{
		checklistbox->Insert(description, checklistbox->GetCount());
		inputField->Clear();
	}
	inputField->SetFocus();
}




//selecting what to do when selecting task
void MainFrame::OnListKeyDown(wxKeyEvent& evt)
{
	switch (evt.GetKeyCode())
	{
	case WXK_DELETE:
		DeleteSelectedTask();
		break;
	case WXK_UP:
		MoveSelectedTask(-1);
		break;
	case WXK_DOWN:
		MoveSelectedTask(1);
		break;
	}
	
	
		
}


//deletion of selection
void MainFrame::DeleteSelectedTask()
{
	int selectedIndex = checklistbox->GetSelection();

	if (selectedIndex == wxNOT_FOUND)
	{
		return;
	}

	checklistbox->Delete(selectedIndex);
}


//moving tasks
void MainFrame::MoveSelectedTask(int offset)
{
	int selectedIndex = checklistbox->GetSelection();

	if (selectedIndex == wxNOT_FOUND)
	{
		return;
	}
	int newIndex = selectedIndex + offset;
	if (newIndex >= 0 && newIndex < checklistbox->GetCount())
	{
		SwapTasks(selectedIndex, newIndex);
		checklistbox->SetSelection(newIndex, true);
	}
}

//swaping tasks
void MainFrame::SwapTasks(int i, int j)
{
	Task taskI{ checklistbox->GetString(i).ToStdString(), checklistbox->IsChecked(i) };
	Task taskJ{ checklistbox->GetString(j).ToStdString(), checklistbox->IsChecked(j) };

	checklistbox->SetString(i, taskJ.description);
	checklistbox->Check(i, taskJ.done);

	checklistbox->SetString(j, taskI.description);
	checklistbox->Check(j, taskI.done);
}

//writing tasks to a .txt for saving
void MainFrame::OnWindowClosed(wxCloseEvent& evt)
{
	std::vector<Task> tasks;
	for (int i = 0; i < checklistbox->GetCount(); i++)
	{
		Task task;
		task.description = checklistbox->GetString(i);
		task.done = checklistbox->IsChecked(i);
		tasks.push_back(task);
	}
	SaveTasksToFile(tasks, "tasks.txt");
	evt.Skip();
}

//loading tasks on start
void MainFrame::AddSavedTasks()
{
	std::vector<Task> tasks = LoadTasksFromFile("tasks.txt");

	for (const Task& task : tasks)
	{
		int index = checklistbox->GetCount();
		checklistbox->Insert(task.description, index);
		checklistbox->Check(index, task.done);
	}
}
