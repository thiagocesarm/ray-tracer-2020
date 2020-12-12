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

        void Union(const Point3D &p) {
            pMin = Point3D(std::min(p.getX(), pMin.getX()),
                           std::min(p.getY(), pMin.getY()),
                           std::min(p.getZ(), pMin.getZ()));
            pMax = Point3D(std::max(p.getX(), pMax.getX()),
                           std::max(p.getY(), pMax.getY()),
                           std::max(p.getZ(), pMax.getZ()));
        };

        inline Vec3 diagonal() const { auto p = pMax - pMin; return Vec3(p.getX(), p.getY(), p.getZ()); }

        inline bool intersect_p(const Ray& r) const {
            float t_min = r.min_t, t_max = r.max_t;
            
            for (int a = 0; a < 3; a++) {
                auto invD = 1.0f / r.getDirection()[a];
                auto t0 = (pMin[a] - r.getOrigin()[a]) * invD;
                auto t1 = (pMax[a] - r.getOrigin()[a]) * invD;
                if (invD < 0.0f)
                    std::swap(t0, t1);
                t_min = t0 > t_min ? t0 : t_min;
                t_max = t1 < t_max ? t1 : t_max;
                if (t_max < t_min)
                    return false;
            }
            return true;
        }
};


Bounds3 boundsUnion(const Bounds3 &b1, const Bounds3 &b2) {
    auto pMin = Point3D(std::min(b1.pMin.getX(), b2.pMin.getX()),
                    std::min(b1.pMin.getY(), b2.pMin.getY()),
                    std::min(b1.pMin.getZ(), b2.pMin.getZ()));
    auto pMax = Point3D(std::max(b1.pMax.getX(), b2.pMax.getX()),
                    std::max(b1.pMax.getY(), b2.pMax.getY()),
                    std::max(b1.pMax.getZ(), b2.pMax.getZ()));
    return Bounds3(pMin, pMax);
};

#endif