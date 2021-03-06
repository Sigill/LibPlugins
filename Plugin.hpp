#ifndef PLUGINS_HPP
#define PLUGINS_HPP

class Plugin {
public:
	Plugin() {}
	virtual ~Plugin() {}
	virtual void do_something() = 0;
};

// the types of the class factories
typedef Plugin* create_t();

#endif /* PLUGINS_HPP */
