#include <lib/lr1.h>
#include <gtest/gtest.h>
#include <vector>
#include <utility>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

using namespace std;


string readFileIntoString(string path) 
{
    ifstream fileStream(path);
    stringstream buffer;
    buffer << fileStream.rdbuf();
    return buffer.str();
}

class TestCase {
public:
    string testName; // Добавлено новое поле testName
    vector<float> InputCollection;
    int Multiple;
    float ExpectedResult;
    vector<float> ExpectedCollection;
    vector<int> ExpectedErrors;

    // Функция для десериализации объекта TestCase из JSON
    static TestCase from_json(const json& j) {
        TestCase tc;
        j.at("testName").get_to(tc.testName); // Парсинг нового поля
        j.at("InputCollection").get_to(tc.InputCollection);
        j.at("Multiple").get_to(tc.Multiple);
        j.at("ExpectedResult").get_to(tc.ExpectedResult);
        j.at("ExpectedCollection").get_to(tc.ExpectedCollection);
        j.at("ExpectedErrors").get_to(tc.ExpectedErrors);
        return tc;
    }
};

// Функция для парсинга коллекции объектов TestCase из строки JSON
vector<TestCase> parseTestCasesFromJson(const string& jsonString) {
    auto j = json::parse(jsonString);
    vector<TestCase> testCases;
    for (const auto& item : j) {
        testCases.push_back(TestCase::from_json(item));
    }
    return testCases;
}


class TestFixture : public ::testing::Test {
protected:
    // Здесь вы можете добавить дополнительные настройки для тестов
    // в функции SetUp()
    void SetUp() override
    {
        
        fileInput = readFileIntoString("../../../../data/tests.json");
        cases = parseTestCasesFromJson(fileInput);

        /*char cwd[FILENAME_MAX];
        if (_getcwd(cwd, sizeof(cwd)) != NULL) {
            cout << "Текущий рабочий каталог: " << cwd << endl;
        }
        else {
            cerr << "Ошибка при получении текущего рабочего каталога" << endl;
        }*/
    }

    string fileInput;
    vector<TestCase> cases;
};

bool CheckErrors(vector<int> expectedErrors, vector<error> errors) 
{
    if(errors.size() != expectedErrors.size())
        return false;
    if (errors.size() != 0)
        for (size_t i = 0; i < errors.size(); i++)
            if (errors[i].code != expectedErrors[i]) return false;
    return true;
}
bool CheckArray(vector<float> expectedArr, vector<float> resultArr) 
{
    if (expectedArr.size() != resultArr.size())
        return false;

    for (size_t i = 0; i < expectedArr.size(); i++)
        if (expectedArr[i] != resultArr[i])
            return false;
    
    return true;
}

TestCase GetTestCaseByTitle(string testName, vector<TestCase> testCases)
{
    for (size_t i = 0; i < testCases.size(); i++)
    {
        if (testCases[i].testName == testName)
            return testCases[i];
    }
    TestCase tc;
    return tc;
}
void PrintInfo(vector<error> errors, float result) {
    setlocale(LC_ALL, "RU");
    if (!errors.empty())
    {
        cout << "Errors: ";
        for (size_t i = 0; i < errors.size(); i++)
        {
            cout << "'" << errors[i].message << "'";
            if (i < errors.size() - 1)
                cout << ", ";
        }
           
        cout << endl;
        return;
    }
    cout << "Answer: " << result << endl;
}

TEST_F(TestFixture, Should_return_error_when_empty_collection)
{
    TestCase tc = GetTestCaseByTitle("Should_return_error_when_empty_collection", cases);

    tuple<vector<float>, float, vector<error>> result = getProductOfMultiples(tc.InputCollection, tc.Multiple);

    vector<float> resultCollection = get<0>(result);
    float resultMult = get<1>(result);
    vector<error> resultErrors = get<2>(result);

    bool checkErrors = CheckErrors(tc.ExpectedErrors, resultErrors);
    
    EXPECT_EQ(checkErrors, true);
    
    EXPECT_EQ(resultMult, tc.ExpectedResult);

    bool checkArray = CheckArray(tc.ExpectedCollection, resultCollection);
    EXPECT_EQ(checkArray, true);

    PrintInfo(resultErrors, resultMult);
}

