#ifndef _BOUNDS3_
#define _BOUNDS3_

#include <limits>
#include <algorithm>
#include "./point3D.h"
#include "./vec3.h"

class Bounds3 {
    public:
        Point3D pMin, pMax;
        Bounds3() {
            float minNum = std::numeric_limits<float>::lowest();
            float maxNum = std::numeric_limits<float>::max();
            pMin = Point3D(maxNum, maxNum, maxNum);
            pMax = Point3D(minNum, minNum, minNum);
        };
        Bounds3(const Point3D &p1, const Point3D &p2)
            : pMin(std::min(p1.getX(), p2.getX()), std::min(p1.getY(), p2.getY()),
                std::min(p1.getZ(), p2.getZ())),
            pMax(std::max(p1.getX(), p2.getX()), std::max(p1.getY(), p2.getY()),
                std::max(p1.getZ(), p2.getZ())) {
        };
        void Union(const Bounds3 &b) {
            pMin = Point3D(std::min(b.pMin.getX(), pMin.getX()),
                           std::min(b.pMin.getY(), pMin.getY()),
                           std::min(b.pMin.getZ(), pMin.getZ()));
            pMax = Point3D(std::max(b.pMax.getX(), pMax.getX()),
                           std::max(b.pMax.getY(), pMax.getY()),
                           std::max(b.pMax.getZ(), pMax.getZ()));
        };
        inline Vec3 diagonal() const { auto p = pMax - pMin; return Vec3(p.getX(), p.getY(), p.getZ()); }
};

#endif