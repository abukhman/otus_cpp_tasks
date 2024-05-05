#include <gtest/gtest.h>
#include "mylibversion.h"

TEST(test_version, test_version)
{
	ASSERT_NE(version(), 100);
}
