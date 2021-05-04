#ifndef THEINTERCEPT_AUDIO_H
#define THEINTERCEPT_AUDIO_H

#define SAMPLE_RATE     (16000)
#define SAMPLE_SIZE     (2)
#define SAMPLE_BITS     (SAMPLE_SIZE * 8)
#define I2S_NUM         (0)

void play_audio(const uint16_t *buf, uint32_t numSamples);

#endif //THEINTERCEPT_AUDIO_H
