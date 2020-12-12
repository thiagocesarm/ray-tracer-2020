#ifndef _TRIANGLE_
#define _TRIANGLE_

#include <iostream>
#include <cmath>
#include <vector>
#include "../ext/tiny_obj_loader.h"
#include "../core/primitive.h"
#include "../core/shape.h"
#include "../parser/scene_xml_params.h"
#include "../parser/paramset.h"
#include "../core/point3D.h"

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
		Triangle( shared_ptr<TriangleMesh> mesh, int tri_id, bool bfc = true )
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
		bool intersect(const Ray& ray, float * thit, Surfel * isect ) const override {
            const float EPSILON = 0.01;
            Vec3 vertex0 = mesh->vertices[v[0]];
            Vec3 vertex1 = mesh->vertices[v[1]];
            Vec3 vertex2 = mesh->vertices[v[2]];
            Vec3 edge1, edge2, h, s, q;
            float a,f,t,u,v;
            edge1 = vertex1 - vertex0;
            edge2 = vertex2 - vertex0;
            h = cross(edge2, ray.getDirection());
            a = dot(edge1, h);
            Vec3 rayOrigin = Vec3 {ray.getOrigin().getX(), ray.getOrigin().getY(), ray.getOrigin().getZ()};

            if (backface_cull) {
                if (a < EPSILON) { return false; }
                auto tVec = rayOrigin - vertex0;
                u = dot(tVec, h);
                if (u < 0.0 || u > a) { return false; }
                auto qVec = cross(edge1, tVec);
                v = dot(ray.getDirection(), qVec);
                if (v < 0.0 || u + v > a) { return false; }

                t = dot(edge2, qVec);
                auto invDet = 1.0 / a;
                t *= invDet;
                u *= invDet;
                v *= invDet;
            } else {
                if (a > -EPSILON && a < EPSILON)
                    return false;    // This ray is parallel to this triangle.
                f = 1.0/a;
                s = rayOrigin - vertex0;
                u = f * dot(s,h);
                if (u < 0.0 || u > 1.0)
                    return false;
                q = cross(edge1, s);
                v = f * dot(ray.getDirection(), q);
                if (v < 0.0 || u + v > 1.0)
                    return false;
                // At this stage we can compute t to find out where the intersection point is on the line.
                t = f * dot(edge2, q);
            }
            if (t > EPSILON && ray.min_t < t && t < ray.max_t) // ray intersection
            {
                *thit = t;
                auto normal_v0 = (1 - u - v) * mesh->normals[n[0]];
                auto normal_v1 = u * mesh->normals[n[1]];
                auto normal_v2 = v * mesh->normals[n[2]];
                isect->n = normal_v0 + normal_v1 + normal_v2;
                isect->p = ray(t);
                return true;
            }
            else // This means that there is a line intersection but not a ray intersection.
                return false;
        }

		bool intersect_p( const Ray& ray ) const override { 
            const float EPSILON = 0.01;
            Vec3 vertex0 = mesh->vertices[v[0]];
            Vec3 vertex1 = mesh->vertices[v[1]];
            Vec3 vertex2 = mesh->vertices[v[2]];
            Vec3 edge1, edge2, h, s, q;
            float a,f,t,u,v;
            edge1 = vertex1 - vertex0;
            edge2 = vertex2 - vertex0;
            h = cross(edge2, ray.getDirection());
            a = dot(edge1, h);
            Vec3 rayOrigin = Vec3 {ray.getOrigin().getX(), ray.getOrigin().getY(), ray.getOrigin().getZ()};

            if (backface_cull) {
                if (a < EPSILON) { return false; }
                auto tVec = rayOrigin - vertex0;
                u = dot(tVec, h);
                if (u < 0.0 || u > a) { return false; }
                auto qVec = cross(edge1, tVec);
                v = dot(ray.getDirection(), qVec);
                if (v < 0.0 || u + v > a) { return false; }

                t = dot(edge2, qVec);
                auto invDet = 1.0 / a;
                t *= invDet;
                u *= invDet;
                v *= invDet;
            } else {
                if (a > -EPSILON && a < EPSILON)
                    return false;    // This ray is parallel to this triangle.
                f = 1.0/a;
                s = rayOrigin - vertex0;
                u = f * dot(s,h);
                if (u < 0.0 || u > 1.0)
                    return false;
                q = cross(edge1, s);
                v = f * dot(ray.getDirection(), q);
                if (v < 0.0 || u + v > 1.0)
                    return false;
                // At this stage we can compute t to find out where the intersection point is on the line.
                t = f * dot(edge2, q);
            }
            return (t > EPSILON && ray.min_t < t && t < ray.max_t);
        }

        Bounds3 bounds() const override { 
            auto point_v0 = Point3D(mesh->vertices[v[0]].x(), mesh->vertices[v[0]].y(), mesh->vertices[v[0]].z());
            auto point_v1 = Point3D(mesh->vertices[v[1]].x(), mesh->vertices[v[1]].y(), mesh->vertices[v[1]].z());
            auto point_v2 = Point3D(mesh->vertices[v[2]].x(), mesh->vertices[v[2]].y(), mesh->vertices[v[2]].z());

            auto bounds = Bounds3(point_v0, point_v1);
            bounds.Union(point_v2);
            return bounds;
        }

        /// This friend function helps us debug the triangles, if we want to.
        friend std::ostream& operator<<( std::ostream& os, const Triangle & t );
};