TEST_F(TestFixture, Should_return_error_when_big_collection)
{
    TestCase tc = GetTestCaseByTitle("Should_return_error_when_big_collection", cases);

    tuple<vector<float>, float, vector<error>> result = getProductOfMultiples(tc.InputCollection, tc.Multiple);

    vector<float> resultCollection = get<0>(result);
    float resultMult = get<1>(result);
    vector<error> resultErrors = get<2>(result);

    bool checkErrors = CheckErrors(tc.ExpectedErrors, resultErrors);

    EXPECT_EQ(checkErrors, true);

    EXPECT_EQ(resultMult, tc.ExpectedResult);

    bool checkArray = CheckArray(tc.ExpectedCollection, resultCollection);
    EXPECT_EQ(checkArray, true);

    PrintInfo(resultErrors, resultMult);
}


TEST_F(TestFixture, Should_return_success_when_one_element) 
{
    TestCase tc = GetTestCaseByTitle("Should_return_success_when_one_element", cases);
    tuple<vector<float>, float, vector<error>> result = getProductOfMultiples(tc.InputCollection, tc.Multiple);
    vector<float> resultCollection = get<0>(result);
    float resultMult = get<1>(result);
    vector<error> resultErrors = get<2>(result);

    bool checkErrors = CheckErrors(tc.ExpectedErrors, resultErrors);

    EXPECT_EQ(checkErrors, true);

    EXPECT_EQ(resultMult, tc.ExpectedResult);

    bool checkArray = CheckArray(tc.ExpectedCollection, resultCollection);
    EXPECT_EQ(checkArray, true);
    PrintInfo(resultErrors, resultMult);
}

TEST_F(TestFixture, Should_return_error_when_multiple_is_zero)
{
    TestCase tc = GetTestCaseByTitle("Should_return_error_when_multiple_is_zero", cases);
    
    tuple<vector<float>, float, vector<error>> result = getProductOfMultiples(tc.InputCollection, tc.Multiple);

    vector<float> resultCollection = get<0>(result);
    float resultMult = get<1>(result);
    vector<error> resultErrors = get<2>(result);

    bool checkErrors = CheckErrors(tc.ExpectedErrors, resultErrors);

    EXPECT_EQ(checkErrors, true);

    EXPECT_EQ(resultMult, tc.ExpectedResult);

    bool checkArray = CheckArray(tc.ExpectedCollection, resultCollection);
    EXPECT_EQ(checkArray, true);
    PrintInfo(resultErrors, resultMult);
}

TEST_F(TestFixture, Should_return_error_when_multiple_is_negative)
{
    TestCase tc = GetTestCaseByTitle("Should_return_error_when_multiple_is_zero", cases);
    tuple<vector<float>, float, vector<error>> result = getProductOfMultiples(tc.InputCollection, tc.Multiple);

    vector<float> resultCollection = get<0>(result);
    float resultMult = get<1>(result);
    vector<error> resultErrors = get<2>(result);

    bool checkErrors = CheckErrors(tc.ExpectedErrors, resultErrors);

    EXPECT_EQ(checkErrors, true);

    EXPECT_EQ(resultMult, tc.ExpectedResult);

    bool checkArray = CheckArray(tc.ExpectedCollection, resultCollection);
    EXPECT_EQ(checkArray, true);
    PrintInfo(resultErrors, resultMult);
}

TEST_F(TestFixture, Should_return_errors_when_multiple_is_zero_and_empty_collection)
{
    TestCase tc = GetTestCaseByTitle("Should_return_errors_when_multiple_is_zero_and_empty_collection", cases);
    tuple<vector<float>, float, vector<error>> result = getProductOfMultiples(tc.InputCollection, tc.Multiple);
            
    vector<float> resultCollection = get<0>(result);
    float resultMult = get<1>(result);
    vector<error> resultErrors = get<2>(result);

    bool checkErrors = CheckErrors(tc.ExpectedErrors, resultErrors);

    EXPECT_EQ(checkErrors, true);

    EXPECT_EQ(resultMult, tc.ExpectedResult);

    bool checkArray = CheckArray(tc.ExpectedCollection, resultCollection);
    EXPECT_EQ(checkArray, true);
    PrintInfo(resultErrors, resultMult);
}

