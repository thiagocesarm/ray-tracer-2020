#ifndef _TRIANGLE_
#define _TRIANGLE_

#include <iostream>
#include <cmath>
#include <vector>
#include "../core/point3D.h"
#include "../core/primitive.h"
#include "../core/shape.h"
#include "../parser/scene_xml_params.h"
#include "../ext/tiny_obj_loader.h"

using namespace std;

/// This struct implements an indexd triangle mesh database.
struct TriangleMesh {
    int n_triangles; //!< # of triangles in the mesh.
    // The size of the three lists below should be 3 * nTriangles. Every 3 values we have a triangle.
    vector< int > vertex_indices;  //!< The list of indices to the vertex list, for each individual triangle.
    vector< int > normal_indices;  //!< The list of indices to the normals list, for each individual triangle.
    vector< int > uvcoord_indices; //!< The list of indices to the UV coord list, for each individual triangle.

    // Here comes the data associated with each vertex. WARNING: The length of the vectors below may differ.
    vector< Vec3 > vertices;  //!< The 3D geometric coordinates
    vector< Vec3 > normals;  //!< The 3D normals.
    vector< Vec3 > uvcoords; //!< The 2D texture coordinates.

    // Regular constructor (almost all data is imported via move semantics).
    TriangleMesh(){/*empty*/};
    /// Copy constructor disabled
    TriangleMesh( const TriangleMesh& ) = delete;
    /// Assign operator disabled.
    TriangleMesh& operator=( const TriangleMesh & ) = delete;
    /// Move constructor.
    TriangleMesh( TriangleMesh && other ) = delete;
};


/// Represents a single triangle.
class Triangle : public Shape {
	private:
		int *v; //!< Pointer to the vertex index array stored in the triangle mesh database. 
		// After the proper triangle initialization, we may access vertices with v[0], v[1], and v[2]
		int *n; //!< Pointer to the normal index array stored in the triangle mesh database.
		// After the proper triangle initialization, we may access normals with n[0], n[1], and n[2]
		int *uv;//!< Pointer to the UV coord index array stored in the triangle mesh database.
		// After the proper triangle initialization, we may access UV coords with uv[0], uv[1], and uv[2]

		shared_ptr<TriangleMesh> mesh; //!< This is the **indexed triangle mesh database** this triangle is linked to.
		bool backface_cull;            //!< Set it `true` to activate backface culling.
	
	public:
        // The single constructor, that receives the mesh, this triangle id, and an indication for backface culling.
		Triangle( shared_ptr<TriangleMesh> mesh, int tri_id, bool bfc=true )
			: Shape(), mesh{mesh}, backface_cull{bfc}
		{
			// This is just a shortcut to access this triangle's data stored in the mesh database.
			v  = &mesh->vertex_indices[ 3 * tri_id ];
			n  = &mesh->normal_indices[ 3 * tri_id ];
			uv = &mesh->uvcoord_indices[ 3 * tri_id ];
		}
		/// Return the triangle's bounding box.
		// Bounds3f object_bound() const;
        /// The regular intersection methods, as defined in the Shape parent class.
		bool intersect(Ray &ray, float *thit, Surfel *isect ) const { 
            const float EPSILON = 0.0000001;
            Vec3 vertex0 = mesh->vertices[v[0]];
            Vec3 vertex1 = mesh->vertices[v[1]];  
            Vec3 vertex2 = mesh->vertices[v[2]];
            Vec3 edge1, edge2, h, s, q;
            float a,f,u,v;
            edge1 = vertex1 - vertex0;
            edge2 = vertex2 - vertex0;
            h = cross(ray.getDirection(), edge2);
            a = dot(edge1, h);
            if (a > -EPSILON && a < EPSILON)
                return false;    // This ray is parallel to this triangle.
            f = 1.0/a;
            Vec3 rayOrigin = Vec3 {ray.getOrigin().getX(), ray.getOrigin().getY(), ray.getOrigin().getZ()};
            s = rayOrigin - vertex0;
            u = f * dot(s,h);
            if (u < 0.0 || u > 1.0)
                return false;
            q = cross(s, edge1);
            v = f * dot(ray.getDirection(), q);
            if (v < 0.0 || u + v > 1.0)
                return false;
            // At this stage we can compute t to find out where the intersection point is on the line.
            float t = f * dot(edge2, q);
            if (t > EPSILON) // ray intersection
            {
                Vec3 vecP = rayOrigin + ray.getDirection() * t;
                *thit = t;
                isect->n = cross(edge1, edge2);
                Point3D p = Point3D {vecP.r(), vecP.g(), vecP.b()};
                isect->p = p;
                return true;
            }
            else // This means that there is a line intersection but not a ray intersection.
                return false; 
        }

		bool intersect_p(Ray &ray ) const { return true; }

        Bounds3 bounds() const override { return Bounds3(Point3D{0,0,0}, Point3D{0,0,0}); }

        /// This friend function helps us debug the triangles, if we want to.
        friend std::ostream& operator<<( std::ostream& os, const Triangle & t );
};

/// This is the entry point for the client. This function begins the process of reading a triangle mesh.
vector<shared_ptr<Shape>>
create_triangle_mesh_shape( bool flip_normals, const ParamSet &ps );

/// This is the function that actually creates the mesh database and the triangles, ans store them in a Shape list.
vector<shared_ptr<Shape>> create_triangle_mesh( shared_ptr<TriangleMesh> , bool );

/// Internal function that calls the tinyobjloader api to read the OBJ data into memory.
bool load_mesh_data( const std::string & filename, bool rvo, bool cn, bool fn, shared_ptr<TriangleMesh> md );

/// This function essentially convertes the mesh data from the tinyobjloader internal data structure to our mesh data structure.
void extract_obj_data( const tinyobj::attrib_t& attrib,
                       const std::vector<tinyobj::shape_t>& shapes,
                       bool rvo, bool cn, bool fn, shared_ptr<TriangleMesh> md );

#endif