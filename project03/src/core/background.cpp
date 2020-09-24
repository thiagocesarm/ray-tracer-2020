#include "background.h"

namespace rt3 {

    Spectrum BackgroundColor::lerp( const Spectrum &S, const Spectrum &E, float t ) const
    {
        // // Color in float, so we can interpolate.
        // Spectrum sf{ S }; // Start
        // Spectrum ef{ E }; // End
        // // the interpolation
        // Spectrum r = (1.f-t) * sf + t * ef;
        // // Make sure we have a regular color.
        // r.x = Clamp( r.x, 0.f, 1.f );
        // r.y = Clamp( r.y, 0.f, 1.f );
        // r.z = Clamp( r.z, 0.f, 1.f );
        // return r;
        
        // TODO: replace this with your code
        return S;
    }

    /*!
     * Samples a color base on spherical interpolation of an image ou colored background.
     *
     * @param pixel_ndc Pixel position in NDC space,  in \f$[0:1]\f$.
     * \return The interpolated color.
     */
    Spectrum Background::sampleXYZ( const Point2f &pixel_ndc ) const
    {
        // TODO
        return Spectrum{0,0,0};
    }

    Spectrum Background::sampleXYZ( const Ray &ray ) const
    {
        // TODO
        return Spectrum{0,0,0};
    }

    void BackgroundTexture::decode_png(const char* filename )
    {
        //decode
        unsigned error = lodepng::decode(image, width, height, filename );

        //if there's an error, display it
        if( error )
        {
            std::ostringstream oss;
            oss << error;
            RT3_ERROR ( std::string{ "Trying to open \"" } + std::string(filename) +
                        std::string{ "\", decoder error " }+ oss.str() +
                        std::string{ ": " } + lodepng_error_text(error) );
        }
        //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
    }

    BackgroundColor * create_color_background( const ParamSet &ps )
    {
        // List of name ids for each corner of the background.
        // NOTE: I'm flipping colors vertically here, because it's easier.
        // I do that by changing the order of the names in the array below.
        // Compare this order with the `Corners_e` order to understand.
        std::string corner_name[]{ "tl", "bl", "br" , "tr" };
        // List of color from the scene to be passed onto the constructor.
        std::vector< ColorXYZ > color_list;

        // [1]=== Retrieve mapping type.
        std::string mapping_str = retrieve( ps, "mapping", std::string{"screen"} );
        Background::mapping_t mapping_chosen{ Background::mapping_t::screen };
        if ( mapping_str == "screen" )
            mapping_chosen = Background::mapping_t::screen;
        else if ( mapping_str == "spherical" )
            mapping_chosen = Background::mapping_t::spherical;
        else
            RT3_WARNING ("create_color_background(): Unknown type of background mapping specified \""
                    + mapping_str + "\", assuming screen mapping." );

        // [2]=== Try to see if there is a single-color attribute present.
        if ( ps.count("color") != 0 )
        {
            // Recall that we always store composite elements as vectors.
            ColorXYZ single_color = retrieve( ps, "color", ColorXYZ{} );
            // Insert it 4 times, because the constructor always
            // assumes that 4 colors are provided in the scene.
            for ( auto i{0} ; i < 4 ; ++i )
                color_list.push_back( single_color );
        }
        // [3]=== Try to get the 4 individual colors, as corners.
        else
        {
            // Try to get up to 4 corners, if they have been specified.
            for ( auto i{0} ; i < 4 ; ++i )
            {
                // Recall that we always store composite elements as vectors.
                ColorXYZ color_value = retrieve( ps, corner_name[i], /* default --> */ ColorXYZ{0,0,0} );
                // Check whether we got RBG values in range [0,255]
                // if ( color_value.r  > 1.f or color_value.g > 1.f or color_value.b > 1.f )
                if ( color_value[0] > 1.f or color_value[1] > 1.f or color_value[2] > 1.f )
                {
                    color_value[0] /= 255.f; // Normalize colors specified in [0,255] values.
                    color_value[1] /= 255.f;
                    color_value[2] /= 255.f;
                }
                // Store color.
                color_list.push_back( color_value );
            }

        }
        // // In case the background has no color in it.
        // if ( color_list.empty() )
        // {
            // RT3_WARNING ("create_color_background(): No colors were provided; building a light grey background. " );
            // color_list.push_back( Spectrum{ 0.3, 0.3, 0.3 } );
        // }
        //

       return new BackgroundColor( color_list, mapping_chosen );
    }

    BackgroundTexture * create_texture_background( const ParamSet &ps )
    {
        // Retrieve mapping type.
        std::string mapping_str = retrieve( ps, "mapping", std::string("screen") );
        Background::mapping_t mapping_chosen{ Background::mapping_t::screen };
        if ( mapping_str == "screen" )
            mapping_chosen = Background::mapping_t::screen;
        else if ( mapping_str == "spherical" )
            mapping_chosen = Background::mapping_t::spherical;
        else
            RT3_WARNING ("create_texture_background(): Unknown type of background mapping specified \""
                    + mapping_str + "\", assuming screen mapping." );

        std::string filename = retrieve( ps, "filename", std::string("unknow") );
        if ( filename == "unknown" )
            RT3_ERROR("create_texture_background(): Requested a textured background, yet no filename was provided.");

        return new BackgroundTexture( filename.c_str(), mapping_chosen );
    }
}
