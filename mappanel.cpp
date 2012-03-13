#include "mappanel.hpp"
#include <wx/dcbuffer.h>

MapPanel::MapPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY) {
	SetClientSize(600,600);
	levelIndex = 0;

	mapSizes[0] = wxSize(8500, 8500);
	mapSizes[1] = wxSize(12000, 12000);
	mapSizes[2] = wxSize(17000, 17000);
	mapSizes[3] = wxSize(24000, 24000);

	Connect(wxEVT_PAINT, wxPaintEventHandler(MapPanel::onPaint), 0, this);
	Connect(wxEVT_MOUSEWHEEL, wxMouseEventHandler(MapPanel::onScroll), 0, this);

	Connect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(MapPanel::onRightDown), 0, this);
	Connect(wxEVT_RIGHT_UP, wxMouseEventHandler(MapPanel::onRightUp), 0, this);
	Connect(wxEVT_MOTION, wxMouseEventHandler(MapPanel::onDrag), 0, this);
	Connect(wxEVT_MOUSE_CAPTURE_LOST, wxMouseCaptureLostEventHandler(MapPanel::onLostCapture), 0, this);

	Connect(wxEVT_ENTER_WINDOW, wxMouseEventHandler(MapPanel::onEnterPanel), 0, this);
	Connect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(MapPanel::onLeavePanel), 0, this);
}

MapPanel::~MapPanel() {
	Disconnect(wxEVT_PAINT, wxPaintEventHandler(MapPanel::onPaint), 0, this);
	Disconnect(wxEVT_MOUSEWHEEL, wxMouseEventHandler(MapPanel::onScroll), 0, this);

	Disconnect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(MapPanel::onRightDown), 0, this);
	Disconnect(wxEVT_RIGHT_UP, wxMouseEventHandler(MapPanel::onRightUp), 0, this);
	Disconnect(wxEVT_MOTION, wxMouseEventHandler(MapPanel::onDrag), 0, this);
	Disconnect(wxEVT_MOUSE_CAPTURE_LOST, wxMouseCaptureLostEventHandler(MapPanel::onLostCapture), 0, this);

	Disconnect(wxEVT_ENTER_WINDOW, wxMouseEventHandler(MapPanel::onEnterPanel), 0, this);
	Disconnect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(MapPanel::onLeavePanel), 0, this);
}

void MapPanel::InitMapLevels(size_t level, wxBitmap& map) {
	mapLevels[level] = map;
}

void MapPanel::onPaint(wxPaintEvent& event) {
	wxBufferedPaintDC dc(this);

	if (levelIndex < 5)
		dc.DrawBitmap(mapLevels[levelIndex].GetSubBitmap(wxRect(mapPos,wxSize(600,600))), 0, 0, false);
	else {
		//wxSize diff = wxSize(6000,6000) - mapSizes[levelIndex];

		double factor = 6000.0 / double(mapSizes[levelIndex - 5].x);
		wxPoint diff = mapPos;

		//wxMessageBox(wxString::Format(wxT("%i %i %f"), diff.x, diff.y, factor), wxT("info"));

		diff.x *= factor;
		diff.y *= factor;

		wxSize virtSize = wxSize(600,600);
		virtSize.x = virtSize.x * factor;
		virtSize.y = virtSize.y * factor;

		//wxMessageBox(wxString::Format(wxT("%i %i   %i %i"), diff.x, diff.y, virtSize.x, virtSize.y), wxT("info"));

		wxImage temp = mapLevels[4].GetSubBitmap(wxRect(diff, virtSize)).ConvertToImage();
		temp.Rescale(600,600);
		dc.DrawBitmap(wxBitmap(temp), 0, 0, false);
	}
}

void MapPanel::onScroll(wxMouseEvent& event) {
	int dir = event.GetWheelRotation();
	if (!event.LeftIsDown() && !event.RightIsDown()) {


		wxSize alt;

		if (levelIndex < 5)
			alt = wxSize(mapLevels[levelIndex].GetWidth(), mapLevels[levelIndex].GetHeight());
		else
			alt = mapSizes[levelIndex-5];

		if (dir < 0) {
			if (levelIndex > 0) {
				levelIndex--;
			}
		}
		else if (dir > 0) {
			if (levelIndex < 8) {
				levelIndex++;
			}
		}

		wxSize neu;
		if (levelIndex < 5)
			neu = wxSize(mapLevels[levelIndex].GetWidth(), mapLevels[levelIndex].GetHeight());
		else
			neu = mapSizes[levelIndex-5];
		wxSize diff = alt - neu;

		//wxMessageBox(wxString::Format(wxT("%i %i"), diff.x, diff.y), wxT("info"));
		//diff /= 2;
		//wxMessageBox(wxString::Format(wxT("%i %i"), diff.x, diff.y), wxT("info"));
		mapPos.x -= diff.x * (event.GetPosition().x / 600.0);
		mapPos.y -= diff.y * (event.GetPosition().y / 600.0);


		if (levelIndex < 5) {
			if (mapPos.x > mapLevels[levelIndex].GetWidth() - 601)mapPos.x = mapLevels[levelIndex].GetWidth() - 601;
			if (mapPos.y > mapLevels[levelIndex].GetHeight() - 601)mapPos.y = mapLevels[levelIndex].GetHeight() - 601;
		}
		else {
			if (mapPos.x > mapSizes[levelIndex-5].x - 601)mapPos.x = mapSizes[levelIndex-5].x - 601;
			if (mapPos.y > mapSizes[levelIndex-5].y - 601)mapPos.y = mapSizes[levelIndex-5].y - 601;
		}

		if (mapPos.x < 0)mapPos.x = 0;
		if (mapPos.y < 0)mapPos.y = 0;
		Refresh(false);
	}
}

void MapPanel::onRightDown(wxMouseEvent& event) {
	CaptureMouse();
	mousePos = event.GetPosition();
}

void MapPanel::onRightUp(wxMouseEvent& event) {
	ReleaseMouse();
}
void MapPanel::onDrag(wxMouseEvent& event) {
	if (event.Dragging()) {
		if (event.LeftIsDown()) {

		}
		else if (event.RightIsDown()) {
			wxPoint movement = mousePos - event.GetPosition();
			mousePos = event.GetPosition();

			mapPos += movement;

			if (levelIndex < 5) {
				if (mapPos.x > mapLevels[levelIndex].GetWidth() - 601)mapPos.x = mapLevels[levelIndex].GetWidth() - 601;
				if (mapPos.y > mapLevels[levelIndex].GetHeight() - 601)mapPos.y = mapLevels[levelIndex].GetHeight() - 601;
			}
			else {
				if (mapPos.x > mapSizes[levelIndex-5].x - 601)mapPos.x = mapSizes[levelIndex-5].x - 601;
				if (mapPos.y > mapSizes[levelIndex-5].y - 601)mapPos.y = mapSizes[levelIndex-5].y - 601;
			}

			if (mapPos.x < 0)mapPos.x = 0;
			if (mapPos.y < 0)mapPos.y = 0;
			Refresh(false);
		}
	}
}

void MapPanel::onLostCapture(wxMouseCaptureLostEvent& event) {
	ReleaseMouse();
}

void MapPanel::onLeavePanel(wxMouseEvent& event) {
	GetParent()->SetFocus();
}

void MapPanel::onEnterPanel(wxMouseEvent& event) {
	SetFocus();
}

wxImage MapPanel::getBasicMap() {
	return mapLevels[4].ConvertToImage();
}
