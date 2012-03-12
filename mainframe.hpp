#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include <wx/wx.h>
#include "mappanel.hpp"

class MainFrame : public wxFrame {

	public:
		MainFrame();
		~MainFrame();

		MapPanel* getMapPanel();

	private:
		MapPanel* mapPanel;
};

#endif
