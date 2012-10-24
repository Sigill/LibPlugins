mkdir -p plugins
gcc -Wall x.c -o plugins/x.so -shared -fPIC
gcc -Wall test_plugins.c -o test_plugins -ldl
