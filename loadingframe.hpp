#ifndef LOADINGFRAME_HPP
#define LOADINGFRAME_HPP

#include <wx/wx.h>

class LoadingFrame : public wxFrame {

	public:
		LoadingFrame();
		~LoadingFrame();
	private:
		void OnPaint(wxPaintEvent& event);
};

#endif
