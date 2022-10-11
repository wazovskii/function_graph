#include "../src/parser.hpp"
#include "../src/polish_notation.hpp"
#include <string>
#include <gtest/gtest.h>


TEST(parser_cxx, parser) {
    std::string test1 = "sin(x)";
    parser *test_parser1 = new parser(test1);
    std::vector<std::string> _test1= {"sin", "(", "x", ")"};
    EXPECT_EQ(test_parser1->run(), _test1);

    std::string test2 = "2x+(tg(30)/4+7)";
    parser *test_parser2 = new parser(test2);
    std::vector<std::string> _test2= {"2", "*", "x", "+", "(", "tg", "(", "30", ")", "/", "4", "+", "7", ")"};
    EXPECT_EQ(test_parser2->run(), _test2);

    std::string test3 = "log(x)";
    parser *test_parser3 = new parser(test3);
    EXPECT_EQ(test_parser3->run().size(), (size_t)0);
}

TEST(parser_cxx, polish_notation) {
    std::vector<std::string> test1= {"sin", "(", "x", ")"};
    translate_to_polish(test1);
    std::vector<std::string> _test1= {"x", "sin"};
    EXPECT_EQ(test1, _test1);

    std::vector<std::string> test2= {"1", "+", "2", "*", "3"};
    translate_to_polish(test2);
    std::vector<std::string> _test2= {"1", "2", "3", "*", "+"};
    EXPECT_EQ(test2, _test2);

    std::vector<std::string> test3= {"(", "1", "+", "2", ")", "*", "3"};
    translate_to_polish(test3);
    std::vector<std::string> _test3= {"1", "2", "+", "3", "*"};
    EXPECT_EQ(test3, _test3);
}

TEST(parser_cxx, calculate) {
    std::vector<std::string> test1= {"sin", "(", "x", ")"};
    translate_to_polish(test1);
    for (double i = -M_PI; i < M_PI; i += 0.001)
        ASSERT_LT(fabs(calculate(test1, i) - sin(i)), 1e-6);
    test1= {"cos", "(", "x", ")"};
    translate_to_polish(test1);
    for (double i = -M_PI; i < M_PI; i += 0.001)
        ASSERT_LT(fabs(calculate(test1, i) - cos(i)), 1e-6);

    std::vector<std::string> test2= {"2", "/", "3"};
    translate_to_polish(test2);
    ASSERT_LT(fabs(calculate(test2, M_PI) - (2.0/3.0)), 1e-6);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}