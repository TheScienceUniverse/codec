#include "../inc/base64.h"

String* encode_base64 (String* plain_text) {
	if (NULL == plain_text) {
		perror ("No input string is given to encode to base64!");
		exit (EXIT_FAILURE);
	}

	size_t byte_count = plain_text -> length;
	BYTE leftout_byte_count = byte_count % 3;
	size_t pad_count = 0;
	size_t triplet_count = byte_count / 3;

	if (leftout_byte_count == 2) {	// 8m = 6n + 2
		pad_count = 1;
	} else if (leftout_byte_count == 1) {	// 8m = 6n + 4
		pad_count = 2;
	} else {	// 8m = 6n = 24x [L.C.M. (6, 8) = 24]
		pad_count = 0;
	}

	if (pad_count > 0) {
		++triplet_count;
	}

	// 01001000 01100101 01101100
	// 010010#00 0110#0101 01#101100	// break into sextets
	// 00010010 00000110 00010101 00101100	// leftpad 00 for octects

	const char* dict = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	String* encoded_text = create_string (4 * triplet_count, plain_text -> text);

	if (NULL == encoded_text -> text) {
		perror ("Unable to allocate memory for base64 encoding!");
		exit (EXIT_FAILURE);
	}

	char* dst_ptr = encoded_text -> text;

	BYTE* src_ptr = (BYTE*)(plain_text -> text);
	BYTE b0, b1, b2;	// byte triplets
	BYTE i0, i1, i2, i3;	// sextet indexes
	char s0, s1, s2, s3;	// sextet characters

	for (size_t i = 0; i < triplet_count; i++) {
		// fill up the byte tripplets = 24 bits
		b0 = *src_ptr++;
		b1 = *src_ptr++;
		b2 = *src_ptr++;

		// emptying memory in the last iteration
		if (i == triplet_count - 1) {
			if (pad_count > 0) {
				b2 = 0x00;
			}

			if (pad_count > 1) {
				b1 = 0x00;
			}
		}

		// sextets
		// 6 bit values
		// stored inside 8 bit variables
		// with 00 as first 2 bits
		i0 = b0 >> 2;
		i1 = ((b0 << 4) & 0x30) | (b1 >> 4); // 0011 0000
		i2 = ((b1 << 2) & 0x3c) | (b2 >> 6); // 0011 1100
		i3 = b2 & 0x3f; // 0011 1111

		// get the 4 characters
		s0 = *(dict + i0);
		s1 = *(dict + i1);
		s2 = (i2 < 64) ? *(dict + i2) : '=';
		s3 = (i3 < 64) ? *(dict + i3) : '=';

		// padding in the last iteration
		if (i == triplet_count - 1) {
			if (pad_count > 0) {
				s3 = '=';
			}

			if (pad_count > 1) {
				s2 = '=';
			}
		}

//		printf ("%c%c%c%c\n", s0, s1, s2, s3);

		// put the 4 characters
		*dst_ptr++ = s0;
		*dst_ptr++ = s1;
		*dst_ptr++ = s2;
		*dst_ptr++ = s3;
	}

	return encoded_text;
}

String* decode_base64 (String* encoded_text) {
	if (NULL == encoded_text) {
		perror ("No input string is given to decode to base64!");
		exit (EXIT_FAILURE);
	}
//printf ("%02lx\n", encoded_text -> length & 0x03);
//return NULL;
	if (0x00 != (encoded_text -> length & 0x03)) {	// modulo 4
		perror ("Corrupted input string format to decode to base64!");
		exit (EXIT_FAILURE);
	}

	size_t pad_count = 0;
	char* src_ptr = encoded_text -> text + encoded_text -> length - 1;
	size_t quadruplet_count = encoded_text -> length / 4;
	

	if ('=' == *src_ptr--) {	// for single pad
		++pad_count;
	}

	if ('=' == *src_ptr--) {	// for double pad
		++pad_count;
	}

	size_t orig_char_count = quadruplet_count * 3 - pad_count;

	String* dict = create_string (0, NULL);
	dict -> text = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	dict -> length = 64;

	BYTE i0, i1, i2, i3;	// 4 indexes // 6 LSBs relevant
	BYTE c0, c1, c2;	// original bytes, all 8 bits relevant

	src_ptr = encoded_text -> text;

	String* decoded_text = create_string (0, "");
	decoded_text -> text = malloc (orig_char_count * sizeof (char));

	if (NULL == decoded_text -> text) {
		perror ("Unable to allocate memory for base64 encoding!");
		exit (EXIT_FAILURE);
	}

	decoded_text -> length = orig_char_count;
	char* dst_ptr = decoded_text -> text;

	// 00010011 00010110 00000101 00101110
	// 00-010011 00-010110 00-000101 00-101110
	// 010011 01#0110 0001#01 101110

	for (size_t i = 0; i < quadruplet_count; i++) {
		// get the 6 bit index value of 8 bit base64 character
		i0 = (BYTE) get_char_first_index (dict, *src_ptr++);
		i1 = (BYTE) get_char_first_index (dict, *src_ptr++);
		i2 = (BYTE) get_char_first_index (dict, *src_ptr++);
		i3 = (BYTE) get_char_first_index (dict, *src_ptr++);

		// get the 3 characters (3 * 8 bits)
		c0 = i0 << 2 | i1 >> 4;
		c1 = i1 << 4 | (i2 >> 2 & 0x0f);
		c2 = i2 << 6 | i3;

		if (0xff == i3) {
			c2 = 0x0;
		}

		if (0xff == i2) {
			c1 = 0x0;
		}

		// put the 3 characters
		*dst_ptr++ = c0;
		*dst_ptr++ = c1;	// CHECK NOT IMPLEMENTED
		*dst_ptr++ = c2;	// CHECK NOT IMPLEMENTED
	}

	dict -> text = NULL;
	dict -> length = 0;
	delete_string (&dict);

	return decoded_text;
}
