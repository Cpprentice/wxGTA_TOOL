#ifndef LOADINGFUNCTION_HPP
#define LOADINGFUNCTION_HPP

#include "mappanel.hpp"
#include <wx/wx.h>

class LoadingFrame;
class LoadingFunction;
/*
class LoadingTimer : public wxTimer {
	public:
		LoadingTimer(LoadingFunction* func);
		void Notify();
	private:
		LoadingFunction* func;
};
*/
class LoadingFunction{
	friend class LoadingTimer;
	public:
		void handle();
		unsigned int getTokens();
		bool isFinished();
		bool isReady();
		LoadingFunction();
		~LoadingFunction();

	protected:
		void returnTokens(unsigned int number);
		virtual void onTimer() = 0;

		unsigned int tokens;
		LoadingFrame* parent;
		//LoadingTimer next;
		bool finished;
		bool ready;
};

class TimeWait : public LoadingFunction {
	public:
		TimeWait(LoadingFrame* parent, unsigned int secs);
	private:
		void onTimer();
};

class MapCreator : public LoadingFunction {
	public:
		MapCreator(LoadingFrame* parent, MapPanel* panel);
		//void handle();
	private:
		MapPanel* panel;
		void onTimer();
};

#endif
