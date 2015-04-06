#include "Plugin.hpp"
#include <iostream>
#include <dlfcn.h>
#include <stdexcept>

int main() {
	using std::cout;
	using std::cerr;

	// load the plug library
	void* plug = dlopen("./plugins/PluginX.so", RTLD_LAZY);
	if (!plug) {
		cerr << "Cannot load library: " << dlerror() << '\n';
		return 1;
	}

	// reset errors
	dlerror();

	// load the symbols
	create_t* create_plug = (create_t*) dlsym(plug, "create");
	const char* dlsym_error = dlerror();
	if (dlsym_error) {
		cerr << "Cannot load symbol create: " << dlsym_error << '\n';
		return 1;
	}

	// create an instance of the class
	Plugin* p = create_plug();

	// use the class
	try {
		p->do_something();
	} catch (std::runtime_error &e) {
		std::cerr << "Caught error: " << e.what() << std::endl;
	}

	// destroy the class
	delete p;

	// unload the plug library
	dlclose(plug);
}
