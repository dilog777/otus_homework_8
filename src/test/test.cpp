#include <gtest/gtest.h>

#include "lib.h"



TEST(test_google_version, test_valid_build)
{
	EXPECT_TRUE(buildNumber() > 0);
}
