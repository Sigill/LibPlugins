#include "Plugin.hpp"
#include <iostream>
#include <dlfcn.h>

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

	destroy_t* destroy_plug = (destroy_t*) dlsym(plug, "destroy");
	dlsym_error = dlerror();
	if (dlsym_error) {
		cerr << "Cannot load symbol destroy: " << dlsym_error << '\n';
		return 1;
	}

	// create an instance of the class
	Plugin* p = create_plug();

	// use the class
	p->do_something();


	// destroy the class
	destroy_plug(p);

	// unload the plug library
	dlclose(plug);
}
