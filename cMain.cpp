#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(10001, OnButtonClicked)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "This is a test", wxPoint(30, 30), wxSize(800,600)) {
	btn = new wxButton * [fieldWidth * fieldHeight];
	wxGridSizer* grid = new wxGridSizer(fieldWidth, fieldHeight, 0, 0);
	field = new int[fieldWidth * fieldHeight];
	for (int i = 0; i < fieldWidth; i++){
		for (int j = 0; j < fieldHeight; j++)
		{
			btn[j * fieldWidth + i] = new wxButton(this, 10000 + j * fieldWidth + i);
			grid->Add(btn[j * fieldWidth + i], 1, wxEXPAND | wxALL);
			btn[j * fieldWidth + i]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
			field[j * fieldWidth + i] = 0;
		}
	}
	this->SetSizer(grid);
	grid->Layout();
}

cMain::~cMain() {
	delete[]btn;
}

void cMain::OnButtonClicked(wxCommandEvent& evt) {
	/*
		On button press function. Currently:
		- Generates minefield after first click st mine can't have same value as first click
		- generates field after first click
		- On loss, display textbox
	*/

	/*
		int x: subtract 10000 from ID to get exact value in array of element. modding by width gives
		what the x value is.
		int y: subtract 10000 from ID to get exact value in array of element. divide by width will
		give how many rows down the y value went, hence giving the y value.
	*/
	int x = (evt.GetId() - 10000) % fieldWidth;
	int y = (evt.GetId() - 10000) / fieldWidth;

	//If it's the first click in the game, set the board
	if (firstClick) {
		int mines = mineCount;

		while (mines) {
			/*
				get appropriate x and y values by modding a random value by field 
				width and height, respectively.
			*/
			int rx = rand() % fieldWidth;
			int ry = rand() % fieldHeight;

			//if the space is empty and it is not equal to the first click it is valid.
			if (field[ry * fieldWidth + rx] == 0 && rx != x && ry!=y) {
				//-1 represents a mine in the space.
				field[ry * fieldWidth + rx] = -1;
				//decrement mine counter untill it is 0, in which no more mines needed.
				mines--;
			}

		}
		//Don't generate board on future clicks.
		firstClick = false;
	}

	//Disable button after clicking it once.
	btn[y * fieldWidth + x]->Enable();

	if (field[y * fieldWidth + x] == -1) {
		//user hit mine, instant lose
		wxMessageBox("You Lose!");

		//reset game
		firstClick = true;
		for (int i = 0; i < fieldWidth; i++){
			for (int j = 0; j < fieldHeight; j++){
				field[j * fieldWidth + i] = 0;
				btn[j*fieldWidth + i]->SetLabel("");
				btn[j*fieldWidth + i]->Enable(true);
			}
		}
	}
	else {
		int mineCount = 0;
		for (int i = -1; i <= 1; i++){
			for (int j = -1; j <= 1; j++){
				if (0 <= x + i && x + i < fieldWidth && 0 <= y + j && y + j < fieldHeight) {
					if (field[(y + j) * fieldWidth + (x + i)] == -1) {
						mineCount++;
					}
				}
			}
		}
		if (mineCount){
			btn[y * fieldWidth + x]->SetLabel(std::to_string(mineCount));
		}
	}

	evt.Skip();
}
