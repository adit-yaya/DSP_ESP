
#include "fft.h"
#include <iostream>

// define pi
const float PI = acos(-1.0f);

// alias for complex nums
using Complex = std::complex<float>;

// write my own swap algorithm for funs
void swap(Complex& i, Complex& j) {
    Complex temp = i;
    i = j;
    j = temp;
}

// bit reverse function to permute input array in place
size_t bit_reverse(size_t n, int num_bits) {
    size_t reversed_n = 0;

    for (int bit = 0; bit < num_bits; bit++) {
        // move reversed over to left one bit
        reversed_n <<= 1;
        // add last bit from n to reversed_n
        reversed_n |= (n & 1);
        // discard front bit
        n >>= 1;
    }

    return reversed_n;
}

// fft function
void fft(std::vector<Complex>& x) {
    // logic
    const size_t N = x.size();
    int num_bits = std::log2(N);

    // base case, empty signal
    if (N <= 1) {
        return;
    }

    for (size_t i = 0; i < N - 1; i++) {
        size_t j = bit_reverse(i, num_bits);

        if (i < j) {
            swap(x[i], x[j]);
        }
    }

    for (size_t len = 2; len <= N; len = len * 2) {
        for (size_t i = 0; i < N; i += len) {
            for (size_t k = 0; k < len / 2; k++) {
                float angle = (-2.0 * PI * k) / len;
                float magnitude = 1;

                Complex twiddle_factor = std::polar(magnitude, angle);

                Complex u = x[i + k];
                Complex v = x[i + (len / 2) + k];

                x[i + k] = u + twiddle_factor * v;
                x[i + (len / 2) + k] = u - twiddle_factor * v;
            }
        }
    }
}


void print_vector(const std::string& label, const std::vector<Complex>& x) {
    std::cout << label << ":" << std::endl;
    for (size_t i = 0; i < x.size(); i++) {
        std::cout << " [" << i << "] = " << x[i] << std::endl;
    }
}

int main() {
    std::vector<Complex> signal = {1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0};
    print_vector("signal", signal);
    
    fft(signal);

    print_vector("fft result", signal);

    return 0;
}