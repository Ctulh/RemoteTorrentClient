
#pragma once

#include "Utils/JsonConfigReader.hpp"

#include <gtest/gtest.h>

TEST(JsonConfigReaderTest, test_config_reader_read_json_file) {
    JsonConfigReader configReader("test.json");

    std::optional<std::string> value;

    ASSERT_NO_THROW(value = configReader["BotApi"]);

    ASSERT_TRUE(value.has_value());
    ASSERT_EQ(value.value(), "testApi");
}