//
//  my_encoder.h
//  ObsProject
//
//  Created by Sivaraman, Ram on 8/24/21.
//

#ifndef my_encoder_h
#define my_encoder_h

#include <stdio.h>
#include "/Users/rsivaram/logitech/obs-studio/libobs/obs.h"


struct obs_encoder_info obs_x264_encoder = {
    .id = "obs_x264",
    .type = OBS_ENCODER_VIDEO,
    .codec = "h264",
    .get_name = obs_x264_getname,
    .create = obs_x264_create,
    .destroy = obs_x264_destroy,
    .encode = obs_x264_encode,
    .update = obs_x264_update,
    .get_properties = obs_x264_props,
    .get_defaults = obs_x264_defaults,
    .get_extra_data = obs_x264_extra_data,
    .get_sei_data = obs_x264_sei,
    .get_video_info = obs_x264_video_info,
    .caps = OBS_ENCODER_CAP_DYN_BITRATE,
};


#endif /* my_encoder_h */
