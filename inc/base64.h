#ifndef BASE64_H
#define BASE64_H

#include "../DSA/inc/string.h"

void display_sextets (String* plain_text);
String* encode_base64 (String* plain_text);
String* decode_base64 (String* cipher_text);

#endif	// BASE64_H