TEST_F(TestFixture, Should_return_errors_when_multiple_is_zero_and_big_collection)
{
    TestCase tc = GetTestCaseByTitle("Should_return_errors_when_multiple_is_zero_and_big_collection", cases);
    tuple<vector<float>, float, vector<error>> result = getProductOfMultiples(tc.InputCollection, tc.Multiple);

    vector<float> resultCollection = get<0>(result);
    float resultMult = get<1>(result);
    vector<error> resultErrors = get<2>(result);

    bool checkErrors = CheckErrors(tc.ExpectedErrors, resultErrors);

    EXPECT_EQ(checkErrors, true);

    EXPECT_EQ(resultMult, tc.ExpectedResult);

    bool checkArray = CheckArray(tc.ExpectedCollection, resultCollection);
    EXPECT_EQ(checkArray, true);
    PrintInfo(resultErrors, resultMult);
}

TEST_F(TestFixture, Should_return_correct_answer_when_collection_contains_max_float)
{
    TestCase tc = GetTestCaseByTitle("Should_return_correct_answer_when_collection_contains_max_float", cases);
    tuple<vector<float>, float, vector<error>> result = getProductOfMultiples(tc.InputCollection, tc.Multiple);

    vector<float> resultCollection = get<0>(result);
    float resultMult = get<1>(result);
    vector<error> resultErrors = get<2>(result);

    bool checkErrors = CheckErrors(tc.ExpectedErrors, resultErrors);

    EXPECT_EQ(checkErrors, true);

    EXPECT_EQ(resultMult, tc.ExpectedResult);

    bool checkArray = CheckArray(tc.ExpectedCollection, resultCollection);
    EXPECT_EQ(checkArray, true);
    PrintInfo(resultErrors, resultMult);
}

TEST_F(TestFixture, Should_return_correct_answer_when_collection_contains_min_float)
{
    TestCase tc = GetTestCaseByTitle("Should_return_correct_answer_when_collection_contains_min_float", cases);
    tuple<vector<float>, float, vector<error>> result = getProductOfMultiples(tc.InputCollection, tc.Multiple);

    vector<float> resultCollection = get<0>(result);
    float resultMult = get<1>(result);
    vector<error> resultErrors = get<2>(result);

    bool checkErrors = CheckErrors(tc.ExpectedErrors, resultErrors);

    EXPECT_EQ(checkErrors, true);

    EXPECT_EQ(resultMult, tc.ExpectedResult);

    bool checkArray = CheckArray(tc.ExpectedCollection, resultCollection);
    EXPECT_EQ(checkArray, true);
    PrintInfo(resultErrors, resultMult);
}

TEST_F(TestFixture, Should_return_error_when_too_big_numbers_in_collection)
{
    TestCase tc = GetTestCaseByTitle("Should_return_error_when_too_big_numbers_in_collection", cases);
    tuple<vector<float>, float, vector<error>> result = getProductOfMultiples(tc.InputCollection, tc.Multiple);

    vector<float> resultCollection = get<0>(result);
    float resultMult = get<1>(result);
    vector<error> resultErrors = get<2>(result);

    bool checkErrors = CheckErrors(tc.ExpectedErrors, resultErrors);

    EXPECT_EQ(checkErrors, true);

    bool checkArray = CheckArray(tc.ExpectedCollection, resultCollection);
    EXPECT_EQ(checkArray, true);
    PrintInfo(resultErrors, resultMult);
}

TEST_F(TestFixture, Should_return_correct_result_when_1024_elements_in_collection)
{
    TestCase tc = GetTestCaseByTitle("Should_return_correct_result_when_1024_elements_in_collection", cases);
    tuple<vector<float>, float, vector<error>> result = getProductOfMultiples(tc.InputCollection, tc.Multiple);

    vector<float> resultCollection = get<0>(result);
    float resultMult = get<1>(result);
    vector<error> resultErrors = get<2>(result);

    bool checkErrors = CheckErrors(tc.ExpectedErrors, resultErrors);

    EXPECT_EQ(checkErrors, true);

    bool checkArray = CheckArray(tc.ExpectedCollection, resultCollection);
    EXPECT_EQ(checkArray, true);
    PrintInfo(resultErrors, resultMult);
}

