#include <complex>
#include <cmath>
#include <iostream>
#include <vector>

// define pi
const double PI = acos(-1);

// alias for complex nums
using Complex = std::complex<double>;

// fft function
void fft(std::vector<Complex>& x) {
    // logic
    const size_t N = x.size();

    // base case, empty signal
    if (N <= 1) {
        return;
    }

    // divide, split signal into even and odd subsequences
    std::vector<Complex> even(N/2);
    std::vector<Complex> odd(N/2);

    for (size_t i = 0; i < N / 2; i++) {
        even[i] = x[2*i];
        odd[i] = x[2*i + 1];
    }

    // conquer
    fft(even);
    fft(odd);

    // combine
    for (size_t k = 0; k < N / 2; k++) {
        // calculate twiddle_factor
        double angle = (-2.0 * PI * k) / N;
        double magnitude = 1;
        Complex twiddle_factor = std::polar(magnitude, angle);

        Complex T = twiddle_factor * odd[k];
        x[k] = even[k] + T;
        x[k + N/2] = even[k] - T;
    }
}

void print_vector(const std::string& label, const std::vector<Complex>& x) {
    std::cout << label << ":" << std::endl;
    for (size_t i = 0; i < x.size(); i++) {
        std::cout << " [" << i << "] = " << x[i] << std::endl;
    }
}

int main() {
    std::vector<Complex> signal = {1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    print_vector("signal", signal);
    
    fft(signal);

    print_vector("fft result", signal);

    return 0;
}


