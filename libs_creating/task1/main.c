#include <stdio.h>
#include <dlfcn.h>
#include <math.h>

int main(int argc, char* argv[]) {

	void* library;
	int (*powerfunc)(int* param);

	library = dlopen("libyyy.so", RTLD_LAZY);
	if (!library) {
		fprintf(stderr, "dlopen() error %s\n", dlerror());
		return -1;
	}

	powerfunc = dlsym(library, argv[1]);
	int number = 25;

	printf("RESULT of %s(%d) = %d\n", argv[1], number, (*powerfunc)(&number));

	dlclose(library);

	return 0;
}

