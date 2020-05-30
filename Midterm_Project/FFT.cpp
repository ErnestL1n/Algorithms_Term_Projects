#include <cstdio>
#include <complex>
#include <iostream>
#include <valarray>
#include <ctime>


const double PI = 3.141592653589793238460;

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

//straight forward method O(n^2)
void DFT(CArray& x, CArray& y)
{
	const size_t N = x.size();

	

	for (size_t k = 0; k < N; k++) {
		y[k] = 0.0;
		for (size_t n = 0;n < N;n++) {
			Complex t = std::polar(1.0, -2 * PI * k * n / N);
			y[k]+=(x[n]*t);
		}
		
	}
}

// Divide and Conquer FFT
// Higher memory requirements and redundancy although more intuitive

void RecursiveFFT(CArray& x)
{
	//for example N=8
	const size_t N = x.size();
	if (N <= 1) return;

	// divide
	//even=x[0] x[2] x[4] x[6]
	CArray even = x[std::slice(0, N / 2, 2)];
	//even=x[1] x[3] x[5] x[7]
	CArray  odd = x[std::slice(1, N / 2, 2)];

	// conquer
	RecursiveFFT(even);
	RecursiveFFT(odd);


	// combine
	for (size_t k = 0; k < N / 2; ++k)
	{
		Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
		x[k] = even[k] + t;
		x[k + N / 2] = even[k] - t;
	}
}

// Bit reverse FFT (in-place, breadth-first, decimation-in-frequency)
// Better optimized but less intuitive

void IterativeFFT(CArray& x)
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

}


/*
// inverse fft (in-place)
void ifft(CArray& x)
{
	// conjugate the complex numbers
	x = x.apply(std::conj);

	// forward fft
	RecursiveFFT(x);

	// conjugate the complex numbers again
	x = x.apply(std::conj);

	// scale the numbers
	x /= x.size();
}
*/


int main()
{

	clock_t start, end;

	Complex test[32768];

	char option = 'n';

	//N=32768,M=10000
	//x[n]=1  <=>   mN-M<=n<=mN+M
	//x[n]=0  <=>   mN+M<n<(m+1)N-M
	//let m=1
	//shift<=>array[0]=array[22768]
	std::cout << std::endl;
	std::cout << "Please wait for about one minute,three procedures are running";
	std::cout << std::endl;
	std::cout << std::endl;
	//n=22768~42768
	for (int i = 0;i <= 20000;i++)test[i] = 1.0;

	//n=42769~55535
	for (int i = 20001;i <= 32767;i++)test[i] = 0.0;

	//for naive DFT
	CArray dft(test, 32768);  //origin one
	CArray Dft(test, 32768);  //after computing


	CArray Rfft(test, 32768);
	CArray Ifft(test, 32768);

	int i = 0;
	int	j = 0;
	int k = 0;

	//measure execution time
	start = clock();
	DFT(dft, Dft);
	end = clock();
	std::cout << "                Time taken by procedure  Normal-DFT  is :" << (double)(end - start) / double(CLOCKS_PER_SEC) << "seconds" << std::endl;
	std::cout << std::endl;

	start = clock();
	RecursiveFFT(Rfft);
	end = clock();
	std::cout << "                Time taken by procedure RecursiveFFT is :" << (double)(end - start) / double(CLOCKS_PER_SEC) <<"seconds" << std::endl;
	std::cout << std::endl;

	start= clock();
	IterativeFFT(Ifft);
	end = clock();
	std::cout << "                Time taken by procedure IterativeFFT is :" << (double)(end - start) / double(CLOCKS_PER_SEC) << "seconds" << std::endl;
	std::cout << std::endl;



	//each time run 32 points
	do {


		std::cout << "-------------------After Executing DFT(StraightForward)------------------------" << std::endl;

		for (int run = 32;i != 32768 && run != 0;i++, run--) {
			printf("Point%7d-----(real,imaginary)parts separated-----is : ", i);
			std::cout << Dft[i] << std::endl;
		}

		std::cout << std::endl;
		std::cout << std::endl;

		std::cout << "-------------------After Executing FFT(Divide And Conquer)------------------------" << std::endl;

		for (int run = 32;j != 32768 && run != 0;j++, run--) {
			printf("Point%7d-----(real,imaginary)parts separated-----is : ", j);
			std::cout << Rfft[j] << std::endl;
		}

		std::cout << std::endl;
		std::cout << std::endl;

		std::cout << "-------------------After Executing FFT(BitReversal)-------------------------------" << std::endl;

		for (int run = 32;k != 32768 && run != 0;k++, run--) {
			printf("Point%7d-----(real,imaginary)parts separated-----is : ", k);
			std::cout << Ifft[k] << std::endl;
		}

		std::cout << std::endl;
		std::cout << "ContinueToPrint? Please press 'Y' then enter" << std::endl;

		std::cin >> option;

	} while (option == 'Y' || option == 'y');


	return 0;
}