#include "mainframe.hpp"

MainFrame::MainFrame() : wxFrame(0, wxID_ANY, wxT("SAMP PLACEMENT TOOL")) {
	SetClientSize(800,600);
	mapPanel = new MapPanel(this);
};

MainFrame::~MainFrame() {

}

MapPanel* MainFrame::getMapPanel() {
	return mapPanel;
}
