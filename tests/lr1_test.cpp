#include <lib/lr1.h>
#include <gtest/gtest.h>
#include <vector>
#include <utility>
#include <string>
#include <limits>

using namespace std;

TEST(NegativeScenarios, Should_return_error_when_empty_collection)
{
    vector<float> arr = {};
    int multiple = 1;
    tuple<vector<float>, float, vector<error>> result = getProductOfMultiples(arr, multiple);

    vector<float> resultCollection = get<0>(result);
    float resultMult = get<1>(result);
    vector<error> resultErrors = get<2>(result);

    EXPECT_EQ(resultErrors.empty(), false);
    EXPECT_EQ(resultErrors.size(), 1);
    bool isEqual = resultErrors[0].message == "Переданная коллекция не должна быть пустой." && resultErrors[0].code == 2;

    EXPECT_EQ(isEqual, true);
}

TEST(GetProducNegativeScenariostOfMultiples, Should_return_error_when_big_collection)
{
    vector<float> arr(1025, 1.0);
    int multiple = 1;
    tuple<vector<float>, float, vector<error>> result = getProductOfMultiples(arr, multiple);

    vector<float> resultCollection = get<0>(result);
    float resultMult = get<1>(result);
    vector<error> resultErrors = get<2>(result);

    EXPECT_EQ(resultErrors.empty(), false);
    EXPECT_EQ(resultErrors.size(), 1);
    bool isEqual = resultErrors[0].message == "В переданной коллекции должно быть меньше 1024 элементов." && resultErrors[0].code == 3;
    EXPECT_EQ(isEqual, true);
}

TEST(PositiveScenarios, Should_return_success_when_one_element) 
{
    float numeber = 10;
    vector<float> arr = {numeber}; 
    tuple<vector<float>, float, vector<error>> result = getProductOfMultiples(arr, 1);
    vector<float> resultCollection = get<0>(result);
    float resultMult = get<1>(result);
    vector<error> resultErrors = get<2>(result);

    EXPECT_EQ(resultCollection.size(), 1);
    EXPECT_EQ(resultMult, numeber);
    EXPECT_EQ(resultErrors.empty(), true);    
}

TEST(NegativeScenarios, Should_return_error_when_multiple_is_zero)
{
    vector<float> arr(10, 1.0);
    int multiple = 0;
    tuple<vector<float>, float, vector<error>> result = getProductOfMultiples(arr, multiple);

    vector<float> resultCollection = get<0>(result);
    float resultMult = get<1>(result);
    vector<error> resultErrors = get<2>(result);

    EXPECT_EQ(resultErrors.empty(), false);
    EXPECT_EQ(resultErrors.size(), 1);
    bool isEqual = resultErrors[0].message == "Заданное число должно быть больше нуля." && resultErrors[0].code == 1;

    EXPECT_EQ(isEqual, true);
}

TEST(NegativeScenarios, Should_return_error_when_multiple_is_negative)
{
    vector<float> arr(50, 1.0);
    int multiple = -1;
    tuple<vector<float>, float, vector<error>> result = getProductOfMultiples(arr, multiple);

    vector<float> resultCollection = get<0>(result);
    float resultMult = get<1>(result);
    vector<error> resultErrors = get<2>(result);

    EXPECT_EQ(resultErrors.empty(), false);
    EXPECT_EQ(resultErrors.size(), 1);
    bool isEqual = resultErrors[0].message == "Заданное число должно быть больше нуля." && resultErrors[0].code == 1;

    EXPECT_EQ(isEqual, true);
}

TEST(PositiveScenarios, Should_return_all_numbers_when_multiple_is_one)
{
    vector<float> arr = {1, 2, 3, 4, 5};
    tuple<vector<float>, float, vector<error>> result = getProductOfMultiples(arr, 1);

    vector<float> resultCollection = get<0>(result);
    float resultMult = get<1>(result);
    vector<error> resultErrors = get<2>(result);

    EXPECT_EQ(resultCollection.size(), 5);
    EXPECT_EQ(resultMult, 1 * 2 * 3 * 4 * 5);
    EXPECT_EQ(resultErrors.empty(), true);    
}