/// This function creates the internal data structure, required by the RT3.
vector<shared_ptr<Shape>>
create_triangle_mesh( shared_ptr<TriangleMesh> mesh, bool backface_cull )
{
	// List of shapes (triangles) we need to return to the client.
	vector<shared_ptr<Shape>> tris;
	// Create the triangles, which are just references to the mesh database.
	for ( int i = 0 ; i < mesh->n_triangles ; ++i )
		tris.push_back(std::make_shared<Triangle>( mesh, i, backface_cull ) );

	return tris;
}

/// This is the function that converts from the tinyobjloader's internal storage to our mesh data organization.
void extract_obj_data( const tinyobj::attrib_t& attrib,
                       const std::vector<tinyobj::shape_t>& shapes,
                       bool rvo, bool cn, bool fn, /* OUT */ shared_ptr<TriangleMesh> md )
{
    std::cout << "-- SUMMARY of the OBJ file --\n";
    std::cout << "# of vertices  : " << (attrib.vertices.size()  / 3) << std::endl;
    std::cout << "# of normals   : " << (attrib.normals.size()   / 3) << std::endl;
    std::cout << "# of texcoords : " << (attrib.texcoords.size() / 2) << std::endl;
    std::cout << "# of shapes    : " << shapes.size()                 << std::endl;
    std::cout << "-----------------------------\n";

    // Retrieve the complete list of vertices.
    auto n_vertices{ attrib.vertices.size()/3 };
    for ( auto idx_v{0u} ; idx_v < n_vertices; idx_v++)
    {
        cout << "   v[" << static_cast<long>(idx_v) << "] = ( "
             << static_cast<double>(attrib.vertices[3 * idx_v + 0]) << ", "
             << static_cast<double>(attrib.vertices[3 * idx_v + 1]) << ", "
             << static_cast<double>(attrib.vertices[3 * idx_v + 2]) << " )\n";

        // Store the vertex in the mesh data structure.
        md->vertices.push_back( Vec3{ attrib.vertices[ 3 * idx_v + 0 ],
                                        attrib.vertices[ 3 * idx_v + 1 ],
                                        attrib.vertices[ 3 * idx_v + 2 ] } );
    }


    // Read the normals
    // TODO: flip normals if requested.
    float flip = ( fn ) ? -1 : 1 ;
    auto n_normals{ attrib.normals.size()/3 };

    // Do we need to compute the normals? Yes only if the user requeste or there are no normals in the file.
    // if ( cn == true or n_normals == 0)
    // {
    //    // TODO: COmpute normals here.
    //    // compute_normals();
    // }
    //else {// Read normals from file. This corresponds to the entire 'for' below.

    // Traverse the normals read from the OBJ file.
    for ( auto idx_n{0u} ; idx_n < n_normals; idx_n++)
    {
        cout << "   n[" << static_cast<long>(idx_n) << "] = ( "
             << static_cast<double>(attrib.normals[3 * idx_n + 0]) << ", "
             << static_cast<double>(attrib.normals[3 * idx_n + 1]) << ", "
             << static_cast<double>(attrib.normals[3 * idx_n + 2]) << " )\n";

        // Store the normal.
        md->normals.push_back( Vec3 { attrib.normals[ 3 * idx_n + 0 ] * flip,
                                        attrib.normals[ 3 * idx_n + 1 ] * flip,
                                        attrib.normals[ 3 * idx_n + 2 ] * flip } );
    }

    // Read the complete list of texture coordinates.
    auto n_texcoords{ attrib.texcoords.size()/2 };
    for ( auto idx_tc{0u} ; idx_tc < n_texcoords; idx_tc++)
    {
        cout << "   t[" << static_cast<long>(idx_tc) << "] = ( "
             << static_cast<double>(attrib.texcoords[2 * idx_tc + 0]) << ", "
             << static_cast<double>(attrib.texcoords[2 * idx_tc + 1]) << " )\n";

        // Store the texture coords.
        md->uvcoords.push_back( Vec3{ attrib.texcoords[ 2 * idx_tc + 0 ],
                                         attrib.texcoords[ 2 * idx_tc + 1 ], 0 } );
    }

    // Read mesh connectivity and store it as lists of indices to the real data.
    auto n_shapes{ shapes.size() };
    md->n_triangles = 0; // We must reset this here.
    // In case the OBJ file has the triangles organized in several shapes or groups, we
    // ignore this and store all triangles as a single mesh dataset.
    // This is why we need to reset the triangle count here.
    for ( auto idx_s{0u} ; idx_s < n_shapes; idx_s++)
    {
        cout << "The shape[" << idx_s << "].name = " << shapes[idx_s].name << '\n';
        cout << "Size of shape["<< idx_s << "].mesh.indices: "
             << static_cast<unsigned long>(shapes[idx_s].mesh.indices.size()) << '\n';
        cout << "shape["<< idx_s << "].num_faces: "
            <<  static_cast<unsigned long>(shapes[idx_s].mesh.num_face_vertices.size()) << '\n';

        // For each face print out the indices lists.
        size_t index_offset = 0;
        // # of triangles for this "shape" (group).
        // NOTE that we are accumulate the number of triangles coming from the shapes present in the OBJ file.
        md->n_triangles += shapes[idx_s].mesh.num_face_vertices.size();
        for ( auto idx_f{0} ; idx_f < md->n_triangles; idx_f++)
        {
            // Number of vertices per face (always 3, in our case)
            size_t fnum = shapes[idx_s].mesh.num_face_vertices[idx_f];

            cout << "  face[" << idx_f << "].fnum = "  << static_cast<unsigned long>(fnum) << '\n';

            // TODO: Invert order of vertices if flag is on. (DONE!)
            if ( rvo == true ) {
                std::cout << "Reverse order\n";
                // For each vertex in the face print the corresponding indices
                for (int v = fnum-1; v >= 0 ; v--)
                {
                    tinyobj::index_t idx = shapes[idx_s].mesh.indices[index_offset + v];
                    cout << "    face[" << idx_f << "].v[" << v << "].indices = "
                        << idx.vertex_index << "/" << idx.normal_index << "/" << idx.texcoord_index << '\n';
                    // Add the indices to the global list of indices we need to pass on to the mesh object.
                    md->vertex_indices.push_back( idx.vertex_index );
                    md->normal_indices.push_back( idx.normal_index );
                    md->uvcoord_indices.push_back( idx.texcoord_index );
                }
            }
            else { // Keep the original vertex order
                // For each vertex in the face get the corresponding indices
                for (size_t v = 0; v < fnum; v++)
                {
                    tinyobj::index_t idx = shapes[idx_s].mesh.indices[index_offset + v];
                    cout << "    face[" << idx_f << "].v[" << v << "].indices = "
                        << idx.vertex_index << "/" << idx.normal_index << "/" << idx.texcoord_index << '\n';
                    // Add the indices to the global list of indices we need to pass on to the mesh object.
                    // This goes to the mesh data structure.
                    md->vertex_indices.push_back( idx.vertex_index );
                    md->normal_indices.push_back( idx.normal_index );
                    md->uvcoord_indices.push_back( idx.texcoord_index );
                }
            }

            // Advance over to the next triangle.
            index_offset += fnum;
        }
    }

    cout << "This is the list of indices: \n";

    cout << "   + Vertices [ ";
    std::copy( md->vertex_indices.begin(), md->vertex_indices.end(), std::ostream_iterator< int > ( std::cout, " " ) );
    cout << "]\n";

    cout << "   + Normals [ ";
    std::copy( md->normal_indices.begin(), md->normal_indices.end(), std::ostream_iterator< int > ( std::cout, " " ) );
    cout << "]\n";

    cout << "   + UV coords [ ";
    std::copy( md->uvcoord_indices.begin(), md->uvcoord_indices.end(), std::ostream_iterator< int > ( std::cout, " " ) );
    cout << "]\n";
}

