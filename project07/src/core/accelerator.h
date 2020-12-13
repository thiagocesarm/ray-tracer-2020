#ifndef _ACCELERATOR_
#define _ACCELERATOR_

using namespace std;

enum class accelerator_type_e : int {
	primlist = 1,
	bvh = 2
};

class Accelerator {
    public:
        accelerator_type_e type;
        Accelerator() { type = accelerator_type_e::primlist; }
        Accelerator(accelerator_type_e type) : type {type} {};
};

#endif