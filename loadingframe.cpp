#include "loadingframe.hpp"
#include <wx/dcbuffer.h>


///LoadingFrame


LoadingFrame::LoadingFrame() : wxFrame(0, wxID_ANY, wxT("GTA SAMP Tool"), wxDefaultPosition, wxSize(800, 600), wxCLOSE_BOX | wxCAPTION | wxSYSTEM_MENU ) {

	SetClientSize(800, 600);
	animation.LoadFile(wxT("resources/loading_ani_single.gif"), wxANIMATION_TYPE_GIF);
	totalTokens = 0;
	currentTokens = 0;
	aniCounter = 0;
	numAniBmps = animation.GetFrameCount();
	loading = false;
	functions = std::vector<LoadingFunction*>();

	background.LoadFile(wxT("resources/background2.png"), wxBITMAP_TYPE_PNG);
	//bar.LoadFile(wxT("resources/loading_ani.png"), wxBITMAP_TYPE_PNG);
	loadingBar = wxBitmap(animation.GetFrame(0));

	Connect(wxEVT_PAINT, wxPaintEventHandler(LoadingFrame::onPaint), 0, this);
	Connect(wxEVT_TIMER, wxTimerEventHandler(LoadingFrame::onTimer), 0, this);

	timer.SetOwner(this);

	//wxAnimationCtrl* aniCtrl = new wxAnimationCtrl(this, wxID_ANY, animation);
	//aniCtrl->Play();

	timer.Start(animation.GetDelay(0), wxTIMER_ONE_SHOT);
}

LoadingFrame::~LoadingFrame() {

	for (size_t i = 0; i < functions.size(); i++) {
		delete functions[i];
	}
	functions.clear();

	Disconnect(wxEVT_PAINT, wxPaintEventHandler(LoadingFrame::onPaint), 0, this);
	Disconnect(wxEVT_TIMER, wxTimerEventHandler(LoadingFrame::onTimer), 0, this);
}

void LoadingFrame::onPaint(wxPaintEvent& event) {
	wxBufferedPaintDC dc(this);
	dc.DrawBitmap(background, 0, 0, false);
	dc.DrawBitmap(loadingBar, 0, 460, true);
}

void LoadingFrame::onTimer(wxTimerEvent& event) {

	aniCounter++;
	if (aniCounter < numAniBmps) {
		loadingBar = wxBitmap(animation.GetFrame(aniCounter));
		timer.Start(animation.GetDelay(aniCounter), wxTIMER_ONE_SHOT);
		//wxPaintEvent evt;
		//ProcessEvent(evt);
		//GetEventHandler()->AddPendingEvent(evt);
		Refresh(false);
	}
	else {
		loadingBar = wxBitmap(wxT("resources/loading_ani2.png"), wxBITMAP_TYPE_PNG);
		//wxPaintEvent evt;
		//ProcessEvent(evt);
		Refresh(false);
		startLoading();
	}

}

void LoadingFrame::connectLoadingFunction(LoadingFunction* func) {
	totalTokens += func->getTokens();
	functions.push_back(func);
}

void LoadingFrame::startLoading() {

	loading = true;
	for (size_t i = 0; i < functions.size(); i++) {
		functions[i]->handle();
		currentTokens += functions[i]->getTokens();
		//wxPaintEvent evt;
		//ProcessEvent(evt);
		Refresh(false);
	}
}
