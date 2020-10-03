#ifndef _PARAMSETITEM_
#define _PARAMSETITEM_

#include <memory>

using namespace std;

class GenericParamSetItem {
    public:
        GenericParamSetItem() {}
        virtual ~GenericParamSetItem() {};
};

template<typename T>
class ParamSetItem : public GenericParamSetItem {
    public:
        const unique_ptr<T[]> values;
        const size_t size;
        ParamSetItem(unique_ptr<T[]> mValues, size_t mSize) : values(move(mValues)), size(mSize) {};
        virtual ~ParamSetItem(){};
};

#endif