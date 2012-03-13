#ifndef MAPPANEL_HPP
#define MAPPANEL_HPP

#include <wx/wx.h>

class MapPanel : public wxPanel {

	public:
		MapPanel(wxWindow* parent);
		~MapPanel();

		void InitMapLevels(size_t level, wxBitmap& map);
		wxImage getBasicMap();
	private:
		void onPaint(wxPaintEvent& event);
		void onScroll(wxMouseEvent& event);
		void onRightDown(wxMouseEvent& event);
		void onRightUp(wxMouseEvent& event);
		void onDrag(wxMouseEvent& event);
		void onLostCapture(wxMouseCaptureLostEvent& event);
		void onLeavePanel(wxMouseEvent& event);
		void onEnterPanel(wxMouseEvent& event);

		wxBitmap mapLevels[5];//The real bitmaps
		wxSize mapSizes[4];//The sizes for the virtual bitmaps
		size_t levelIndex;

		wxPoint mousePos;
		wxPoint mapPos;
};

#endif
