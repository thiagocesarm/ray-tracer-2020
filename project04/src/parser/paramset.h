#ifndef _PARAMSET_
#define _PARAMSET_

#include <unordered_map>
#include <memory>
#include <string>
#include "../parser/paramsetitem.h"

using namespace std;

class ParamSet {
    public:
        ParamSet();
        template <typename T> void add(const string &key, unique_ptr<T[]> value, size_t size);
        template <typename T> const T& find(const string &key, const T& defaultVaue);
        template <typename T> const T* findArray(const string &key);
    private:
        unordered_map<string, shared_ptr<GenericParamSetItem>> params;
};

ParamSet::ParamSet() {
    params = unordered_map< string, shared_ptr<GenericParamSetItem>>();
}

template <typename T> 
void ParamSet::add(const string &key, unique_ptr<T[]> value, size_t size) {
    if (value == nullptr) { return; }
    shared_ptr<ParamSetItem<T>> item(new ParamSetItem<T>(move(value), size));
    params[key] = item;
}

template <typename T>
const T& ParamSet::find(const string &key, const T& defaultValue) {
    auto result = params.find(key);
    if (result == params.end()) {
        return defaultValue;
    } else {
        auto genericParamSetItemPtr = result->second.get();
        auto paramSetItemPtr = dynamic_cast<ParamSetItem<T>*>(genericParamSetItemPtr);
        return paramSetItemPtr->values[0];
    }
}

template <typename T> 
const T* ParamSet::findArray(const string &key) {
    auto result = params.find(key);
    if (result == params.end()) {
        return nullptr;
    } else {
        auto genericParamSetItemPtr = result->second.get();
        auto paramSetItemPtr = dynamic_cast<ParamSetItem<T>*>(genericParamSetItemPtr);
        return paramSetItemPtr->values.get();
    }
}

#endif