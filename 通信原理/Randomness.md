# Probabilities about Randomness
Infromation is random.
## probability
### Definition
...
### Bayes' rule
$$P(B_k|A)=\frac{P[A|B_k]P[B_k]}{\sum P[A|B_i]P[B_i]}$$
* 先验概率，发射前知道的概率(A)
* 后验概率，接收后才知道的概率(B)
* 条件概率，信道转移概率
### Bernoulli
$$P(A)=p,P(\bar{A})=1-p\\
K in N\\
\frac{n!}{k!(n-k)!}p^k(1-p)^{n-k}\\
N is big,p is small\\
C^k_np^k(1-p)^{n-k}\sim\frac{\lambda^k}{k!}e^{-\lambda},\lambda=np\\
n\to\infty,P\to Gaussian\ distribution$$
## Random Variables
...
## Random Processes
add time to random variables
* ensemble average:$E[X(t)]=\int_{-\infty}^\infty xf_x(x)dx$
* time average:$<X(t)>=lim_{\tau\to\infty}\frac{1}{2T}\int X(t)dt$
### Ergodicity

### Stationarity
### Power Spectral Density
### Filtering
