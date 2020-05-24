#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "libusertweet.h"

int fortytwo()
{
	    return 42;
}

int tweet() {
	GoInt id;
	struct GetLastTweetByHandle_return ut;
	void *handle;
	char *error;

	handle = dlopen ("./libusertweet.so", RTLD_LAZY);
	if (!handle) {
		fprintf(stderr, "%s\n", dlerror());
		exit(1);
	}

	GoInt (*gethandle)() = dlsym(handle, "NewHandleID");
	if ((error = dlerror()) != NULL)  {
		fprintf(stderr, "%s\n", error);
		exit(1);
	}

	id = (*gethandle)();

	struct GetLastTweetByHandle_return (*gettweet)(GoInt, char*) = dlsym(handle, "GetLastTweetByHandle");
	if ((error = dlerror()) != NULL)  {
		fprintf(stderr, "%s\n", error);
		exit(1);
	}

	ut = (*gettweet)(id, "VersitySoftware");
	if (ut.r0 != 0) {
		printf("Error: %s\n", ut.r2);
		exit(1);
	}

	printf("%s\n", ut.r1);
	return 0;
}

int encrypt(const char * value) {
	printf("%s\n", value);
	return 0;
}

typedef int (*intFunc) ();

#ifdef _WIN32
static const char libut[] = "./libusertweet.dll";
#elif
static const char libut[] = "./libusertweet.so";
#endif

int main() {
	GoInt ret;
	void *handle;

	handle = dlopen (libut, RTLD_LAZY);
	if (!handle) {
		fprintf(stderr, "%s\n", dlerror());
		exit(1);
	}

	GoInt (*InitEncrypt)(intFunc f) = dlsym(handle, "InitEncrypt");

	ret = (*InitEncrypt)(fortytwo);

	printf("%lld\n", ret);

	return 0;
}


