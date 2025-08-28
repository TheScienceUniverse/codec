#include <stdio.h>
#include <stdlib.h>

#include "./DSA/inc/string.h"
#include "./inc/base64.h"
#include "./inc/adler32.h"

int main (int argc, char* argv[]) {
	if (argc < 5) {
		puts ("$ codec -t <\"type\"> [-e/-d] <\"input\">[ENTER]");
		perror ("Not enough input! Please give type flag and value!");
		exit (EXIT_FAILURE);
	}

	enum Code_Type {
		C_Base64
		, C_Adler32
		, C_Undefined
	};

	enum Process_Type {
		P_Encoding
		, P_Decoding
		, P_Undefined
	};

	enum Code_Type c_type;
	enum Process_Type p_type;

	if (compare_raw_strings_shh (2, "-t", 2, argv [1])) {
		if (compare_raw_strings_shh (6, "base64", 6, argv [2])) {
			c_type = C_Base64;
		} else if (compare_raw_strings_shh (7, "adler32", 7, argv [2])) {
			c_type = C_Adler32;
		}
	}

	String* input = create_string (strlen (argv [4]), argv [4]);
	String* output = NULL;

	if (compare_raw_strings_shh (2, "-e", 2, argv [3])) {
		p_type = P_Encoding;
	} else if (compare_raw_strings_shh (2, "-d", 2, argv [3])) {
		p_type = P_Decoding;
	}

	if (P_Undefined != p_type) {
		input = create_string (strlen (argv [4]), argv [4]);
	}

	if (C_Base64 == c_type && P_Encoding == p_type) {
		puts ("Encoding Base64...");
		output = encode_base64 (input);
	} else if (C_Base64 == c_type && P_Decoding == p_type) {
		puts ("Decoding Base64...");
		output = decode_base64 (input);
	} else if (C_Adler32 == c_type && P_Encoding == p_type) {
		puts ("Encoding Adler32...");
		output = encode_adler32 (input);
	} else if (C_Adler32 == c_type && P_Decoding == p_type) {
		puts ("Decoding not available for Base64...");
	} else {
		perror ("Unknown input!\n");
		return (EXIT_FAILURE);
	}

/*
	if (compare_raw_strings_shh (2, "-e", 2, argv [3])) {
		puts ("Encoding...");
		output = encode_base64 (input);
	} else if (compare_raw_strings_shh (2, "-d", 2, argv [3])) {
		puts ("Decoding...");
		output = decode_base64 (input);
	}
*/
	printf ("[");
	display_string (input);
	printf ("] -> [");
	display_string (output);
	printf ("]\n");

	delete_string (&output);
	delete_string (&input);

	return EXIT_SUCCESS;
}
