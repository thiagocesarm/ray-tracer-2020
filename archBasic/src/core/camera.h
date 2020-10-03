#ifndef CAMERA_H
#define CAMERA_H

#include "rt3.h"
#include "film.h"
#include "paramset.h"

namespace rt3 {

    /// Implements a positionable camera.
    /*!
     * The camera is specified by three components:
     *  + (1) A _camera frame_ (cf),
     *  + (2) type of projection, and
     *  + (3) a _view plane_ (vp).
     *
     * The **cf** is especified by an origin (viewpoint or eye position \f$e\f$), and
     * an orthonormal basis \f$\{\mathbf{\hat{u}},\mathbf{\hat{v}}, \mathbf{\hat{w}}\}\f$.
     *
     * The **type of projection** (ToP) determines how the rays are shoot from the
     * camera's viewpoint. There are two basic types of projection:
     * _perspective_, and _parallel_.
     * In the perspective projection all the rays have the same origin but different
     * directions.
     * In the parallel projectio all rays have the same direction but different origins.
     *
     * We provide two ways (methods) to define the **vp**, depending on the
     * **ToP** required.
     * Regardeless of the way we define a **vp** (discussed shortly),
     * at the end we end up with the same set of information to describe an **vp**.
     * They are: a point at its left lower corner, and
     * two vectors with the vertical and horizontal dimensions of the **vp**.
     * We've adopted the right handed coordinate system
     * We traverse the screen from lower left hand corner to the
     * higher right hand corner using two offset vectors, \f$\mathbf{s}\f$
     * and \f$\mathbf{t}\f$,
     * along the screen sides to move the ray endpoint across the screen.
     * Note that the **vp** is somehow _attached_ to the camera frame in the
     * sense that if we turn the camera around its \f$\mathbf{\hat{w}}\f$ axis
     * the **vp** follows along that same rotation.
     *
     * Example: a view plane 4 x 2
     *  - origin (0,0,0)
     *  - lowe left corner: (-2,-1,-1)
     *  - horizontal (4,0,0)
     *  - vertical (0,2,0)
     *
     * ```
     *             (-2, 1,-1)                                       (2, 1,-1)
     *   v   ^      +--------------------------------------------------+
     *   e   |      |      s                                           |
     *   r   |      +---------------->* (ray intersection w/ screen)   |
     *   t   |      |                 ^                                |
     *   .   |      |                 |                                |
     *       |      |                 |                                |
     *   a   |      |                 | t                              |
     *   x   |      |                 |                                |
     *   i   |      |                 |                                |
     *   s   |      |                 |                                |
     *       +      *-----------------+--------------------------------+
     * (0,2,0)     (-2,-1,-1)                                       (2,-1,-1)
     *
     *              +-------------------------------------------------->
     *                             horizontal axis (4,0,0)
     * ```
     *
     * If the **ToP** is parallel we need to provide:
     * + the _dimensions_ of the **vp**; and,
     * + a _direction_, \f$\mathbf{d}\f$, for all rays.
     *
     * The dimensions of the **vp** are often specified by the 
     * position of each of the four edges: left, right, bottom, and top.
     * In the example above, they are, respectivelly, -2, +2, -1, +1.
     *
     * The ray direcion is usually perpendicular to the **vp**, so
     * \f$\mathbf{d}=-\mathbf{\hat{w}}\f$,
     * which is called an _orthogonal projection_.
     * If we wish an _oblique parallel_ projection we need to specify the
     * ray direction separately.
     *
     * If we want a perspective projection, we need to define:
     * + an _angle_ for the _vertical field of view_ (vfov);
     * + the _aspect_ ratio between width and height (so we can determine the width of the **vp**);
     * + the _focal length_ that positions the **vp** along the; and,
     * + the _normal_, \f$\mathbf{d}\f$, to the **vp** so we can
     * support _oblique perspective_.
     *
     * For the perspective projection, the **vp** should be specified
     *
     */
     class Camera
     {
         public:
             // === Camera Public Interface

            /// Legacy compatibility constructor version
             Camera( Film *f ) : film{ f }
             { /* empty */ }

             virtual ~Camera()
             {
                 film.release();
             };//= default;
             virtual void generate_ray( real_type ss, real_type tt, Ray& ray) const = 0;
             virtual void generate_ray( size_type x, size_type y, Ray& ray) const = 0;

             // === Camera Public Data

             //--- Film information.
             std::unique_ptr< Film > film; //!< Film or image entity.

             //--- Camera frame information.
             // The camera frame (TODO change this into a matrix transform CameraToWorld).
             Point3f eye{0,0,0};  //!< Camera view point (origin).
             Vector3f u{0,1,0};      //!< Camera's X local coordinate system.
             Vector3f v{1,0,0};      //!< Camera's Y local coordinate system.
             Vector3f w{0,0,1};      //!< Camera's Z local coordinate system.
             Vector3f vpn{0,0,-1};   //!< Normal to the view plane in case we need oblique projection.

             //--- View plane information.
             // The view plane is defined in the camera's coordinate system.
             // By default the view plane's normal is the camera's lookat
             // direction or -m_w.
             // However, it is possible to specify a vp normal different from the
             // lookat direction, to get *oblique projections*.
             Point3f llc{-1,-1,-1}; //!< The vp's lower left corner, i.e. the vp's origin.
             Vector3f vp_horz_axis{1,0,0}; //!< The vp's horizontal axis: defines the widht of the vp.
             Vector3f vp_vert_axis{0,1,0}; //!< The vp's vertical axis: defines the height of the vp.
             real_type l,r,b,t; //!< ortographic box dimensions.

             void build_camera_frame( Point3f lf, Point3f la, Vector3f vup );
     };

}
#endif
//-------------------------------------------------------------------------------