/// This function calls the basic tinyobjloader loading function and stores all the data into the tinyobjloader's internal data structures.
bool load_mesh_data( const std::string & filename, bool rvo, bool cn, bool fn, shared_ptr<TriangleMesh> md )
{
    // Default load parameters
    const char* basepath = NULL;
    bool triangulate = true;

    std::cout << "Loading " << filename << std::endl;

    // This is the tinyobj internal data structures.
    tinyobj::attrib_t attrib; // Hold all the data, such as vertex, normals, UV coords
    std::vector<tinyobj::shape_t> shapes; // Represents a collection of faces, grouped in a unit.
    std::vector<tinyobj::material_t> materials; // Materials, NOT USED HERE.

    // Warnings and Error values.
    std::string warn;
    std::string err;

    // Timing loading.
    //================================================================================
    auto start = std::chrono::steady_clock::now();
    //================================================================================
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename.c_str(),
            basepath, triangulate);
    //================================================================================
    std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
    //Store the time difference between start and end
    std::chrono::duration<double> diff = end - start;

    // Milliseconds (10^-3)
    std::cout << "\t\t>>> " << std::chrono::duration <double, std::milli> (diff).count()
        << " ms" << std::endl;

    // Nanoseconds (10^-9)
    std::cout << "\t\t>>> " << std::chrono::duration <double, std::nano> (diff).count()
        << " ns" << std::endl;

    // Seconds
    auto diff_sec = std::chrono::duration_cast<std::chrono::seconds>(diff);
    std::cout << "\t\t>>> " << diff_sec.count() << " s" << std::endl;
    //================================================================================

    if (!warn.empty()) {
        cout << "WARN: " << warn << std::endl;
    }

    if (!err.empty()) {
       cerr << "ERR: " << err << std::endl;
    }

    if (!ret) {
        cout << "Failed to load/parse .obj.\n";
        return false;
    }

    // Let us now "convert" or "migrate" the data from tinyobjloader data structure into out mesh data.
    extract_obj_data( attrib, shapes, // TinyObjeLoader data structures (IN)
                      rvo, cn, fn,    // Mesh modifiers (IN)
                      md );           // Reference to the mesh data to fill in. (OUT)

    return true;
}

