#include <string>
#include <vector>
#include <tuple>
#include <cmath>
#include <iostream>

using namespace std;

class error {
public:
    string message;
    int code;

    error(string msg, int cod) : message(msg), code(cod) {}
};

tuple<vector<float>, float, vector<error>> getProductOfMultiples(const vector<float>& arr, int multiple) {
   
    setlocale(LC_ALL, "RU");
    vector<float> products;
    vector<error> errors;
    float total = 1;

    if (multiple <= 0)
        errors.emplace_back("The specified number must be greater than zero.", 1);
   

    if (arr.empty())
        errors.emplace_back("The passed collection must not be empty.", 2);

    if (arr.size() > 1024)
        errors.emplace_back("The passed collection must contain fewer than 1024 elements.", 3);

    if (!errors.empty())
        return make_tuple(products, total, errors);

    for (size_t i = 0; i < arr.size(); i += multiple) {
        products.push_back(arr[i]);
        total *= arr[i];
        if (isinf(total))
        {
            errors.emplace_back("An overflow occurred during multiplication.", 4);
            break;
        }
    }
    

    return make_tuple(products, total, errors);
}