#ifndef _BVH_
#define _BVH_

#include "../core/ray.h"
#include "../core/primitive.h"
#include "./aggregate.h"

using namespace std;

inline int random_int(int min, int max);
inline bool box_compare(const shared_ptr<Primitive> a, const shared_ptr<Primitive> b, int axis);
bool box_x_compare (const shared_ptr<Primitive> a, const shared_ptr<Primitive> b);
bool box_y_compare (const shared_ptr<Primitive> a, const shared_ptr<Primitive> b);
bool box_z_compare (const shared_ptr<Primitive> a, const shared_ptr<Primitive> b);

class BVHNode : public Primitive {
    public:
        shared_ptr<Primitive> left;
        shared_ptr<Primitive> right;
        Bounds3 box;

        BVHNode();

        BVHNode(vector<shared_ptr<Primitive>> objects, size_t start, size_t end) {
            int axis = random_int(0,2);
            auto comparator = (axis == 0) ? box_x_compare
                            : (axis == 1) ? box_y_compare
                                        : box_z_compare;

            size_t object_span = end - start;

            if (object_span == 1) {
                left = right = objects[start];
            } else if (object_span == 2) {
                if (comparator(objects[start], objects[start+1])) {
                    left = objects[start];
                    right = objects[start+1];
                } else {
                    left = objects[start+1];
                    right = objects[start];
                }
            } else {
                std::sort(objects.begin() + start, objects.begin() + end, comparator);

                auto mid = start + object_span/2;
                left = make_shared<BVHNode>(objects, start, mid);
                right = make_shared<BVHNode>(objects, mid, end);
            }

            box = boundsUnion(left->bounds(), right->bounds());
        }

        bool intersect( const Ray& r, Surfel *sf ) const override {
            if (!box.intersect_p(r))
                return false;

            bool hit_left = left->intersect(r, sf);
            bool hit_right = right->intersect(r, sf);

            return hit_left || hit_right;
        }

		bool intersect_p( const Ray& r ) const override {
            if (!box.intersect_p(r))
                return false;

            bool hit_left = left->intersect_p(r);
            bool hit_right = right->intersect_p(r);

            return hit_left || hit_right;
        }

        Material * getMaterial() const override {
            std::cout << ">>> ERROR: Called getMaterial() on BVH Node\n";
            return nullptr;
        }

        Bounds3 bounds() const override {
            return box;
        }


};

class BVHAccel: public AggregatePrimitive {
    private:
        shared_ptr<BVHNode> root;
    
    public:
        BVHAccel(vector<shared_ptr<Primitive>> prims) : root { make_shared<BVHNode>(prims, 0, prims.size()) }{};

        bool intersect( const Ray& r, Surfel *sf ) const override {
            return root->intersect(r, sf);
        };

		bool intersect_p( const Ray& r ) const override {
            return root->intersect_p(r);
        };

        Bounds3 bounds() const override {
            return root->bounds();
        };
};

inline int random_int(int min, int max) {
    // Returns a random integer in [min,max].
    return rand() % (max + 1) + min;
};

inline bool box_compare(const shared_ptr<Primitive> a, const shared_ptr<Primitive> b, int axis) {
    auto box_a = a->bounds();
    auto box_b = a->bounds();;

    return box_a.pMin[axis] < box_b.pMin[axis];
};

bool box_x_compare (const shared_ptr<Primitive> a, const shared_ptr<Primitive> b) {
    return box_compare(a, b, 0);
};

bool box_y_compare (const shared_ptr<Primitive> a, const shared_ptr<Primitive> b) {
    return box_compare(a, b, 1);
};

bool box_z_compare (const shared_ptr<Primitive> a, const shared_ptr<Primitive> b) {
    return box_compare(a, b, 2);
};

#endif