// This is the function called by the API to create a triangle mesh shape.
/* 
 * This is the entry-point function for the client code.
 * This function decodes the `ParamSet` data and, based on that, it either
 * (1) creates a triangle mesh manually (from the XML attributes), or
 * (2) calls another function to load an OBJ file and create the triangle mesh.
 *
 * @param flip_normals This flag asks to invert the normal of all triangles. This is a global flag, set by a API command.
 * @param ps The ParamSet object sent from the client code with all the information related to the triangle mesh read from the scene file.
 *
 * @return The list of Shape (triangles) that we read from the scene file.
 */
vector< shared_ptr<Shape> >
create_triangle_mesh_shape( bool flip_normals, ParamSet &ps )
{
    bool bkfc_on{false};                 // Controls whether the backface cull should be done or not.
    bool reverse_vertex_order{false};   // If this is true, we store vertices in reverse order inside the mesh.
    bool compute_normals{false};        // Indicate whether we need to calculate the triangle's normals manually.

    // This is a collection of data structures passed between function calls.
    // This structure may be filled in with information from a OBJ file
    // or from the XML attributes extracted from the scene file itself.
	shared_ptr<TriangleMesh> mesh = std::make_shared<TriangleMesh>(); // Default Ctro.

    // Retrieve filename.
    string filename = ps.find<string>(TriangleParams::FILENAME, ""); // Retrieving data associated with 'filename' attrib.
    // Retrieve backface ON/OFF
    string bkf_on_str = ps.find<string>(TriangleParams::BACKFACE_CULL, "");
    if ( bkf_on_str == "on" or bkf_on_str == "true" )
        bkfc_on = true;
    // Retrieve Reverse vertex order ON/OFF
    string rvo_str = ps.find<string>(TriangleParams::REVERSE_VERTEX_ORDER, "");
    if ( rvo_str == "on" or rvo_str == "true" )
        reverse_vertex_order = true;
    // Retrieve compute normals flag
    string cn_str = ps.find<string>(TriangleParams::COMPUTE_NORMALS, "");
    if ( cn_str == "on" or cn_str == "true" )
        compute_normals = true;

    // Here we have only two option: read mehs data from OBJ file or from the ParamSet.
    if ( filename != "" ) { // Read mesh data from an OBJ file provided in the scene file.
        // Call our auxiliary function that interfaces with tinyobjloader API.
        if ( load_mesh_data( filename, reverse_vertex_order, compute_normals, flip_normals, mesh ) )
            std::cout << ">>> Mesh data successfuly loaded!\n";
        else
            std::cout << ">>> Mesh data loading failed!\n";
    }
    else { // This means we must read the mesh data from the scene file, not from the OBJ file.

        // TODO: retrieve the attributes of the triangle mesh present in the XML scene file.
        // 
        // Here you must retrieve from the ParamSet all the data that might appear in a trianglemesh object.
        // Usually these are the vertices, normals, and indices.
        // 
        // You should read all the data into the `tri_mesh_data` object so that the function call below works,
        // regardless if the data came from the OBJ file or was read directly from the scene file.

        auto num_triangles = ps.find<int>(TriangleParams::NTRIANGLES, 0);
        auto num_vertices = ps.find<int>(TriangleParams::NUM_VERTICES, 0);
        auto indices = ps.findArray<int>(TriangleParams::INDICES);
        auto vertices = ps.findArray<float>(TriangleParams::VERTICES);
        auto normals = ps.findArray<float>(TriangleParams::NORMALS);
        auto uv = ps.findArray<float>(TriangleParams::UV);

        for (size_t i = 0; i < num_triangles; i++) {
            mesh->vertex_indices.push_back(indices[i*3]);
            mesh->vertex_indices.push_back(indices[i*3 + 1]);
            mesh->vertex_indices.push_back(indices[i*3 + 2]);

            mesh->normal_indices.push_back(indices[i*3]);
            mesh->normal_indices.push_back(indices[i*3 + 1]);
            mesh->normal_indices.push_back(indices[i*3 + 2]);

            if (uv != nullptr) {
                mesh->uvcoord_indices.push_back(indices[i*3]);
                mesh->uvcoord_indices.push_back(indices[i*3 + 1]);
                mesh->uvcoord_indices.push_back(indices[i*3 + 2]);
            }
        }

        std::vector<Vec3> vecVertices;
        std::vector<Vec3> vecNormals;
        std::vector<Vec3> vecUv;
        for (size_t i = 0; i < num_vertices; i++) {
            vecVertices.push_back(Vec3{vertices[i*3], vertices[i*3 + 1], vertices[i*3 + 2]});
            vecNormals.push_back(Vec3{normals[i*3], normals[i*3 + 1], normals[i*3 + 2]});
            if (uv != nullptr) { vecUv.push_back(Vec3{uv[i*2], uv[i*2 + 1], 0}); } // UV only has 2 values
        }

        mesh->n_triangles = num_triangles;
        mesh->vertices = vecVertices;
        mesh->normals = vecNormals;
        mesh->uvcoords = vecUv;
    }

    // At this point, the tri_mesh_data object has already been filled in with data coming either from a OBJ file or from the scene file.
    return create_triangle_mesh( mesh, bkfc_on ); // Note the use of move semantics here.
}

