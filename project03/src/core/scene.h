#ifndef SCENE_H
#define SCENE_H

#include "rt3.h"
#include "rt3-base.h"

namespace rt3 {
/*!
 * \brief This class represents a RT3 scene.
 * A scene has an aggregate, a set of (local) lights, and a background.
 */
class Scene {
    public:
        /// Scene constructor.
        Scene( std::unique_ptr< Background > background )
            : background(std::move(background))
        {
        }

        /// Background object.
        std::unique_ptr< Background > background;

    private:
};
}  // namespace pbrt

#endif  // PBRT_CORE_SCENE_H
