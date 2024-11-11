#include <gmock/gmock.h>
#include <gtest/gtest.h>

const char *data_filename = "../../tests/range_queries_data.txt";
const char *answers_filename = "../../tests/range_queries_answers.txt";

int main(int argc, char *argv[])
{
    if(argc >= 3)
    {
        data_filename = argv[1];
        answers_filename = argv[2];
    }
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

