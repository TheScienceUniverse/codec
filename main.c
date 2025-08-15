#include <stdio.h>
#include <stdlib.h>

#include "./DSA/inc/string.h"
#include "./inc/base64.h"

int main (int argc, char* argv[]) {
	if (argc < 4) {
		perror ("Not enough input! Please give type flag and value!");
		exit (EXIT_FAILURE);
	}

	String* input = create_string (strlen (argv [3]), argv [3]);
	String* output = NULL;

	if (compare_raw_strings_shh (2, "-e", 2, argv [1])) {
		puts ("Encoding...");
		output = encode (input);
	} else if (compare_raw_strings_shh (2, "-d", 2, argv [1])) {
		puts ("Decoding...");
		output = decode (input);
	}

	printf ("[");
	display_string (input);
	printf ("] -> [");
	display_string (output);
	printf ("]\n");

	delete_string (&output);
	delete_string (&input);

	return EXIT_SUCCESS;
}
