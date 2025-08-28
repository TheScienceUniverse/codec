#include "../inc/test.h"

void test_base64 (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [Base64]\n" RESET_STYLE);

	String* genuine_text = create_string (3, "Man");
	String* awaited_text = create_string (4, "TWFu");
	String* encoded_text = encode_base64 (genuine_text);
	TEST (Cmp_Equivalent == compare_strings (encoded_text, awaited_text), "Matched encoded text with expected encoded text");
	String* decoded_text = decode_base64 (encoded_text);
	TEST (Cmp_Equivalent == compare_strings (decoded_text, genuine_text), "Matched decoded text with genuine text");
	delete_string (&encoded_text);
	delete_string (&decoded_text);
	delete_string (&awaited_text);
	delete_string (&genuine_text);

	genuine_text = create_string (2, "Ma");
	awaited_text = create_string (4, "TWE=");
	encoded_text = encode_base64 (genuine_text);
	TEST (Cmp_Equivalent == compare_strings (encoded_text, awaited_text), "Matched encoded text with expected encoded text");
	decoded_text = decode_base64 (encoded_text);
	TEST (Cmp_Equivalent == compare_strings (decoded_text, genuine_text), "Matched decoded text with genuine text");
	delete_string (&encoded_text);
	delete_string (&decoded_text);
	delete_string (&awaited_text);
	delete_string (&genuine_text);

	genuine_text = create_string (1, "M");
	awaited_text = create_string (4, "TQ==");
	encoded_text = encode_base64 (genuine_text);
	TEST (Cmp_Equivalent == compare_strings (encoded_text, awaited_text), "Matched encoded text with expected encoded text");
	decoded_text = decode_base64 (encoded_text);
	TEST (Cmp_Equivalent == compare_strings (decoded_text, genuine_text), "Matched decoded text with genuine text");
	delete_string (&encoded_text);
	delete_string (&decoded_text);
	delete_string (&awaited_text);
	delete_string (&genuine_text);

	genuine_text = create_string (27, "Many hands make light work.");
	awaited_text = create_string (36, "TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu");
	encoded_text = encode_base64 (genuine_text);
	TEST (Cmp_Equivalent == compare_strings (encoded_text, awaited_text), "Matched encoded text with expected encoded text");
	decoded_text = decode_base64 (encoded_text);
	TEST (Cmp_Equivalent == compare_strings (decoded_text, genuine_text), "Matched decoded text with genuine text");
	delete_string (&encoded_text);
	delete_string (&decoded_text);
	delete_string (&awaited_text);
	delete_string (&genuine_text);

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [Base64]\n" RESET_STYLE);
}
