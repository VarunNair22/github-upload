#pragma once

#include "wx/wx.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();
	int fieldWidth = 10;
	int fieldHeight = 10;
	int mineCount = 30;
	wxButton** btn;

	int* field = nullptr;
	bool firstClick = true;


	void OnButtonClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

