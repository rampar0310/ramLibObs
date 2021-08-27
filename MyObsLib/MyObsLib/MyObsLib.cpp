//
//  MyObsLib.cpp
//  MyObsLib
//
//  Created by Sivaraman, Ram on 8/25/21.
//

#include <iostream>
#include "MyObsLib.hpp"
#include "MyObsLibPriv.hpp"
#include <iostream>
#include "../../obs-studio/libobs/obs.h"
#include <obs-module.h>
#include "my_source.h"
#include "my_output.h"
#include "my_service.h"
#include "my_encoder.h"


OBS_DECLARE_MODULE();
using namespace std;

struct obs_video_info video_info = {
    /**
           * Graphics module to use (usually "libobs-opengl" or "libobs-d3d11")
           */
          .graphics_module = "libobs-opengl",

          .fps_num = 30,       /**< Output FPS numerator */
          .fps_den = 1,       /**< Output FPS denominator */

          .base_width = 800,    /**< Base compositing width */
          .base_height = 600,   /**< Base compositing height */

          .output_width = 800,  /**< Output width */
          .output_height = 600, /**< Output height */
          .output_format = VIDEO_FORMAT_YVYU, /**< Output format */

          /** Video adapter index to use (NOTE: avoid for optimus laptops) */
          .adapter  =0,

          /** Use shaders to convert to different color formats */
          .gpu_conversion = true,

          .colorspace = VIDEO_CS_DEFAULT,  /**< YUV type (if YUV) */
         .range= VIDEO_RANGE_FULL ,       /**< YUV range (if YUV) */

          .scale_type= OBS_SCALE_DISABLE    /**< How to scale if scaling */
};
struct obs_audio_info audio_info = {
        .samples_per_sec = 30,
        .speakers = SPEAKERS_STEREO
};

    
    //Declare various modules
    obs_module_t* source_module;
    obs_module_t* encoder_module;
    obs_module_t* output_module;
    obs_module_t* service_module;
    obs_data_t* defaults;
    obs_encoder_t* my_h264_encoder;
    obs_encoder_t* my_aac_encoder;
    size_t mixer_idx = 0;
    obs_service_t* my_service;
    obs_output_t* my_output;
    obs_source_t* my_source;
    void *rtmp_custom_data = NULL; //this data needs to be populated. not sure how the data would look like
    obs_data_t *video_settings=NULL;//this obs_data needs to be populated. not sure how the data would look like
    obs_data_t *audio_settings=NULL;//this obs_data needs to be populated. not sure how the data would look like
    string json_string_with_settings_for_twitch = {"My twitch username, pwd and key in JSON format"};
    
bool obs_module_load(void)
    {
            obs_register_source(&my_source_info);
            obs_register_output(&rtmp_output_info);
            obs_register_encoder(&obs_x264_encoder);
            obs_register_service(&rtmp_custom_service);
            return true;
    }
    

    bool StartUpOBS() {
        
     //Load various module
        obs_module_load();
        obs_startup("en_US", NULL, NULL);
        obs_reset_video(&video_info);
        obs_reset_audio(&audio_info);
        
        
        auto ret1 = obs_open_module(&source_module, "/Users/rsivaram/logitech/obs-studio/build/soFiles/image-source.so", NULL);
        if(ret1 != MODULE_SUCCESS){
            cout << "Error loading source" << ret1 <<endl;
            return false;
        }
            
            
        auto ret2 = obs_open_module(&encoder_module, "/Users/rsivaram/logitech/obs-studio/build/soFiles/obs-x264.so.so", NULL);
        if(ret2 != MODULE_SUCCESS){
            cout << "Error loading encoder" << ret1 <<endl;
            return false;
        }
            
        auto ret3 = obs_open_module(&output_module, "/Users/rsivaram/logitech/obs-studio/build/soFiles/obs-outputs.so", NULL);
        if(ret3 != MODULE_SUCCESS){
            cout << "Error loading output" << ret1 <<endl;
            return false;
        }
            
        auto ret4 = obs_open_module(&service_module, "/Users/rsivaram/logitech/obs-studio/build/soFiles/rtmp-services.so", NULL);
        if(ret4 != MODULE_SUCCESS){
            cout << "Error loading rmtp service" << ret1 <<endl;
            return false;
        }
        /* Initialize various modules*/
        if(!obs_init_module(source_module))
            return false;
        if(!obs_init_module(encoder_module))
            return false;
        if(!obs_init_module(output_module))
            return false;
        if(!obs_init_module(service_module))
            return false;
        /* Notifies modules that all modules have been loaded.*/
        obs_post_load_modules();
        
        
        
        /* create source */
        my_source = obs_source_create("my_source", "OBS_SOURCE_TYPE_INPUT", NULL, NULL);
        
        /* create audio, video encoders */
        my_h264_encoder = obs_video_encoder_create("obs_x264" , "OBS_ENCODER_VIDEO", NULL, NULL);
        if(!my_h264_encoder)
        {
            cout << "Failed to create video encoder!!" << endl;
            return false;
        }
        
        my_aac_encoder = obs_audio_encoder_create("obs_audio" , "OBS_ENCODER_AUDIO", NULL, mixer_idx, NULL);
        if(my_aac_encoder != NULL) {
            cout << "Failed to create audio encoder!!" << endl;
            return false;
        }
        /* Set default settings for output */
        
        set_rtmp_stream_defaults(defaults);
        
        
        /* Create rtmp output*/
        rtmp_output_info.create(defaults, my_output);
        
        
        
        
        /* Setting the audio and video encoders */
        obs_encoder_set_video(my_h264_encoder, obs_get_video());
        obs_encoder_set_audio(my_aac_encoder, obs_get_audio());
        obs_output_set_video_encoder(my_output, my_h264_encoder);
        obs_output_set_audio_encoder(my_output, my_aac_encoder, 0); // set index=0, usually the default one.
        //Setting service
        obs_data_t *settings = obs_data_create_from_json(json_string_with_settings_for_twitch);
        
        //apply encoder settings
        
        rtmp_custom_service.apply_encoder_settings(rtmp_custom_data, video_settings, audio_settings);

        //this creates the twitch service
        rtmp_custom_service.create(settings, my_service);
        
        //this assigns the twitch service to the output
        obs_output_set_service(my_output, my_service); /* if a stream */

        /* start the output */
        obs_output_start(my_output);
        
    }

    void ShutDown() {
        
        /*Releases all data associated with OBS and terminates the OBS context */
        obs_output_stop(my_output);
        rtmp_custom_service.destroy(rtmp_custom_data);
        obs_module_unload();
        obs_encoder_release(my_h264_encoder);
        obs_encoder_release(my_aac_encoder);
        obs_source_release(my_source);

       
        obs_shutdown();
    }



void MyObsLib::HelloWorld(const char * s)
{
    MyObsLibPriv *theObj = new MyObsLibPriv;
    theObj->HelloWorldPriv(s);
    delete theObj;
};

void MyObsLibPriv::HelloWorldPriv(const char * s) 
{
    std::cout << s << std::endl;
};



