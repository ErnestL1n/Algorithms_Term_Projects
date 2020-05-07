//aurthor:https://github.com/ErnestL1n

//reference:Introduction to Algorithms, 3rd Edition (The MIT Press)
//reference:https://rosettacode.org/wiki/Fast_Fourier_transform#C.2B.2B
//This version is with Divide and Conquer approach

#include<cstdlib>
#include<iostream>
#include<complex>
#define _USE_MATH_DEFINES
#include <math.h>   //  =>  M_PI
#include<valarray>



const double PI=M_PI;

using namespace std;

typedef complex<double> Complex;

typedef valarray<Complex> complexArray;

// Type:int  Storage size: 4 bytes :-2147483648 to 2147483647
// 2147483647=2^31
// 32768=2^15


#define N 32768
#define M 10000


void Recursive_FFT(complexArray& x) {
	const size_t n = x.size();
	if (n <= 1) return;

	// divide
	complexArray even = x[std::slice(0, n / 2, 2)];
	complexArray  odd = x[std::slice(1, n / 2, 2)];

	// conquer
	Recursive_FFT(even);
	Recursive_FFT(odd);

	// combine
	for (size_t k = 0; k < n / 2; ++k)
	{
		Complex t = std::polar(1.0, -2 * PI * k / n) * odd[k];
		x[k] = even[k] + t;
		x[k + N / 2] = even[k] - t;
	}
}

