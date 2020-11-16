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
        }
        Bounds3(const Point3D &p1, const Point3D &p2)
            : pMin(std::min(p1.getX(), p2.getX()), std::min(p1.getY(), p2.getY()),
                std::min(p1.getZ(), p2.getZ())),
            pMax(std::max(p1.getX(), p2.getX()), std::max(p1.getY(), p2.getY()),
                std::max(p1.getZ(), p2.getZ())) {
        }
        inline Bounds3 Union(const Bounds3 &b, const Point3D &p) {
            return Bounds3(Point3D(std::min(b.pMin.getX(), p.getX()),
                                  std::min(b.pMin.getY(), p.getY()),
                                  std::min(b.pMin.getZ(), p.getZ())),
                            Point3D(std::max(b.pMax.getX(), p.getX()),
                                   std::max(b.pMax.getY(), p.getY()),
                                   std::max(b.pMax.getZ(), p.getZ())));
        }
        inline Bounds3 Union(const Bounds3 &b1, const Bounds3 &b2) {
            return Bounds3(Point3D(std::min(b1.pMin.getX(), b2.pMin.getX()),
                                   std::min(b1.pMin.getY(), b2.pMin.getY()),
                                   std::min(b1.pMin.getZ(), b2.pMin.getZ())),
                            Point3D(std::max(b1.pMax.getX(), b2.pMax.getX()),
                                    std::max(b1.pMax.getY(), b2.pMax.getY()),
                                    std::max(b1.pMax.getZ(), b2.pMax.getZ())));
        }
        inline Bounds3 Intersect(const Bounds3 &b1, const Bounds3 &b2) {
            return Bounds3(Point3D(std::max(b1.pMin.getX(), b2.pMin.getX()),
                                   std::max(b1.pMin.getY(), b2.pMin.getY()),
                                   std::max(b1.pMin.getZ(), b2.pMin.getZ())),
                            Point3D(std::min(b1.pMax.getX(), b2.pMax.getX()),
                                    std::min(b1.pMax.getY(), b2.pMax.getY()),
                                    std::min(b1.pMax.getZ(), b2.pMax.getZ())));
        }
        inline Vec3 diagonal() const { auto p = pMax - pMin; return Vec3(p.getX(), p.getY(), p.getZ()); }
};

#endif