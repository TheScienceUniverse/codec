#include "../inc/test.h"

void test_adler32 (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [Adler32]\n" RESET_STYLE);

	String* genuine_text = create_string (13, "Hello, World!");
	String* encoded_text = encode_adler32 (genuine_text);
	String* awaited_text = create_string (8, "1f9e046a");
	TEST (Cmp_Equivalent == compare_strings (encoded_text, awaited_text), "Matched encoded text with expected encoded text");
	delete_string (&awaited_text);
	delete_string (&encoded_text);
	delete_string (&genuine_text);

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [Adler32]\n" RESET_STYLE);
}
