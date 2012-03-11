#include "app.hpp"
#include "loadingframe.hpp"

IMPLEMENT_APP(App);

bool App::OnInit() {

	wxInitAllImageHandlers();

	LoadingFrame* frame = new LoadingFrame();
	frame->Show();
	return true;
}
