
#include "gtest/gtest.h"
#include "Utils/StringOperations.hpp"

TEST(StringOperationsTest, test_split_operation_with_existing_delimiters) {
    std::string const stringForSplit = "Text0 Text1 Text2";
    char const delimiter = ' ';

    StringVector result;
    ASSERT_NO_THROW(result = StringOperations::split(stringForSplit, delimiter));

    ASSERT_EQ(result.size(), 3);

    ASSERT_EQ(result[0], "Text0");
    ASSERT_EQ(result[1], "Text1");
    ASSERT_EQ(result[2], "Text2");
}

TEST(StringOperationsTest, test_split_operation_with_existing_delimiters_in_a_row) {
    std::string const stringForSplit = "Text0  Text1  Text2";
    char const delimiter = ' ';

    StringVector result;
    ASSERT_NO_THROW(result = StringOperations::split(stringForSplit, delimiter));

    ASSERT_EQ(result.size(), 3);

    ASSERT_EQ(result[0], "Text0");
    ASSERT_EQ(result[1], "Text1");
    ASSERT_EQ(result[2], "Text2");
}


TEST(StringOperationsTest, test_split_operation_without_existing_delimiters) {
    std::string const stringForSplit = "Text0 Text1 Text2";
    char const delimiter = ',';

    StringVector result;
    ASSERT_NO_THROW(result = StringOperations::split(stringForSplit, delimiter));

    ASSERT_EQ(result.size(), 1);

    ASSERT_EQ(result[0], stringForSplit);
}