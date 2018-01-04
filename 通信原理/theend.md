# Sampling
## Sampling and Reconstruction
### ABC
1. Sampling is the process of converting a continuous-time signal to a sequence of numbers
2. Reconstruction is the operation of filling the gaps in the sampled data
3. Alias refers to the fundamental distortion introduced by sampling
### Nyquist frequency
$$\Omega_N=2\Omega_m$$
$\Omega_m$ is the highest frequency of signal
### Problem
Sampling of an infinite bandwidth signal always gives rise to alisaing;no matter how high the sampling rate
### Solution
1. The bandwidth of a real signal is always practically finite
2. Filter the signal efore it is sampled
## PCM
* $T_x$:convert the sequence into a modulated pulse tran
* $R_x$:reconstruct the signal by tracking certain parameter of the pulse train
* eg:PAM,PWM,PPM,PCM
### Steps
* sample,quantize, and code
### Quantization
* Quantization noise:$P_q=\frac{1}{3}\frac{m_p^2}{L^2},signal\in[-m_p,m_p],divide into L levels$
* SNR:\frac{P_m}{P_q}
# Probability
## Law of Total Probability
$P[A]=P[A|B]P[P]+P[A|\overline{B}]P[\overline{B}]$
## Bayes' Rule
$P(B_k|A)=\frac{P[A|B_k]P[B_k]}{\sum P[A|B_i]P[B_i]}$
## Bernoulli Trials
Probability of k successes in n Bernoulli trials:
$$C_n^kp^k(1-p)^{n-k}=\frac{n!}{k!(n-k)!}p^k(1-p)^{n-k}$$
### Poisson distribution
$$P(X=k)=\frac{\lambda^k}{k!}e^{-\lambda},\lambda=probability\ of\ happening,k=times$$
## Random Variables(RV)
### Moments
$$X~Exp(\lambda)=>f(x)=\lambda e^{-lambda x},for\ x>0\\
Mean:\mu=E[X]=\int xf(x)dx\\
2ndmoment:E[X^2]=\int x^2f(x)dx\\
\sigma^2=E[X^2]-(E[X])^2\\
Expectation of function of a RV:E[g(X)]=\int g(x)f(x)dx$$
### Some Functions
* Gaussian:
$$X~N(\mu,\sigma^2)=>f(x)=\frac{1}{\sqrt{2\pi\sigma^2}}e^{-\frac{(x-\mu)^2}{2\sigma^2}}$$
* Q:
$$Q(x)=\int_x^\infty N(0,1)dx$$
* PDF:联合密度分布函数
### Conditional Probability
$$E[E[Y|X]]=E[Y]\\
E[Y|X]=\int yf(y|x)dy\\
E[E[Y|X]]=\int yf(y|x)dyf(x)dx=E[Y]\\
\sigma_{xy}=E[(x-\mu_x)(y-\mu_y)]=E[xy]-\mu_x\mu_y\\
\simga_{xy}=0=>x\ y\ are\ uncorrelate=>f(x|y)=E[XY]=E[X]E[Y]\\
f(x|y)=f(x),f(x,y)=f(x)f(y)=>independence$$
### Two Types of Averages
* ensemble average:E[X(t)]=\int_{-\infty}^{\infty} xf_x(x)dx
* time average:<X(t)>=\lim_{T\to\infty}\frac{1}{2T}\int_{-T}^T X(t)dt
### Ergodicity
* time average = ensemble averages
* \mu(t)=E[X(t)]
* $R_{xx}(t,t-\tau)=E[X(t)X^* (t-\tau)]$

### Strict Sense Stationary(SSS)
* its statistics are invariant to a time shift;the joint pdf for{X(t),...}is independent of t.
* Ergodic=>SSS,SSS/=>Ergodic
### WSS
* $E[X(t)]=\mu,E[X(t)X^* (t-\tau)]=R(\tau)$ are both independent of time t
* SSS=>WSS,WSS/=>SSS
#### Properties of R
$$ R_x(0)=power\\
  R_x(-\tau)=R_x^* (\tau)=>Hermitian symmetry\\
 |R_x(\tau)|\leq R_x(0)\\
 R_x(\tau_0)=R_x(0)=>R_x(m\tau_0)=R_x(0)\\
 if\ X(t)\ is\ ergodic,and\ not\ periodic=>R_x(\infty)=\mu^2\\
 F{R_x(\tau)}\geq0\ for\ all\ frequency$$
#### Power Spectral Density
$$S_x(f)=\int_{-\infty}^\infty R_x(\tau)e^{-j\omega\tau}\tau$$
# Digital Comm
## Line Coding
### On-Off Coding
$1\to p(t),0\to0$
### Polar Coding
$1\to p(t),0\to-p(t)$
### Bipolar Coding
$1\to p(t)or -p(t),0\to0$
### PSD
$$S_y(\omega)=|P(\omega)|^2S_x(\omega)\\
S_x(\omega)=\frac{1}{T_b}\sum_{n=-\infty}^\infty R_ne^{jn\omega T_b}\\
R_n=E[a_ka_{k+n}]\\
for\ p(t)=rect(\frac{t}{T_b/2})P(\omega)=\frac{T_b}{2}sinc(\frac{\omega T_b}{4}):width\ =\ T_b$$