TEST_F(TestFixture, Should_return_correct_answer_when_collection_contains_negative_numbers)
{
    TestCase tc = GetTestCaseByTitle("Should_return_correct_answer_when_collection_contains_negative_numbers", cases);
    tuple<vector<float>, float, vector<error>> result = getProductOfMultiples(tc.InputCollection, tc.Multiple);

    vector<float> resultCollection = get<0>(result);
    float resultMult = get<1>(result);
    vector<error> resultErrors = get<2>(result);

    bool checkErrors = CheckErrors(tc.ExpectedErrors, resultErrors);

    EXPECT_EQ(checkErrors, true);

    bool checkArray = CheckArray(tc.ExpectedCollection, resultCollection);
    EXPECT_EQ(checkArray, true);
    PrintInfo(resultErrors, resultMult);
}


TEST_F(TestFixture, Should_return_first_number_when_multiple_greater_than_arr_size)
{
    TestCase tc = GetTestCaseByTitle("Should_return_first_number_when_multiple_greater_than_arr_size", cases);
    tuple<vector<float>, float, vector<error>> result = getProductOfMultiples(tc.InputCollection, tc.Multiple);

    vector<float> resultCollection = get<0>(result);
    float resultMult = get<1>(result);
    vector<error> resultErrors = get<2>(result);

    bool checkErrors = CheckErrors(tc.ExpectedErrors, resultErrors);

    EXPECT_EQ(checkErrors, true);

    bool checkArray = CheckArray(tc.ExpectedCollection, resultCollection);
    EXPECT_EQ(checkArray, true);
    PrintInfo(resultErrors, resultMult);
}


TEST_F(TestFixture, Should_return_error_when_multiple_is_min_int)
{
    TestCase tc = GetTestCaseByTitle("Should_return_error_when_multiple_is_min_int", cases);
    tuple<vector<float>, float, vector<error>> result = getProductOfMultiples(tc.InputCollection, tc.Multiple);

    vector<float> resultCollection = get<0>(result);
    float resultMult = get<1>(result);
    vector<error> resultErrors = get<2>(result);

    bool checkErrors = CheckErrors(tc.ExpectedErrors, resultErrors);

    EXPECT_EQ(checkErrors, true);

    bool checkArray = CheckArray(tc.ExpectedCollection, resultCollection);
    EXPECT_EQ(checkArray, true);
    PrintInfo(resultErrors, resultMult);
}

TEST_F(TestFixture, Should_return_first_number_when_multiple_is_max_int)
{
    TestCase tc = GetTestCaseByTitle("Should_return_first_number_when_multiple_is_max_int", cases);
    tuple<vector<float>, float, vector<error>> result = getProductOfMultiples(tc.InputCollection, tc.Multiple);

    vector<float> resultCollection = get<0>(result);
    float resultMult = get<1>(result);
    vector<error> resultErrors = get<2>(result);

    bool checkErrors = CheckErrors(tc.ExpectedErrors, resultErrors);

    EXPECT_EQ(checkErrors, true);

    bool checkArray = CheckArray(tc.ExpectedCollection, resultCollection);
    EXPECT_EQ(checkArray, true);
    PrintInfo(resultErrors, resultMult);
}

TEST_F(TestFixture, Should_return_full_collection_when_multiple_is_one)
{
    TestCase tc = GetTestCaseByTitle("Should_return_full_collection_when_multiple_is_one", cases);
    tuple<vector<float>, float, vector<error>> result = getProductOfMultiples(tc.InputCollection, tc.Multiple);

    vector<float> resultCollection = get<0>(result);
    float resultMult = get<1>(result);
    vector<error> resultErrors = get<2>(result);

    bool checkErrors = CheckErrors(tc.ExpectedErrors, resultErrors);

    EXPECT_EQ(checkErrors, true);

    bool checkArray = CheckArray(tc.ExpectedCollection, resultCollection);
    EXPECT_EQ(checkArray, true);
}