#include "loadingframe.hpp"
#include <wx/dcbuffer.h>
#include <wx/utils.h>

///LoadingFrame


LoadingFrame::LoadingFrame(MainFrame* mainframe) : wxFrame(0, wxID_ANY, wxT("GTA SAMP Tool"), wxDefaultPosition, wxDefaultSize, wxCLOSE_BOX | wxCAPTION | wxSYSTEM_MENU ) {

	this->mainframe = mainframe;

	SetClientSize(800, 600);
	animation.LoadFile(wxT("resources/loading_ani_single.gif"), wxANIMATION_TYPE_GIF);
	totalTokens = 0;
	currentTokens = 0;
	aniCounter = 0;
	numAniBmps = animation.GetFrameCount();
	loading = false;
	functions = std::vector<LoadingFunction*>();

	background.LoadFile(wxT("resources/background2.png"), wxBITMAP_TYPE_PNG);
	loadingBar = wxBitmap(animation.GetFrame(0));


	Connect(wxEVT_PAINT, wxPaintEventHandler(LoadingFrame::onPaint), 0, this);
	Connect(wxEVT_TIMER, wxTimerEventHandler(LoadingFrame::onTimer), 0, this);
	Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(LoadingFrame::onClose), 0, this);
/*
	TimeWait* t0 = new TimeWait(this, 1);
	TimeWait* t1 = new TimeWait(this, 4);
	TimeWait* t2 = new TimeWait(this, 2);
	TimeWait* t3 = new TimeWait(this, 3);
	TimeWait* t4 = new TimeWait(this, 1);


	connectLoadingFunction(t0);
	connectLoadingFunction(t1);
	connectLoadingFunction(t2);
	connectLoadingFunction(t3);
	connectLoadingFunction(t4);

*/
	MapCreator* mc = new MapCreator(this, mainframe->getMapPanel());
	connectLoadingFunction(mc);

	timer.SetOwner(this);
	timer.Start(animation.GetDelay(0), wxTIMER_ONE_SHOT);
}

LoadingFrame::~LoadingFrame() {

	timer.Stop();

	Disconnect(wxEVT_PAINT, wxPaintEventHandler(LoadingFrame::onPaint), 0, this);
	Disconnect(wxEVT_TIMER, wxTimerEventHandler(LoadingFrame::onTimer), 0, this);
}

void LoadingFrame::onPaint(wxPaintEvent& event) {
	wxBufferedPaintDC dc(this);

	dc.DrawBitmap(background, 0, 0, false);
	dc.DrawBitmap(loadingBar, 0, 460, true);
	if (loading) {

		unsigned int width = 680 * currentTokens;
		if (totalTokens != 0)
			width /= totalTokens;
		else
			width = 680;
		wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
		if (width != 0) {
			gc->SetBrush(gc->CreateLinearGradientBrush(0.0, 0.0, 1000.0, 80.0, wxColour(255,0,0,170), wxColour(0,255,0,170)));
			gc->DrawRectangle(60.0, 490.0, width, 80.0);
		}
		delete gc;
	}
}

void LoadingFrame::onClose(wxCloseEvent& event) {
	if (currentTokens != totalTokens && totalTokens != 0)
		mainframe->Close();
	event.Skip();
}

void LoadingFrame::onTimer(wxTimerEvent& event) {

	if (loading) {
		if (functions.size() > 0) {
			if (functions[0]->isReady()) {
				if (functions[0]->isFinished()) {
					currentTokens += functions[0]->getTokens();
					Refresh(false);
					delete functions[0];
					functions.erase(functions.begin());
				}
				if (functions.size() > 0)
					functions[0]->handle();
				timer.Start(10, wxTIMER_ONE_SHOT);
			}
		}
		else {
			//timer.Stop();
			wxSleep(2);
			mainframe->Show();

			Close();
		}
	}
	else {

		aniCounter++;
		if (aniCounter < numAniBmps) {
			loadingBar = wxBitmap(animation.GetFrame(aniCounter));
			timer.Start(animation.GetDelay(aniCounter), wxTIMER_ONE_SHOT);
			Refresh(false);
		}
		else {
			loadingBar = wxBitmap(wxT("resources/loading_ani2.png"), wxBITMAP_TYPE_PNG);
			Refresh(false);
			startLoading();
		}
	}
}

void LoadingFrame::receiveTokens(unsigned int number) {

	currentTokens += number;
	Refresh(false);
}

void LoadingFrame::triggerNext() {
	//timer.Start(10, wxTIMER_ONE_SHOT);
	wxTimerEvent evt;
	AddPendingEvent(evt);
}

void LoadingFrame::connectLoadingFunction(LoadingFunction* func) {
	totalTokens += func->getTokens();
	functions.push_back(func);
}

void LoadingFrame::startLoading() {

	loading = true;
	timer.Start(50, wxTIMER_ONE_SHOT);
}
