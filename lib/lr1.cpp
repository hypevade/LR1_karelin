#include <string>
#include <vector>
#include <tuple>

using namespace std;

class error {
public:
    string message;
    int code;

    error(string msg, int cod) : message(msg), code(cod) {}
};

tuple<vector<float>, float, vector<error>> getProductOfMultiples(const vector<float>& arr, int multiple) {
    
    vector<float> products;
    vector<error> errors;
    float total = 1;

    if (multiple <= 0)
        errors.emplace_back("Заданное число должно быть больше нуля.", 1);

    if (arr.empty())
        errors.emplace_back("Переданная коллекция не должна быть пустой.", 2);

    if (arr.size() > 1024)
        errors.emplace_back("В переданной коллекции должно быть меньше 1024 элементов.", 3);

    if (!errors.empty())
        return make_tuple(products, total, errors);

    for (size_t i = 0; i < arr.size(); i += multiple) {
        products.push_back(arr[i]);
        total *= arr[i];
        if (isinf(total))
        {
            errors.emplace_back("Произошло переполнение при умножении.", 4);
            break;
        }
    }

    return make_tuple(products, total, errors);
}