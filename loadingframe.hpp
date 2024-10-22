#ifndef LOADINGFRAME_HPP
#define LOADINGFRAME_HPP

#include <wx/wx.h>
#include <wx/animate.h>
#include <vector>
#include "loadingfunction.hpp"
#include "mainframe.hpp"
#include <wx/zipstrm.h>
#include <wx/wfstream.h>

class LoadingFrame : public wxFrame {

	public:
		LoadingFrame(MainFrame* mainframe);
		~LoadingFrame();

		void receiveTokens(unsigned int number);
		//void triggerNext();
		wxZipInputStream* getZip();
		bool openZipEntry(wxString name);

	private:
		void onPaint(wxPaintEvent& event);
		void onTimer(wxTimerEvent& event);
		void onClose(wxCloseEvent& event);

		void startLoading();

		///Call this in Constructor
		void connectLoadingFunction(LoadingFunction* func);

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

		MainFrame* mainframe;
		wxFileInputStream* input;
		wxZipInputStream* zip;
		std::vector<wxZipEntry*> zipEntries;
};

#endif
