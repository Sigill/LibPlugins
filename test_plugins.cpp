/**
 * A sample program to load all the shared objects from the directory
 * "plugins" and call their misc() function
 */

#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <dlfcn.h>
#include <string.h>


#define PARENT_DIR ".."
#define CURRENT_DIR "."
#define PRG_VERSION "0.0a"

/* Prototype for the misc() function */
typedef void(*Misc)(char * buffer);

/* A nice struct for a plugin */
struct Plugin 
{
	/* Shared object handle */
	void *so;
	/* Misc() address, plugin version & info */
	Misc misc;
	char *version;
	char *info;
};

/* create an alias for easier usage*/
typedef struct Plugin Plugin;

/* A function for checking libdl errors */
int dlok(const char *msg)
{
	char *error;
	if ( (error = dlerror()) ) {
		printf("%s: %s\n", msg, error);
		return 0;
	}
	return 1;
}

/* Loads plugin named "soname" into the struct Plugin plugin*/
void *loadplugin(Plugin *plugin, const char *soname)
{
	printf("Loading %s...\n", soname);

	/* Load the library, resolve symbols as they are needed. */
	plugin->so = dlopen(soname, RTLD_LAZY);

	if ( plugin->so ) {
		/* Get the misc() address */
		plugin->misc = (Misc)dlsym(plugin->so, "misc");
		if (!dlok("\\-misc() not found")) return 0;

		/* Display plugin info */
		plugin->info = (char*)dlsym(plugin->so, "info");
		if (!dlok("\\-info not found")) return 0;
		printf("Plugin info: %s\n", plugin->info);
		/* Check program-plugin version match */
		plugin->version = (char*)dlsym(plugin->so, "version");
		if (!dlok("\\-version not found")) return 0;
		if (strcmp(plugin->version, PRG_VERSION)) {
			printf("Non-%s plugin version: %s\n", PRG_VERSION, plugin->version);
			return 0;
		}
	}

	return plugin->so;
}

/* A seperated unloader */
int unloadplugin(Plugin *plugin)
{
	return dlclose(plugin->so);
}

/* Define the directory containing plugins */
char plugindir[] = "./plugins";

int main(void)
{
	/* Pointers for a directory and an entry */
	DIR *dir;
	struct dirent *ep;

	/* A plugin */
	Plugin plugin;

	/* A temporary buffer */
	char buffer[200];

	/* A buffer to work on */
	char workbuffer[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	printf("Original workbuffer: %s\n", workbuffer);
	/* Grab the directory */
	dir = opendir(plugindir);

	if (dir) {
		/* Read all the entries - say there are only shared objects inside */
		while ( (ep = readdir(dir)) ) {
			/* Obviously skip these entries */
			if ( !strcmp(ep->d_name, PARENT_DIR) || !strcmp(ep->d_name, CURRENT_DIR) ) continue;

			/* Try to load the plugin */
			sprintf(buffer, "%s/%s", plugindir, ep->d_name);
			if ( loadplugin(&plugin, buffer) ) {

				/* Call the misc() func */
				(*plugin.misc)(workbuffer);
				printf("Workbuffer after misc(): %s\n", workbuffer);

				/* Release the plugin */
				unloadplugin(&plugin);
			} 
		}
		/* Close the directory */
		closedir(dir);
	} else {
		perror("Error opening dir \"./plugins\"\n");
		return -1;
	}

	return 0;
}

