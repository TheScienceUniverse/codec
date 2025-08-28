#include "../inc/adler32.h"

#define PROCESSOR_ENDIAN_LITTLE *((uint32_t*)("\x01\x02\x03\x04")) == 0x04030201
#define PROCESSOR_ENDIAN_BIG *((uint32_t*)("\x01\x02\x03\x04")) == 0x01020304
#define PROCESSOR_ENDIAN_PDP *((uint32_t*)("\x01\x02\x03\x04")) == 0x02010304

String* encode_adler32 (String* input) {
	uint16_t ADLER_PRIME = 65521;	// largest prime smaller than 65536 (i.e. 2^16)
	uint16_t a = 1, b = 0;
	BYTE* x = (BYTE*)(input -> text);

	for (size_t i = 0; i < input -> length; i++) {
		a += *x++;

		if (a > ADLER_PRIME) {
			a -= ADLER_PRIME;
		}

		b += a;

		if (b > ADLER_PRIME) {
			b -= ADLER_PRIME;
		}
	}

	uint32_t checksum = (b << 16) + a;

	String* checksum_string = create_string (8, "_--_");
	char* y = checksum_string -> text;
	x = (BYTE*)(&checksum);

	if (PROCESSOR_ENDIAN_BIG) {
		sprintf (y + 0, "%02x", *(x + 0));
		sprintf (y + 2, "%02x", *(x + 1));
		sprintf (y + 4, "%02x", *(x + 2));
		sprintf (y + 6, "%02x", *(x + 3));
	} else if (PROCESSOR_ENDIAN_LITTLE) {
		sprintf (y + 0, "%02x", *(x + 3));
		sprintf (y + 2, "%02x", *(x + 2));
		sprintf (y + 4, "%02x", *(x + 1));
		sprintf (y + 6, "%02x", *(x + 0));
	}

	return checksum_string;
}
