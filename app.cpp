#include "app.hpp"
#include "loadingframe.hpp"
#include "mainframe.hpp"

IMPLEMENT_APP(App);

bool App::OnInit() {

	wxInitAllImageHandlers();

	MainFrame* mainframe = new MainFrame();
	LoadingFrame* frame = new LoadingFrame(mainframe);
	frame->Show();
	return true;
}
