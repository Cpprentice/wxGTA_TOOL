#ifndef LOADINGFUNCTION_HPP
#define LOADINGFUNCTION_HPP

class LoadingFunction {
	public:
		virtual void handle() = 0;
		unsigned int getTokens();
	protected:
		unsigned int tokens;
};

#endif