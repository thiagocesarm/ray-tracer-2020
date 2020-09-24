#include "film.h"
#include "paramset.h"
#include "image_io.h"
#include "api.h"

#include <cmath>

namespace rt3 {

    //=== Film Method Definitions
    Film::Film( const Point2i &resolution,
                const std::string &filename , image_type_e imgt,
                bool gc )
        : m_full_resolution{resolution},
        m_filename{filename},
        m_activate_gamma_correction{ gc },
        image_type{ imgt },
        m_color_buffer_ptr{ nullptr }
    {
        // [0]=== Remove extension of image filename.
        auto pos = filename.rfind('.');
        if( pos != std::string::npos)
        {
            m_filename = filename.substr(0, pos);
        }
        // else, keep `m_filename` as it is.
        
        // [1]=== Allocate memory for 8-bit image.
        auto ncols = resolution[0];
        auto nrows = resolution[1];
        m_color_buffer_ptr = std::make_unique< ColorBuffer >( ncols /* width */, nrows, /* Depth, RGB = */ 3 ) ;
    }

    Film::~Film()
    {
    }

    /// Add the color to image.
    void Film::add_sample( const Point2f &pixel_coord,
            const ColorXYZ &pixel_color )
    {
        // TODO: add color to the proper location.
        m_color_buffer_ptr->set( pixel_coord[0], pixel_coord[1], 0,  pixel_color[0] );
        m_color_buffer_ptr->set( pixel_coord[0], pixel_coord[1], 1,  pixel_color[1] );
        m_color_buffer_ptr->set( pixel_coord[0], pixel_coord[1], 2,  pixel_color[2] );
    }

    /// Convert image to RGB, compute final pixel values, write image.
    void Film::write_image(void) const
    {
        uint8_t *raw8 = m_color_buffer_ptr.get()->raw_data(); // raw pointer for writing.
        auto resolution = m_full_resolution;

        // [4]=== Write image to file.
        bool write_ok{false};
        std::string image_name{ m_filename };
        if ( image_type == image_type_e::PNG )
        {
            image_name += std::string{".png"};
            write_ok = rt3::save_png( raw8, resolution[0], resolution[1], 3, image_name.c_str() );
        }
        else if ( image_type == image_type_e::PPM3 )
        {
            image_name += std::string{".ppm"};
            write_ok = rt3::save_ppm3( raw8, resolution[0], resolution[1], 3, image_name.c_str() );
        }
        else if ( image_type == image_type_e::PPM6 )
        {
            image_name += std::string{".ppm"};
            write_ok = rt3::save_ppm6( raw8, resolution[0], resolution[1], 3, image_name.c_str() );
        }

        // Did it work?
        if ( write_ok )
            RT3_MESSAGE( "\n    Image successfuly written to file \"" + m_filename + "\".\n" );
        else
            RT3_MESSAGE( "\n    Failed while attempting to open image file \'" + m_filename + "\' for writing.\n" );
    }
    


    Film * create_film( const ParamSet &ps )
    {
        std::cout << ">>> Inside create_film()\n";
        std::string filename;
        // Let us check whether user has provided an output file name via
        // command line arguments in main().
        if ( API::curr_run_opt.outfile != "")
        {
            // Retrieve filename.
            filename = API::curr_run_opt.outfile;
            // Try to get parameters' output file name.
            // Aux function that retrieves info from the ParamSet.
            std::string filename_from_file = retrieve( ps, "filename", std::string{""} );
            if ( filename_from_file != "") // We also get a filename from scene file...
                RT3_WARNING( string{"Output filename supplied on command line, \""} +
                         API::curr_run_opt.outfile +
                         string{"\" is overriding filename provided in scene description file, \""} +
                         filename_from_file );
        }
        else
        {
            // Try yo retrieve filename from scene file.
            filename = retrieve( ps, "filename", std::string{"image.png"} );
        }

        // Read resolution.
        // Aux function that retrieves info from the ParamSet.
        int xres = retrieve( ps, "x_res", int(1280) );
        // Aux function that retrieves info from the ParamSet.
        int yres = retrieve( ps, "y_res", int(720) );
        // Quick render?
        if ( API::curr_run_opt.quick_render == true)
        {
            // decrease resolution.
            xres = std::max(1, xres / 4);
            yres = std::max(1, yres / 4);
        }

        // Read crop window information.
        // TODO

        // Get output file type.
        Film::image_type_e fit{ Film::image_type_e::PNG };
        // Aux function that retrieves info from the ParamSet.
        string fit_str = retrieve( ps, "img_type", string{"png"} );
        if ( fit_str == "ppm3" )
            fit = Film::image_type_e::PPM3;
        else if ( fit_str == "ppm6" or fit_str == "ppm" )
            fit = Film::image_type_e::PPM6;
        else if ( fit_str == "png" )
            fit = Film::image_type_e::PNG;
        else
            RT3_WARNING( string{"Unrecognized image type \""} + fit_str +
                     string{"\"received. Assuming PNG."} );

        // Get gamma correction request.
        string gc_str = retrieve( ps, "gamma_corrected", string{"false"} );
        bool gamma_corrected = ( gc_str == "true" or gc_str == "on" or gc_str == "yes" ) ? true : false ;

        return new Film( Point2i{ xres, yres}, filename, fit, gamma_corrected );
    }
}  // namespace pbrt