TEST(NegativeScenarios, Should_return_errors_when_multiple_is_zero_and_empty_collection)
{
    vector<float> arr = {};
    int multiple = 0;
    tuple<vector<float>, float, vector<error>> result = getProductOfMultiples(arr, multiple);
            
    vector<float> resultCollection = get<0>(result);
    float resultMult = get<1>(result);
    vector<error> resultErrors = get<2>(result);

    EXPECT_EQ(resultErrors.empty(), false);
    EXPECT_EQ(resultErrors.size(), 2);
}

TEST(NegativeScenarios, Should_return_errors_when_multiple_is_zero_and_big_collection)
{
    vector<float> arr(1025, 1.0);
    int multiple = 0;
    tuple<vector<float>, float, vector<error>> result = getProductOfMultiples(arr, multiple);

    vector<float> resultCollection = get<0>(result);
    float resultMult = get<1>(result);
    vector<error> resultErrors = get<2>(result);

    EXPECT_EQ(resultErrors.empty(), false);
    EXPECT_EQ(resultErrors.size(), 2);
}

//TEST(NegativeScenarios, Should_return_error_when_too_big_numbers_in_collection)
//{
//    vector<float> largeValues = { 1e38f, 2e38f };
//    int multiple = 1;
//    tuple<vector<float>, float, vector<error>> result = getProductOfMultiples(largeValues, multiple);
//
//    vector<float> resultCollection = get<0>(result);
//    float resultMult = get<1>(result);
//    vector<error> resultErrors = get<2>(result);
//
//    EXPECT_EQ(resultErrors.empty(), false);
//    EXPECT_EQ(resultErrors.size(), 1);
//
//    bool isEqual = resultErrors[0].message == "Произошло переполнение при умножении." && resultErrors[0].code == 4;
//    EXPECT_EQ(isEqual, true);   
//}

TEST(NegativeScenarios, Should_return_error_when_too_big_numbers_in_collection)
{
    vector<float> largeValues = { 1e38f, 2e38f };
    int multiple = 1;
    tuple<vector<float>, float, vector<error>> result = getProductOfMultiples(largeValues, multiple);

    vector<float> resultCollection = get<0>(result);
    float resultMult = get<1>(result);
    vector<error> resultErrors = get<2>(result);

    EXPECT_EQ(resultErrors.empty(), false);
    EXPECT_EQ(resultErrors.size(), 1);

    bool isEqual = resultErrors[0].message == "Произошло переполнение при умножении." && resultErrors[0].code == 4;
    EXPECT_EQ(isEqual, true);
}

TEST(PositiveScenarios, Should_return_correct_result_when_1024_elements_in_collection)
{
    vector<float> arr(1024, 1.0);
    int multiple = 1;
    tuple<vector<float>, float, vector<error>> result = getProductOfMultiples(arr, multiple);

    vector<float> resultCollection = get<0>(result);
    float resultMult = get<1>(result);
    vector<error> resultErrors = get<2>(result);

    EXPECT_EQ(resultErrors.empty(), true);

    EXPECT_EQ(resultMult == 1, true);
}

TEST(PositiveScenarios, Should_return_correct_answer_when_collection_contains_negative_numbers)
{
    vector<float> arr = { 1, -2, 3, -4, 5 };
    int multiple = 2;
    tuple<vector<float>, float, vector<error>> result = getProductOfMultiples(arr, multiple);

    vector<float> resultCollection = get<0>(result);
    float resultMult = get<1>(result);
    vector<error> resultErrors = get<2>(result);

    EXPECT_EQ(resultCollection.size(), 3);
    EXPECT_EQ(resultMult, 15);
    EXPECT_EQ(resultErrors.empty(), true);
}

TEST(PositiveScenarios, Should_return_first_number_when_greater_than_arr_size)
{
    float firstNumeber = 10;
    vector<float> arr = { firstNumeber, 14, 15, 20, 21, 25, 30 };
    tuple<vector<float>, float, vector<error>> result = getProductOfMultiples(arr, 100);
    vector<float> resultCollection = get<0>(result);
    float resultMult = get<1>(result);
    vector<error> resultErrors = get<2>(result);

    EXPECT_EQ(resultCollection.size(), 1);
    EXPECT_EQ(resultMult, firstNumeber);
    EXPECT_EQ(resultErrors.empty(), true);
}
