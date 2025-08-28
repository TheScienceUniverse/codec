#include <stdio.h>
#include <stdlib.h>

#include "./inc/test.h"

int main (void) {
	test_base64();
	test_adler32();

	return EXIT_SUCCESS;
}
