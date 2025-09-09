#include "fft.h"
#include <complex>
#include <cmath>
#include <iostream>
#include <vector>

// define pi
const float PI = acos(-1);

// alias for complex nums
using Complex = std::complex<float>;

// stft function here
std::vector<std::vector<Complex> > stft(const std::vector<float>& signal, size_t window_size, size_t hop_size) {
    std::vector<std::vector<Complex> > stft_results;

    std::vector<float> hann_window(window_size);
    for (size_t n = 0; n < window_size; ++n) {
        hann_window[n] = 0.5 * (1 - cos((2 * PI * n) / (window_size - 1)));
    }

    for (size_t i = 0; i + window_size <= signal.size(); i += hop_size) {
        std::vector<Complex> frame(window_size);
        
        for (size_t j = 0; j < window_size; ++j) {
            frame[j] = Complex(signal[i + j] * hann_window[j], 0.0f);
        }

        fft(frame);
        stft_results.push_back(frame);
    }
    return stft_results;
}


void print_spectrogram(const std::vector<std::vector<Complex> >& spectrogram, float sample_rate, size_t window_size) {
    std::cout << "- stft result -" << std::endl;

    if (spectrogram.empty()) {
        std::cout << "empty result" << std::endl;
        return;
    }

    for (size_t i = 0; i < spectrogram.size(); ++i) {
        const auto& frame = spectrogram[i];
        
        float max_magnitude = -1.0f;
        size_t max_bin_index = 0;

        for (size_t k = 0; k < window_size / 2; ++k) {
            float magnitude = std::abs(frame[k]);
            if (magnitude > max_magnitude) {
                max_magnitude = magnitude;
                max_bin_index = k;
            }
        }

        float dominant_frequency = (float)max_bin_index * sample_rate / window_size;

        std::cout << "frame " << i << ":\tdominant frequency = ~" << (int)dominant_frequency << " Hz" << std::endl;
    }
}

int main() {
    const float SAMPLE_RATE = 4000.0f; 
    const size_t WINDOW_SIZE = 512;   
    const size_t HOP_SIZE = 256;      

    std::vector<float> signal;
    size_t signal_length = 1 * SAMPLE_RATE; 
    float frequency1 = 440.0f;
    float frequency2 = 880.0f;

    for (size_t i = 0; i < signal_length / 2; ++i) {
        signal.push_back((sin(2.0f * PI * frequency1 * i / SAMPLE_RATE)));
    }

    for (size_t j = signal_length / 2; j < signal_length; ++j) {
        signal.push_back((sin(2.0f * PI * frequency2 * j / SAMPLE_RATE)));
    }

    std::cout << "1s, 440 -> 880hz" << std::endl;

    std::vector<std::vector<Complex> > spectrogram = stft(signal, WINDOW_SIZE, HOP_SIZE);

    print_spectrogram(spectrogram, SAMPLE_RATE, WINDOW_SIZE);

    return 0;
}

