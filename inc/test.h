#ifndef TEST_H
#define TEST_H

#include "./text_style.h"

#define COLOR_PASSED BOLD_GREEN
#define COLOR_FAILED BOLD_RED 
#define COLOR_OFF RESET_STYLE

#define TEST(cond, msg) {													\
	if (cond) {																\
		printf ("\t[" COLOR_PASSED "PASSED" COLOR_OFF "]: (%s)\n", msg);	\
	} else {																\
		printf ("\t[" COLOR_FAILED "FAILED" COLOR_OFF "]: (%s)				\
			file:%s line:%d\n", msg, __FILE__, __LINE__);					\
	}																		\
}

#include "../DSA/inc/string.h"

#include "./base64.h"
void test_base64 (void);

#endif // TEST_H
