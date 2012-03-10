#include "app.hpp"

IMPLEMENT_APP(App);

bool App::OnInit() {

	wxFrame* frame = new wxFrame(0, wxID_ANY, wxT("GTA SAMP Tool"));
	frame->Show();
	return true;
}
