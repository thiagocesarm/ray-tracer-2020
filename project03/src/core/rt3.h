#ifndef RT3_H
#define RT3_H 1
#include <cassert>


#include <iostream>
#include <cmath>
#include <cstdlib>
#include <memory>
using std::unique_ptr;
using std::shared_ptr;
#include <vector>
using std::vector;
#include <stack>
using std::stack;
#include <map>
using std::map;
#include <unordered_map>
using std::unordered_map;
#include <string>
using std::string;
#include <algorithm>
using std::min;
using std::max;
using std::swap;
using std::sort;
#include <utility>
using std::pair;
using std::make_pair;
#include <tuple>
using std::tuple;
#include <array>
using std::array;

//== Alias to the chosen data structure to implement a dictionary.
//#define Dictionary std::unordered_map
#define Dictionary std::map


//=== Aliases
namespace rt3 {
    /// ATENTION: This is just to compile the project. You need to implement Point3f!!!!
    // Alias to a Point3f (simulation)
    using Point3f = std::array< float, 3>;
    // Temporary Vec3, just to compile. TODO: Implement a real one!!!
    using Vector3f = std::array< float, 3>;
    using ColorXYZ = std::array< float, 3>;
    using Spectrum = std::array< float, 3>;
    using Normal3f = std::array< float, 3>;
    using Ray      = std::array< float, 3>;


    // List of points
    using ListPoint3f = std::vector< Point3f >;


    // Temporary Vec3i. TODO: code a real one.
    using Vector3i = std::array< int, 3>;
    using Point3i  = std::array< int, 3>;
    using Point2i  = std::array< int, 2>;
    using Point2f  = std::array< float, 2>;

    template <typename T, size_t S>
    std::ostream& operator<<( std::ostream& os , const std::array<T,S>& v )
    {
        os << "[ ";
        for ( const auto &e: v )
            os << e << " ";
        os << "]";
        return os;
    }

    // Global Forward Declarations
    class Camera;
    class OrthographicCamera;
    class PerspectiveCamera;
    class Film;
    class Scene;
    class Background;
    class BackgroundColor;
    class BackgroundTexture;
    class Integrator;
    class FlatIntegrator;
    // class Integrator;

    //=== aliases
    typedef float real_type;
    typedef size_t size_type;
    typedef std::tuple< bool, std::string> result_type;

    /// This struct holds information provided via command line arguments
    struct RunningOptions {
        RunningOptions() : filename{""}, outfile{""}, quick_render{false}
        {
            crop_window[0][0] = 0; //!< x0
            crop_window[0][1] = 1; //!< x1,
            crop_window[1][0] = 0; //!< y0
            crop_window[1][1] = 1; //!< y1
        }
        // [row=0] -> X; [row=1] -> Y
        // x0, x1, y0, y1
        real_type crop_window[2][2]; //!< Crop window to render. 1 = 100% of the full resolition.
        std::string filename; //!< input scene file name.
        std::string outfile;  //!< output image file name.
        bool quick_render;    //!< when set, render image with 1/4 of the requested resolition.
    };

    /// Lambda expression that returns a lowercase version of the input string.
    auto CSTR_LOWERCASE = [](const char * t)->std::string
    {
        std::string str{ t };
        std::transform( str.begin(), str.end(), str.begin(), ::tolower );
        return str;
    };
    /// Lambda expression that returns a lowercase version of the input string.
    auto STR_LOWERCASE = [](const string& t)->std::string
    {
        std::string str{ t };
        std::transform( str.begin(), str.end(), str.begin(), ::tolower );
        return str;
    };

    //=== Global Inline Functions

    /*! Linear interpolation.
     * \param t The parameter, in [0,1].
     * \param v1 The initial interpolation value.
     * \param v2 The final interpolation value.
     * \return The interpolated value.
     */
    //
    inline float Lerp(float t, float v1, float v2) {
        return (1.f - t) * v1 + t * v2;
    }


    /// Clamp T to [low,high].
    template <typename T, typename U, typename V>
        inline T Clamp(T val, U low, V high) {
            if (val < low)       return low;
            else if (val > high) return high;
            else                 return val;
        }

    /// Degrees to radians.
    inline float Radians(float deg) {
        return ((float)M_PI/180.f) * deg;
    }


    /// Radians to degreees.
    inline float Degrees(float rad) {
        return (180.f/(float)M_PI) * rad;
    }
}

#endif // RT3_H
