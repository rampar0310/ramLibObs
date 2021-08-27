//
//  my_service.h
//  ObsProject
//
//  Created by Sivaraman, Ram on 8/24/21.
//

#ifndef my_service_h
#define my_service_h

#include <stdio.h>
#include "/Users/rsivaram/logitech/obs-studio/libobs/obs.h"

struct obs_service_info rtmp_custom_service = {
    .id = "rtmp_custom",
        .get_name = rtmp_custom_name,
        .create = rtmp_custom_create,
        .destroy = rtmp_custom_destroy,
        .update = rtmp_custom_update,
        .get_properties = rtmp_custom_properties,
        .get_url = rtmp_custom_url,
        .get_key = rtmp_custom_key,
        .get_username = rtmp_custom_username,
        .get_password = rtmp_custom_password,
        .apply_encoder_settings = rtmp_custom_apply_settings
    
};

#endif /* my_service_h */
