#include "loadingframe.hpp"

LoadingFrame::LoadingFrame() : wxFrame(0, wxID_ANY, wxT("GTA SAMP Tool"), wxDefaultPosition, wxSize(1024, 768), wxCLOSE_BOX | wxCAPTION | wxSYSTEM_MENU ) {
	totalTokens = 0;
	currentTokens = 0;
	functions = std::vector<LoadingFunction*>();

	background = new wxBitmap(wxT("resources/wallpaper.png"), wxBITMAP_TYPE_PNG);
	bar = new wxBitmap(wxT("resources/loadingbar.png"), wxBITMAP_TYPE_PNG);

	Connect(wxEVT_PAINT, wxPaintEventHandler(LoadingFrame::onPaint), 0, this);
}

LoadingFrame::~LoadingFrame() {

	for (size_t i = 0; i < functions.size(); i++) {
		delete functions[i];
	}
	functions.clear();
	delete background;

	Disconnect(wxEVT_PAINT, wxPaintEventHandler(LoadingFrame::onPaint), 0, this);
}

void LoadingFrame::onPaint(wxPaintEvent& event) {
	wxPaintDC dc(this);

	dc.DrawBitmap(*background, 0, 0, false);
	dc.DrawBitmap(*bar, 350, 500, true);


}

void LoadingFrame::connectLoadingFunction(LoadingFunction* func) {
	totalTokens += func->getTokens();
	functions.push_back(func);
}

void LoadingFrame::startLoading() {
	for (size_t i = 0; i < functions.size(); i++) {
		functions[i]->handle();
		currentTokens += functions[i]->getTokens();
		wxPaintEvent evt;
		ProcessEvent(evt);
	}
}
