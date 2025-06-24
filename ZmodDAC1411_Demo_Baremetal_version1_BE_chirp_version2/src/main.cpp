#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include "xparameters.h"
#include "zmoddac1411.h"
#include "zmod.h"

#define ZMOD_DAC_BASE_ADDR     XPAR_ZMODDAC_0_AXI_ZMODDAC1411_V1_0_0_BASEADDR
#define DMA_DAC_BASE_ADDR      XPAR_ZMODDAC_0_AXI_DMA_1_BASEADDR
#define FLASH_ADDR_DAC         0x31
#define DMA_DAC_IRQ            XPAR_FABRIC_ZMODDAC_0_AXI_DMA_1_MM2S_INTROUT_INTR
#define IIC_BASE_ADDR          XPAR_PS7_I2C_1_BASEADDR

// Constants for Chirp
const double PI = 3.14159265358979323846;

// Function to apply Gaussian window
void applyGaussianWindow(std::vector<float> &waveform, float smoothing, float duration) {
    int n = waveform.size();
    std::vector<float> window(n);
    for (int i = 0; i < n; i++) {
        float t = i * duration / n;
        window[i] = 0.5 * (1 + erf((t - 2 * smoothing) / smoothing))
                  - 0.5 * (1 + erf((t + 2 * smoothing - duration) / smoothing));
        waveform[i] *= window[i];
    }
}

// Function to generate chirp
std::vector<float> generateChirp(float freq1, float freq2, float duration, int samples, float amplitude, bool reverse = false) {
    std::vector<float> waveform(samples);
    float m = (freq2 - freq1) / (2 * duration);
    for (int i = 0; i < samples; i++) {
        float t = i * duration / samples;
        float freq = m * t + freq1;
        waveform[i] = amplitude * sin(2 * PI * t * freq);
    }
    if (reverse) {
        std::reverse(waveform.begin(), waveform.end());
    }
    return waveform;
}

// Function to add delay
void addDelay(std::vector<float> &waveform, int preDelay, int postDelay) {
    waveform.insert(waveform.begin(), preDelay, 0.0f);
    waveform.insert(waveform.end(), postDelay, 0.0f);
}

// Function to repeat waveform
std::vector<float> repeatWaveform(const std::vector<float> &waveform, int repetitions) {
    std::vector<float> repeatedWaveform;
    for (int i = 0; i < repetitions; i++) {
        repeatedWaveform.insert(repeatedWaveform.end(), waveform.begin(), waveform.end());
    }
    return repeatedWaveform;
}

int main() {
    // Initialize the DAC object
    ZMODDAC1411 dacZmod(ZMOD_DAC_BASE_ADDR, DMA_DAC_BASE_ADDR, IIC_BASE_ADDR, FLASH_ADDR_DAC, DMA_DAC_IRQ);

    // Parameters for the chirp (band excitation) signal
    float center_freq = 500e3;
    float bandwidth = 60e3;
    float duration = 4e-3;
    int BE_ppw = 1000;       // points per waveform
    int BE_rep = 2;          // number of repetitions
    float amplitude = 1;
    float smoothing = 125;
    bool chirpUp = true;
    
    float freq1 = center_freq - bandwidth / 2;
    float freq2 = center_freq + bandwidth / 2;
    
    // Generate chirp waveform (Band Excitation)
    std::vector<float> chirpWaveform = generateChirp(freq1, freq2, duration, BE_ppw, amplitude, !chirpUp);
    applyGaussianWindow(chirpWaveform, smoothing, duration);
    int preDelay = 0;
    int postDelay = 0;
    addDelay(chirpWaveform, preDelay, postDelay);
    std::vector<float> repeatedChirp = repeatWaveform(chirpWaveform, BE_rep);

    // Generate a second signal: Cantilever Excitation Waveform
    // For this example, we simply scale the chirp signal (e.g., to have a range from -4 to 4)
    std::vector<float> cantileverWaveform = repeatedChirp;
    float cantileverScale = 4.0f;
    for (size_t i = 0; i < cantileverWaveform.size(); i++) {
        cantileverWaveform[i] *= cantileverScale;
    }

    // Assuming the DAC supports 2 channels, we allocate a buffer that will hold interleaved data:
    // Lower 16 bits for channel 0 (chirp) and upper 16 bits for channel 1 (cantilever).
    size_t length = repeatedChirp.size();
    uint32_t *buf = dacZmod.allocChannelsBuffer(length);

    for (size_t i = 0; i < length; i++) {
        int16_t valRawChirp = dacZmod.getSignedRawFromVolt(repeatedChirp[i], 1);
        int16_t valRawCantilever = dacZmod.getSignedRawFromVolt(cantileverWaveform[i], 1);
        // Pack channel 0 in the lower 16 bits and channel 1 in the upper 16 bits
        buf[i] = ((uint16_t)valRawCantilever << 16) | ((uint16_t)valRawChirp);
    }

    // Configure the DAC: set frequency divider and gain for both channels
    dacZmod.setOutputSampleFrequencyDivider(2);
    dacZmod.setGain(0, 1);
    dacZmod.setGain(1, 1);

    // Transfer the buffer to the DAC and start the output
    dacZmod.setData(buf, length);
    dacZmod.start();

    // Free the allocated buffer
    dacZmod.freeChannelsBuffer(buf, length);

    return 0;
}
