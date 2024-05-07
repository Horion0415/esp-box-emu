#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define AUDIO_SAMPLE_RATE (22000)
#define AUDIO_BUFFER_SIZE (AUDIO_SAMPLE_RATE / 5 + 1)

void audio_init();
int16_t* get_audio_buffer();
void audio_play_frame(uint8_t *data, uint32_t num_bytes);

bool is_muted();
void set_muted(bool mute);

int get_audio_volume();
void set_audio_volume(int percent);

#ifdef __cplusplus
}
#endif
