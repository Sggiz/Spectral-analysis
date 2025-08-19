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

### 2. FFT principle

Let $X = \left[ X(0), X(1), \ldots, X(N-1) \right]$ be the input signal, its $n$-th component being $X(n)$ and its length of the form $N = 2^b$.
Let's define two derived signals of length $\frac{N}{2} = 2^{b-1}$ :

- $X_{\mathsf{even}} = \left[ X(0), X(2), \ldots, X(N-2) \right] = \left[ X(2n)\right]$
- $X_{\mathsf{odd}} = \left[ X(1), X(3), \ldots, X(N-1) \right] = \left[ X(2n+1)\rigth]$

We'll call their respective transforms $Y$, $Y_{\mathsf{even}}$ and $Y_{\mathsf{odd}}$. Thus, by the definition of the Fourier transform, for a given $k \in \llbracket 1, N-1 \rrbracket$ :

$$ Y(k) = \sum_{n=0}^{N-1} X(n) \exp{-2i \pi k \frac{n}{N}} $$

To easy the following expressions, we introduce the complex constant $\omega = \exp(-2i \pi /N)$ which verifies :

$$ \omega^{n} = \omega^{n \mod N} $$

Thus we can write :

$$ Y(k) = \sum_{n=0}^{N-1} \omega^{kn} X(n) $$

And knowing that $Y_{\mathsf{even}}$ and $Y_{\mathsf{odd}}$'s corresponding constants is $\omega^2$ :

$$ Y_{\mathsf{even}}(k) = \sum_{n=0}^{\frac{N}{2}-1} (\omega^2)^kn X(2n)$$

$$ Y_{\mathsf{odd}}(k) = \sum_{n=0}^{\frac{N}{2}-1} (\omega^2)^kn X(2n+1) $$

With these equations we easily prove, by dividing the first sum into two sums with alternating terms, that if $k \in \llbracket 1, \frac{N}{2} -1 \rrbracket$ :

$$ Y(k) = Y_{\mathsf{even}}(k) + \omega^k Y_{\mathsf{odd}}(k) $$

And more generally, with $\omega$'s cyclic nature, if $k \in \llbracket 1, N-1 \rrbracket$ :

$$ Y(k) = Y_{\mathsf{even}}(k \mod \frac{N}{2}) + \omega^k Y_{\mathsf{odd}}(k \mod \frac{N}{2}) $$

With this relation between a transform of an entry signal and the transforms of its derived signals (with halved lengths), we can deduce the Fast-Fourier-Transform algorithm.
Elementary inputs are Single-data signals, which are their own transform and a transforms construction through the last relation is made linearly.
Thus, we achieve a nearly-linear complexity through the dynamic programming algorithm based on the proven results.