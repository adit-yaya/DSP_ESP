#pragma once

#include <vector>
#include <complex>
#include <cmath>
 
// alias for complex nums
using Complex = std::complex<float>;

// write my own swap algorithm for funs
void swap(Complex& i, Complex& j);

// bit reverse function to permute input array in place
size_t bit_reverse(size_t n, int num_bits);

// fft function
void fft(std::vector<Complex>& x);