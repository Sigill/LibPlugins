#include "Plugin.hpp"

#include <iostream>

class PluginX : public Plugin {
public:
	virtual void do_something() {
		std::cout << "This is plugin X" << std::endl;
	}
};

extern "C" Plugin* create() {
	return new PluginX;
}

extern "C" void destroy(Plugin* p) {
	delete p;
}
