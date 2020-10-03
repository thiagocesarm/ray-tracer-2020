#include "api.h"

namespace rt3 {
            
//=== API's static members declaration and initialization.
API::APIState API::curr_state = APIState::Uninitialized;
RunningOptions API::curr_run_opt;
unique_ptr< RenderOptions > API::render_opt;
GraphicsState API::curr_GS;

// THESE FUNCTIONS ARE NEEDED ONLY IN THIS SOURCE FILE (NO HEADER NECESSARY)
// ˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇ


Camera * API::make_camera( const std::string &type,
        const ParamSet &camera_ps,
        const ParamSet &lookat_ps,
        Film *film )
{
    std::cout << ">>> Inside API::make_camera()\n";

    Camera *camera{ nullptr };

    if ( type == "perspective" )
    {
        camera = create_perspective_camera( camera_ps, lookat_ps,  film );
        // Later on, we'll use the call below.
        // camera = create_perspective_camera( ps, film );
    }
    else if ( type == "orthographic")
    {
        camera = create_orthographic_camera( camera_ps, lookat_ps, film );
    }
    else RT3_WARNING( string{"Camera \""} + type + string{"\" unknown."} );

    return camera;
}

Film * API::make_film( const std::string &type, const ParamSet &ps )
{
    std::cout << ">>> Inside API::make_film()\n";
    Film *film{ nullptr };
    if ( type == "image")
        film = create_film( ps );
    else
        RT3_WARNING( string{"Film \""} + type + string{"\" unknown."} );
    return film;
}

Integrator * API::make_integrator( void )
{
    std::shared_ptr<const Camera> camera( setup_camera() );
    if (!camera) {
        RT3_ERROR("API::make_integrator(): Unable to setup camera");
        return nullptr;
    }

    // Create integrator based on the type defined.
    Integrator *integrator = nullptr;
    if ( render_opt->integrator_type == "flat" )
        integrator = create_flat_integrator( render_opt->integrator_ps, camera);
    // else if ( render_opt->integrator_type == "normal_map" )
        // integrator = create_normal_map_integrator( render_opt->integrator_ps, sampler, camera );
    // else if ( render_opt->integrator_type == "depth_map" )
        // integrator = create_depth_map_integrator( render_opt->integrator_ps, sampler, camera );
    // else if ( render_opt->integrator_type == "gcodex" )
        // integrator = create_gcodex_integrator( render_opt->integrator_ps, sampler, camera );
    // else if (IntegratorName == "path")
        // integrator = CreatePathIntegrator(IntegratorParams, sampler, camera);
    // else if (IntegratorName == "volpath")
        // integrator = CreateVolPathIntegrator(IntegratorParams, sampler, camera);
    // else if (IntegratorName == "bdpt") {
        // integrator = CreateBDPTIntegrator(IntegratorParams, sampler, camera);
    // } else if (IntegratorName == "mlt") {
        // integrator = CreateMLTIntegrator(IntegratorParams, camera);
    // } else if (IntegratorName == "ambientocclusion") {
        // integrator = CreateAOIntegrator(IntegratorParams, sampler, camera);
    // } else if (IntegratorName == "sppm") {
        // integrator = CreateSPPMIntegrator(IntegratorParams, camera);
    // }
    else {
        RT3_ERROR( string{"API::make_integrator(): Integrator \""} + render_opt->integrator_type + string{"\" unknown." } );
        return nullptr;
    }

    return integrator;
}
// ˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆ

Camera * API::setup_camera( void )
{
    std::cout << ">>> Inside API::setup_camera()\n";
    Film *film = API::make_film( render_opt->film_type, render_opt->film_ps );
    if ( !film )
    {
        RT3_ERROR( "API::setup_camera(): Unable to create film." );
        return nullptr;
    }
    return API::make_camera( render_opt->camera_type, render_opt->camera_ps, render_opt->lookat_ps, film );
}


Scene * API::make_scene( void )
{
    // [1] Create the scene
    // We instantiate a temporary raw pointer, that will be returned
    // to a unique pointer on the client side.
    //
    // ATTENTION
    // For now, the only parameter the scene needs is the background.
    // Later on, we need to pass in the primitives (objects), and lights
    // to the scene.
    Scene *scene { new Scene{ std::move(render_opt->background) } };

    return scene;
}

// END OF THE AUXILIARY FUNCTIONS
// =========================================================================

//=== API's public methods implementation
void API::init_engine( const RunningOptions & opt )
{
   // Save running option sent from the main().
   curr_run_opt = opt;
   // Check current machine state.
   if ( curr_state != APIState::Uninitialized )
       RT3_ERROR( "API::init_engine() has already been called! ");
   // Set proper machine state
   curr_state = APIState::SetupBlock;
   // Preprare render infrastructure for a new scene.
   render_opt = make_unique< RenderOptions >(); 
   // Create a new initial GS
   curr_GS = GraphicsState();
   RT3_MESSAGE( "[1] Rendering engine initiated.\n" );
}

void API::clean_up( void )
{
    // Check for correct machine state
    if ( curr_state == APIState::Uninitialized )
        RT3_ERROR("API::clean_up() called before engine initialization.");
    else if ( curr_state == APIState::WorldBlock )
        RT3_ERROR("API::clean_up() called inside world definition section.");
    curr_state = APIState::Uninitialized;

    RT3_MESSAGE( "[4] Rendering engine clean up concluded. Shutting down...\n" );
}

void API::run( void )
{
    // Try to load and parse the scene from a file.
    RT3_MESSAGE( "[2] Beginning scene file parsing...\n" );
    // Recall that the file name comes from the running option struct.
    parse( curr_run_opt.filename.c_str() );
}


void API::world_begin( void )
{
    VERIFY_SETUP_BLOCK("API::world_begin");      // check for correct machine state.
    curr_state = APIState::WorldBlock;      // correct machine state.
}

void API::world_end( void )
{
    VERIFY_WORLD_BLOCK("API::world_end");
    // The scene has been properly set up and the scene has
    // already been parsed. It's time to render the scene.

    // [1] Create the integrator.
    unique_ptr< Integrator > the_integrator{ make_integrator() };

    // [2] Create the scene.
    unique_ptr< Scene > the_scene{ make_scene() };

    // [3] Run integrator if previous instantiations went ok
    if ( the_integrator and the_scene )
    {
        RT3_MESSAGE( "    Parsing scene successfuly done!\n" );
        RT3_MESSAGE( "[2] Starting ray tracing progress.\n" );
        auto samp_integrator = the_integrator.get();

        // Get image dimensions info.
        if ( samp_integrator )
        {
            // Structure biding, c++17.
            auto res  = samp_integrator->camera->film->get_resolution();
            size_t w = res[0];
            size_t h = res[1];
            RT3_MESSAGE( "    Image dimensions in pixels (W x H): " + std::to_string(w) + " x " + std::to_string(h) + ".\n" );
            RT3_MESSAGE( "    Ray tracing is usually a slow process, please be patient: \n" );
        }
        //================================================================================
        auto start = std::chrono::steady_clock::now();
        the_integrator->render( *the_scene );
        auto end = std::chrono::steady_clock::now();
        //================================================================================
        auto diff = end - start; //Store the time difference between start and end
        // Seconds
        auto diff_sec = std::chrono::duration_cast<std::chrono::seconds>(diff);
        RT3_MESSAGE( "    Time elapsed: " + std::to_string(diff_sec.count()) + " seconds (" +
                 std::to_string( std::chrono::duration <double, std::milli> (diff).count() ) +  " ms) \n" );
    }
    // [4] Basic clean up
    curr_state = APIState::SetupBlock;      // correct machine state.
    reset_engine();
}



/// This api function is called when we need to re-render the *same* scene (i.e. objects, lights, materials, etc) , maybe with different integrator, and camera setup.
/// Hard reset on the engine. User needs to setup all entities, such as camera, integrator, accelerator, etc.
void API::reset_engine(void)
{
    curr_GS = GraphicsState();
    // This will delete all information on integrator, cameras, filters,
    // acceleration structures, etc., that has been set previously.
    render_opt.reset( new RenderOptions );
}

void API::integrator( const ParamSet &ps )
{
    VERIFY_SETUP_BLOCK("API::integrator");
    // Aux function that retrieves info from the ParamSet.
    string type = retrieve( ps, "type", string{"unknown"} );
    render_opt->integrator_type = type;
    render_opt->integrator_ps = ps;
}

void API::camera( const ParamSet &ps )
{
    VERIFY_SETUP_BLOCK("API::camera");
    // Aux function that retrieves info from the ParamSet.
    string type = retrieve<std::string>( ps, "type", string{"unknown"} );
    render_opt->camera_type= type;
    render_opt->camera_ps = ps;
}

void API::background( const ParamSet& ps )
{
    std::cout << ">>> Inside API::background()\n";
    VERIFY_WORLD_BLOCK("API::background");

    // Assign a default value in case type is not in the ParamSet object.
    std::string type = retrieve( ps, "type", string("unknown") );
    if ( type == "unknown" )
        RT3_ERROR("API::background(): Missing \"type\" specificaton for the background.");

    Background *bkg{ nullptr };
    if ( type == "texture" )
    {
        bkg = create_texture_background( ps );
    }
    else if ( type == "colors" )
    {
        bkg = create_color_background( ps );
    }
    else 
    {
        RT3_WARNING( string{"API::background(): unknown background type \""} + type +
                  string{"\" provided; assuming colored background."} );
        bkg = create_color_background( ps );
    }

    // Store current background object.
    render_opt->background.reset( bkg );
}

void API::film( const ParamSet &ps )
{
    std::cout << ">>> Inside API::film()\n";
    VERIFY_SETUP_BLOCK("API::film");
    // retrieve type from ps.
    string type = retrieve( ps, "type", string{"unknown"} );
    render_opt->film_type = type;
    render_opt->film_ps = ps;
}

void API::look_at( const ParamSet &ps )
{
    VERIFY_INITIALIZED("API:look_at");

    // ATTENTION:
    // For now, just store these information into a separate
    // ParamSet to be passed over to the create_camera() function.
    // Later on, when we introduce geometric transformation into
    // the project, we will extract these values here so we can
    // compose the Look_at transformation into the CTM.
    render_opt->lookat_ps = ps;
}

}  // namespace rt3
