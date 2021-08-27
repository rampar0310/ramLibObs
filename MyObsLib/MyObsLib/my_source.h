//
//  my_source.h
//  ObsProject
//
//  Created by Sivaraman, Ram on 8/24/21.
//

#ifndef my_source_h
#define my_source_h

#include <stdio.h>
#include "/Users/rsivaram/logitech/obs-studio/libobs/obs.h"
void *(create)(obs_data_t *settings, obs_source_t *source);
const char* (sourcename)(void*);
void (destroy)(void *);
unsigned int (source_update)(void*);
unsigned int (source_render)(void*);
void get_width(struct obs_data *);
obs_properties_t* get_height(void *);

struct obs_source_info my_source_info = {
    "my_source",
    OBS_SOURCE_TYPE_INPUT,
    OBS_SOURCE_VIDEO,
    sourcename,
    create,
    destroy,
    source_update,
    source_render,
    get_width,
    get_height
};



#endif /* my_source_h */
