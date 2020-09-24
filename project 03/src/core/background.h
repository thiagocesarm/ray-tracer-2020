#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "rt3.h"
#include "rt3-base.h"

namespace rt3 {
    // TODO: Create a virtual class Background and derive BackgroundColor, BackgroundSphereImage, BackgroundSkyBoxImage.
    // UPDATE: Partially done. We have spherical environment mapping
    /*!
     * A background is basically a rectangle, have a color associated to each corner.
     * A background might be sampled based on a normalized coordinate in \f$[0,1]^2.\f$.
     * We generate samples with bilinear interpolation of the corner colors.
     * We consider the corners in a circular clockwise order, starting at the lower-left corner.
     *
     * Alternatively, a background might be a regular image.
     */
    class Background
    {
        public:
            /// Types of color mapping scheme
            enum class mapping_t {
                screen=0,  //!< background is assigned to the image screen
                spherical  //!< background is assigne to a sphere surrounding the scene.
            };


        public:
            mapping_t mapping_type; //!< sampling type we use to pick a color.

            /// Ctro receiving a single color for the entire background.
            Background( mapping_t mt=mapping_t::spherical ): mapping_type{mt} {/* empty */}

            virtual ~Background(){ /* empty */ };
            Spectrum sampleXYZ( const Ray & ) const;
            Spectrum sampleXYZ( const Point2f &pixel_ndc ) const;
    };

    class BackgroundColor : public Background
    {
        private:
            /// Each corner has a color associated with.
            Spectrum corners[4]={{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
            /// Corner indices.
            enum Corners_e {
                bl=0, //!< Bottom left corner.
                tl,   //!< Top left corner.
                tr,   //!< Top right corner.
                br    //!< Bottom right corner.
            };

            /// Return the linearly interpolated color in [A;B], based on the parameter \f$0\leq t \leq 1.\f$
            Spectrum lerp( const Spectrum &A, const Spectrum &B, float t ) const;

        public:

            /// Ctro receives a list of four colors, for each corner.
            BackgroundColor( const std::vector< Spectrum >& colors, mapping_t mt=mapping_t::spherical ) : Background{ mt }
            {
                // Copy colors to corners.
                auto ct{0};
                // It's precondition to have 4 colors.
                for ( const auto & c : colors )
                    corners[ct++] = c; // copy to the internal storage.
            }

            virtual ~BackgroundColor() { };
    };

    class BackgroundTexture : public Background
    {
        private:
            /// Raw pixels of an image, 4 channels per pixel RGBA
            std::vector<unsigned char> image; //the raw pixels
            /// Dimensions of the image.
            unsigned width, height;

        private:
            // TODO: Background should no read an image. Rather, it
            // should as to a manager class (that stores images) to
            // do that and return a pointer to the image data.
            /// External function to load a PNG image as the background.
            void decode_png( const char* );

        public:
            /// Ctro based on an image.
            BackgroundTexture( const char * filename, mapping_t mt=mapping_t::spherical ) : Background{ mt }
            {
                decode_png(filename);
            }

            virtual ~BackgroundTexture() {};
    };

    // factory pattern functions.
    BackgroundColor * create_color_background( const ParamSet &ps );
    BackgroundTexture * create_texture_background( const ParamSet &ps );
}
#endif
