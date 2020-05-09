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
void Recursive_FFT(complexArray& x)
{
	// DFT
	unsigned int N = x.size(), k = N, n;
	double thetaT = 3.14159265358979323846264338328L / N;
	Complex phiT = Complex(cos(thetaT), -sin(thetaT)), T;
	while (k > 1)
	{
		n = k;
		k >>= 1;
		phiT = phiT * phiT;
		T = 1.0L;
		for (unsigned int l = 0; l < k; l++)
		{
			for (unsigned int a = l; a < N; a += n)
			{
				unsigned int b = a + k;
				Complex t = x[a] - x[b];
				x[a] += x[b];
				x[b] = t * T;
			}
			T *= phiT;
		}
	}
	// Decimate
	unsigned int m = (unsigned int)log2(N);
	for (unsigned int a = 0; a < N; a++)
	{
		unsigned int b = a;
		// Reverse bits
		b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1));
		b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2));
		b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4));
		b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8));
		b = ((b >> 16) | (b << 16)) >> (32 - m);
		if (b > a)
		{
			Complex t = x[a];
			x[a] = x[b];
			x[b] = t;
		}
	}
	//// Normalize (This section make it not working correctly)
	//Complex f = 1.0 / sqrt(N);
	//for (unsigned int i = 0; i < N; i++)
	//	x[i] *= f;
}
	int main()
	{
		const Complex test[] = { 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0 };
		complexArray data(test, 8);



		// forward fft
		Recursive_FFT(data);

		std::cout << "fft" << std::endl;
		for (int i = 0; i < 8; ++i)
		{
			std::cout << data[i] << std::endl;
		}

		
		

		return 0;
	}







