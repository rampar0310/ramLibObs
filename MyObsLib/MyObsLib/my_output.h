//
//  my_output.h
//  ObsProject
//
//  Created by Sivaraman, Ram on 8/24/21.
//

#ifndef my_output_h
#define my_output_h

#include <stdio.h>
#include "../../obs-studio/libobs/obs.h"
//#include "../../obs-studio/plugins/obs-outputs/rtmp-helpers.h



struct obs_output_info rtmp_output_info = {
    .id = "rtmp_output",
    .flags = OBS_OUTPUT_AV | OBS_OUTPUT_ENCODED | OBS_OUTPUT_SERVICE |
         OBS_OUTPUT_MULTI_TRACK,
    .encoded_video_codecs = "h264",
    .encoded_audio_codecs = "aac",
    .get_name = rtmp_stream_getname,
    .create = rtmp_stream_create,
    .destroy = rtmp_stream_destroy,
    .start = rtmp_stream_start,
    .stop = rtmp_stream_stop,
    .encoded_packet = rtmp_stream_data,
    .get_defaults = rtmp_stream_defaults,
    .get_properties = rtmp_stream_properties,
    .get_total_bytes = rtmp_stream_total_bytes_sent,
    .get_congestion = rtmp_stream_congestion,
    .get_connect_time_ms = rtmp_stream_connect_time,
    .get_dropped_frames = rtmp_stream_dropped_frames,
};

void set_rtmp_stream_defaults(obs_data_t* defaults) {
    rtmp_stream_defaults(defaults);
}


#endif /* my_output_h */
