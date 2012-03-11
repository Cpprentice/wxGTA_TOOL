#ifndef LOADINGFRAME_HPP
#define LOADINGFRAME_HPP

#include <wx/wx.h>
#include <wx/animate.h>
#include <vector>
#include "loadingfunction.hpp"

class LoadingFrame : public wxFrame {

	public:
		LoadingFrame();
		~LoadingFrame();

		void connectLoadingFunction(LoadingFunction* func);

		void startLoading();


	private:
		void onPaint(wxPaintEvent& event);
		void onTimer(wxTimerEvent& event);

		wxTimer timer;

		unsigned int totalTokens;
		unsigned int currentTokens;
		std::vector<LoadingFunction*> functions;
		wxBitmap background;
		wxBitmap loadingBar;
		wxAnimation animation;
		bool loading;
		int aniCounter;
		int numAniBmps;
};

#endif
