#include "loadingfunction.hpp"
#include "loadingframe.hpp"
#include <wx/utils.h>
/*
LoadingTimer::LoadingTimer(LoadingFunction* func) {
	this->func = func;
}

void LoadingTimer::Notify() {
	func->onTimer();
}


*/



LoadingFunction::LoadingFunction() {//: next(this) {
	finished = false;
	ready = true;
}

LoadingFunction::~LoadingFunction() {
	//next.Stop();
}

unsigned int LoadingFunction::getTokens() {
	return tokens;
}

void LoadingFunction::returnTokens(unsigned int number) {
	if ( number <= tokens) {
		tokens -= number;
		parent->receiveTokens(number);
	}
}

void LoadingFunction::handle() {
	ready = false;
	//wxMessageBox(wxT("i am here"), wxT("info"));
	//next.Start(10, wxTIMER_ONE_SHOT);
	//next.Notify();
	onTimer();
}

bool LoadingFunction::isFinished() {
	return finished;
}

bool LoadingFunction::isReady() {
	return ready;
}





TimeWait::TimeWait(LoadingFrame* parent, unsigned int secs) {
	tokens = secs;
	this->parent = parent;
}

void TimeWait::onTimer() {
	//wxMessageBox(wxT("got here"), wxT("info"));
	wxSleep(1);
	returnTokens(1);
	if (tokens == 0)
		finished = true;
	ready = true;
	//parent->triggerNext();
}








MapCreator::MapCreator(LoadingFrame* parent, MapPanel* panel) {
	tokens = 20;
	this->panel = panel;
	this->parent = parent;
}
/*
void MapCreator::handle() {

	wxImage basicMap(wxT("resources/gtasa_aerial_map_true.jpg"), wxBITMAP_TYPE_JPEG);

	returnTokens(2);



}*/

void MapCreator::onTimer() {

	static bool first = true;
	wxImage basicMap;

	if (first) {
		parent->openZipEntry(wxT("gtasa_aerial_map_true.jpg"));
		basicMap.LoadFile(*parent->getZip(), wxBITMAP_TYPE_JPEG);
		first = false;
		wxBitmap temp = basicMap;
		panel->InitMapLevels(4, temp);
		returnTokens(4);
	}
	else {
		basicMap = panel->getBasicMap();

		if( tokens == 16) {
			wxBitmap temp = basicMap.Scale(600, 600, wxIMAGE_QUALITY_HIGH);
			panel->InitMapLevels(0, temp);
			returnTokens(8);
		}
		else if( tokens == 8) {
			wxBitmap temp = basicMap.Scale(1060, 1060, wxIMAGE_QUALITY_HIGH);
			panel->InitMapLevels(1, temp);
			returnTokens(4);
		}
		else if (tokens == 4) {
			wxBitmap temp = basicMap.Scale(1900, 1900, wxIMAGE_QUALITY_HIGH);
			panel->InitMapLevels(2, temp);
			returnTokens(2);
		}
		else if (tokens == 2) {
			wxBitmap temp = basicMap.Scale(3370, 3370, wxIMAGE_QUALITY_HIGH);
			panel->InitMapLevels(3, temp);
			returnTokens(2);
		}
		else if (tokens == 0) {
			finished = true;
		}
	}
	ready = true;
	//parent->triggerNext();
}
