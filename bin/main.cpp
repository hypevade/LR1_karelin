#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>
#include <lib/lr1.h>

using namespace std;


int main() {
    setlocale(LC_ALL, "RU");
    vector<float> arr;
    int multiply;
    float inputNumber;
    string inputLine;

    cout << "������� ����� ��� �������, ����������� �������� (������� 'end' ��� ���������� �����): ";
    while (cin >> inputNumber) {
        arr.push_back(inputNumber);
        if (cin.peek() == '\n') break;
    }

    cin.clear();
    fflush(stdin);

    cout << "������� �������� multiply: ";
    cin >> multiply;

    if (cin.fail()) {
        cout << "������������ ���� ��� multiply. ����������, ������� �����." << endl;
        return 1;
    }

    
    tuple<vector<float>, float, vector<error>> result = getProductOfMultiples(arr, multiply);

    vector<error> errors = get<2>(result);
    if (!errors.empty()) 
    {
        for (const auto& err : errors) 
            cout << "Error: " << err.message << " Code: " << err.code << endl;
        
        return 0;
    }
    vector<float> resultCollection = get<0>(result);
    float resultM = get<1>(result);

    cout << "������������ ���������: ";

    for (size_t i = 0; i < resultCollection.size(); i++) 
        cout << resultCollection[i] << "; ";
    
    cout << endl;

    cout << "����������� ������������: " << resultM << endl;


    return 0;
}