* Essential bandwidth=$R_b=\frac{1}{T_b}$
* average energy per symbol=$E_s=\frac{1}{n}\sum_{k=1}^n a_k^2$
* average energy per bit=$E_b=\frac{E_s}{\lceil log_2n\rceil}$
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
\sigma_{xy}=0=>x\ y\ are\ uncorrelate=>f(x|y)=E[XY]=E[X]E[Y]\\
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
#### Polar
$R_0=E[a_k^2]=1,R_n=E[a_ka_{k+n}]=E[a_k]E[a_{k+n}]=0$
#### On-Off Keying
$R_0=\frac{1}{2},R_n=\frac{1}{4},S_x=\frac{1}{4T_b}(1+\frac{2\pi}{T_b}\sum_{n=-\infty}^\infty\delta(\omega-\frac{2\pi n}{T_b}))=\frac{1}{4T_b}(1+\sum e^{-jn\omega T_b})$<br/>
级数求和看作无限长δ函数的傅里叶变换:$\sum e^{-jn\omega T_b}=\frac{2\pi}{T_b}\sum\delta(\omega-\frac{2n\pi}{T_b})$
#### Bipolar
$R_0=\frac{1}{2},R_1=-\frac{1}{4},R_2=0,R_n=0$
## Digital Baseband Transmission
### Inter-Sysbol Interference(ISI)
* Define $p_i=p(iT_b)$
* Zero ISI -> $y_n=\sum a_kp_{n_k}=\sum p_ia_{n-i}=\sqrt{E}a_n$
* Let $p_0=\sqrt{E},y_n=a_n\sqrt{E}+\sum p_ia_{n-i}$
* $"-"=past,"+"=future$
### Ideal Nyquist Pulse
* $p(t)=\sqrt{E}sinc(\frac{t}{T_b})$
* $P(\omega)=\sqrt{E}/0$
* $p_i=p(iT_b)=\sqrt{E}/0$
* $p(f_0)=0.5R_b,R_b=\frac{1}{T_b},R_b\ is\ in\ \omega space$
### Raised Cosine Spectrum
$$p(t)=\sqrt{E}sinc(\frac{t}{T_b})(\frac{cos(\alpha t\pi/T_b)}{1-4\alpha^2t^2/T_b^2})\\
For\ large\ t,envelope\ of\ p(t)\ decays\ in\ \frac{1}{t^3}\\
Transmission\ bandwidth\ requirement\ B_\tau=\frac{1+\alpha}{2T_b}\\
Roll-off\ factor\ \alpha=\frac{f_x}{f_0}$$
### Duobinary Pulse
$$p(t)=\frac{sin(\pi R_bt)}{\pi R_bt(1-T_bt)}\\
P(\omega)=\frac{2}{R_b}cos(\frac{\omega}{2R_b})rect(\frac{\omega}{2\pi R_b})e^{-j\frac{\omega}{2R_b}}\\
p(t)decays\ in\ \frac{1}{t^2}\\
p_i=1[i=0,1],0$$
### M-ary Data
### Eye Diagram
time function defined on $-\frac{T_b}{2}\leq t\leq\frac{T_b}{2}$,must show the time axis
### Detector
* Correlation Receiver:Max:$\int(r(t)-s_i(t))^2dt$
* Minimum Distance Detector:Max:$\int r(t)s_i(t)-\frac{E_i}{2}$
* Projection Receiver:Min:$||r-s_i||^2$
### FSK
$$\Delta f= \frac{f_m-f_1}{2}=\frac{M-1}{2}\delta f\\
B_T=2(\frac{M-1}{2}\delta f+f_{carrier})$$
