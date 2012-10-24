mkdir -p plugins
echo Building plugin x
gcc -Wall x.cpp -o plugins/x.so -shared -fPIC
echo building plugin test app
gcc -Wall test_plugins.cpp -o test_plugins -ldl -lstdc++
