#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

TEST_CASE("Catch operability", "[simple]"){
    REQUIRE(1+1 == 2);
}

#include "funcs.h"

TEST_CASE("test 1, file", "[simple]"){
    std::ofstream inputPrepare;
    inputPrepare.open ("input.txt", std::ofstream::trunc);
    inputPrepare<<
                "7\n"
                "2 1\n"
                "4 5\n"
                "7 4\n"
                "8 2\n"
                "9 6\n"
                "11 3\n"
                "15 3\n"
                "1\n"
                "2 6"
            ;
    inputPrepare.close();

    std::ifstream input( "input.txt", std::ofstream::in);
    std::ofstream output("output.txt", std::ofstream::trunc);
    parseFile(input,output);
    input.close();
    output.close();

    std::ifstream outputCheck("output.txt", std::ofstream::in);
    std::stringstream buffer;
    buffer<<outputCheck.rdbuf();
    outputCheck.close();
    REQUIRE(buffer.str() ==
            "4\n"
    );
}

TEST_CASE("test 2", ""){
    std::stringstream input(
            "6\n"
            "1 1\n"
            "3 2\n"
            "5 6\n"
            "7 2\n"
            "10 4\n"
            "11 1\n"
            "3\n"
            "5 6\n"
            "1 4\n"
            "4 2"
            );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() ==
            "0\n"
            "5\n"
            "4\n"
    );
}

TEST_CASE("1 raise and 1 climb, forward and reverse", ""){
    std::stringstream input(
            "9\n"
            "1 1\n"
            "2 1\n"
            "3 4\n"
            "5 9\n"
            "6 9\n"
            "7 7\n"
            "8 3\n"
            "9 3\n"
            "10 1\n"
            "20\n"
            "1 1\n"//0
            "1 2\n"//0
            "1 3\n"//3
            "2 3\n"//3
            "2 3\n"//3
            "1 4\n"//8
            "2 4\n"//8
            "3 4\n"//5
            "1 5\n"//8
            "1 9\n"//8
            "5 6\n"//0
            "5 8\n"//0
            "4 9\n"//0
            "4 3\n"//0
            "4 1\n"//0
            "6 5\n"//2
            "7 5\n"//6
            "8 5\n"//6
            "9 4\n"//8
            "9 1\n"//8
    );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() ==
            "0\n"
            "0\n"
            "3\n"
            "3\n"
            "3\n"
            "8\n"
            "8\n"
            "5\n"
            "8\n"
            "8\n"
            "0\n"
            "0\n"
            "0\n"
            "0\n"
            "0\n"
            "2\n"
            "6\n"
            "6\n"
            "8\n"
            "8\n"
    );
}

TEST_CASE("saw", ""){
    std::stringstream input(
            "6\n"
            "1 1\n"
            "3 4\n"
            "5 2\n"
            "7 7\n"
            "10 2\n"
            "11 3\n"
            "4\n"
            "1 6\n"//9
            "6 1\n"//7
            "3 5\n"//5
            "5 3\n"//5
    );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() ==
            "9\n"
            "7\n"
            "5\n"
            "5\n"
    );
}
