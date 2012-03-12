#include "loadingfunction.hpp"
#include <wx/utils.h>

unsigned int LoadingFunction::getTokens() {
	return tokens;
}

TimeWait::TimeWait(unsigned int secs) {
	tokens = secs;
}

void TimeWait::handle() {
	wxSleep(tokens);
}
