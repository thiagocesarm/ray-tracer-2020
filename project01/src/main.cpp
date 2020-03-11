#include "tinyxml2.h"
#include <iostream>
#include <memory>
#include "paramset.h"

using namespace tinyxml2;
using namespace std;

int main() {
    ParamSet paramSet = ParamSet();
    std::unique_ptr<int[]> value{ new int[1] };
    value[0] = 10;
    value[1] = 20;
    value[2] = 30;
    paramSet.add("teste", move(value), 1);
    auto resultOne = paramSet.find<int>("teste", 0);
    cout << resultOne << "\n";
    auto resultArray = paramSet.findArray<int>("teste");
    cout << resultArray[0] << " " << resultArray[1] << " " << resultArray[2] << "\n";
    return 0;
}