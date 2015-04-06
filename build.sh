mkdir -p plugins

echo Building plugin x
gcc -Wall x.cpp -o plugins/x.so -shared -fPIC
echo building plugin test app
gcc -Wall test_plugins.cpp -o test_plugins -ldl -lstdc++

echo "Building plugin x (class)"
gcc -Wall PluginX.cpp -g -o plugins/PluginX.so -shared -fPIC
echo building class plugin test app
gcc -Wall test_plugin_class.cpp -g -o test_plugin_class -ldl -lstdc++
