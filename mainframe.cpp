#include "mainframe.hpp"

MainFrame::MainFrame() : wxFrame(0, wxID_ANY, wxT("SAMP PLACEMENT TOOL"), wxDefaultPosition, wxDefaultSize, wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX) {
	SetClientSize(800,600);
	mapPanel = new MapPanel(this);

	toolsPanel = new ToolsPanel(this);

	toolsPanel->SetFocus();
};

MainFrame::~MainFrame() {

}

MapPanel* MainFrame::getMapPanel() {
	return mapPanel;
}
