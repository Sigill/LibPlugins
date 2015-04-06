#include "Plugin.hpp"

#include <iostream>
#include <stdexcept>

class PluginX : public Plugin {
public:
	virtual void do_something() {
		std::cout << "This is plugin X" << std::endl;
		throw std::runtime_error("Plop");
	}
};

extern "C" Plugin* create() {
	return new PluginX;
}