std::ostream& operator<<( std::ostream& os, const Triangle & t )
{
    constexpr short X{0};
    constexpr short Y{1};
    constexpr short Z{2};

    os  << "    + V0: ("
        << t.mesh->vertices[ t.v[0] ][X] << ", "
        << t.mesh->vertices[ t.v[0] ][Y] << ", "
        << t.mesh->vertices[ t.v[0] ][Z] << ")\n"
        << "    + V1: ("
        << t.mesh->vertices[ t.v[1] ][X] << ", "
        << t.mesh->vertices[ t.v[1] ][Y] << ", "
        << t.mesh->vertices[ t.v[1] ][Z] << ")\n"
        << "    + V2: ("
        << t.mesh->vertices[ t.v[2] ][X] << ", "
        << t.mesh->vertices[ t.v[2] ][Y] << ", "
        << t.mesh->vertices[ t.v[2] ][Z] << ")\n"

        << "    + N0: ("
        << t.mesh->normals[ t.n[0] ][X] << ", "
        << t.mesh->normals[ t.n[0] ][Y] << ", "
        << t.mesh->normals[ t.n[0] ][Z] << ")\n"
        << "    + N1: ("
        << t.mesh->normals[ t.n[1] ][X] << ", "
        << t.mesh->normals[ t.n[1] ][Y] << ", "
        << t.mesh->normals[ t.n[1] ][Z] << ")\n"
        << "    + N2: ("
        << t.mesh->normals[ t.n[2] ][X] << ", "
        << t.mesh->normals[ t.n[2] ][Y] << ", "
        << t.mesh->normals[ t.n[2] ][Z] << ")\n"

        << "    + UV0: ("
        << t.mesh->uvcoords[ t.uv[0] ][X] << ", "
        << t.mesh->uvcoords[ t.uv[0] ][Y] << ")\n"
        << "    + UV1: ("
        << t.mesh->uvcoords[ t.uv[1] ][X] << ", "
        << t.mesh->uvcoords[ t.uv[1] ][Y] << ")\n"
        << "    + UV2: ("
        << t.mesh->uvcoords[ t.uv[2] ][X] << ", "
        << t.mesh->uvcoords[ t.uv[2] ][Y] << ")\n";

    return os;
}

#endif