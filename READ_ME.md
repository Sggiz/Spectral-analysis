## Fast Fourier Transform

The Fast Fourier Transform is a dynamic algorithm used to calculate the discrete fourier transform of a given signal. It is implemented through the function `computeFFT` which has the following prototype :

    Spectre* computeFFT(Sig* sig)

Using a Divide-and-Conquer process, its time-complexity is brought down to being nearly-linear, instead of the quadratic complexity of the naive approach.

### 1. padding

In order to simplify the FFT implementation, the entry signal of length $N$ is padded with $p$ zeroes, ensuring that we manipulate a signal of length $2^b$.

To find how the entry signal has to be padded (calculating p), we notice the following conditions :

> $2^{b-1} < N \leq 2^b$
> $b-1 < \log_2 N \leq b$
> $b = \lceil \log_2 N \rceil$
> thus:
> $p = 2^b - N = 2^{\lceil \log_2 N \rceil} - N$

