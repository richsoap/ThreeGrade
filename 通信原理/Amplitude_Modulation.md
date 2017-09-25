# Amplitude Modulation
## Outline
* Double sideband suppressed carrier
* Amplitude Modulation
* Quadrature amplitude Modulation
* single sideband Modulation
* Vestigial sideband Modulation
* Local carrier synchronization

## DSB-SC
### meaning
* Double:one peak to two
* No division，0/0 = N/A
### expression
* Message Signal: $m(t)$
* Carrier Signal: $cos(\omega_c*t)$
* $m(t)cos(\omega_c*t)=\frac{1}{2}m(t)e^{-j\omega_ct}\frac{1}{2}m(t)e^{j\omega_ct}$
### demodulation
Synchronous/Coherent demodulation

## AM
### meaning
The first way of AM.</br>
Extra transmit power( A+min(m(t)) > 0 )</br>
Easy to demodulation(envelope detector).</br>
Positive frequency is meaningful, nagative frequency is meaningless.
### expression
* Message Signal: $m(t)$
* Carrier Signal: $cos(\omega_ct)$
* Modulated Signal: $(A + m(t))cos(\omega_ct)$ $\frac{1}{2}[M(\omega+\omega_c)+M(\omega-\omega_c)]+\frac{A}{2}[\delta(\omega+\omega_c)+\delta(\omega-\omega_c)]$
### demodulation
Asynchronous demodulation

## QAM
### meaning
Use sin for f1, cos for f2 to modulate 2 signals at the same time.
### expression
$$\phi(t) = m_1(t)\cdot cos(\omega t)+m_2(t)\cdot sin(\omega t)\\$$
### demodulation
Synchronous/Coherent demodulation(sin and cos for different signals)

## SSB
### meaning
* S1,$m(t)* cos(\omega t)$
* S2,bandpass filter to remove part of the signal(shar frequency cut of is very difficult to implement at high frequency)
* Hilbert Transform: $H(\omega )=-jsgn(\omega)$
* Or, two steps. move to $\omega_m$(low than $\omega_t$),than use a bandpass filter.Then move to $\omega_t$.
### envelope detector
$$A^2>>m^2(t)+m_h^2(t)\\
Acos(\omega t)+m(t)cos(\omega t)+m_h(t)sin(\omega t) = [A+m(t)]cos(\omega t)+m_h(t)sin(\omega t)\\=K(t)[cos\theta cos(\omega t)+sin\theta sin(\omega t)]\\
K^2(t)=A^2[1+frac{2m(t)}{A}+\frac{m^2(t)+m_h^2(t)}{A^2}]\\Envelop \approx \sqrt{1+2m(t)/A}-1\approx m(t)/A$$

## VSB(Vestigial sideband modulation)
### meaning
* It's too hard to make SSB true. Therefore we have to use VSB to approach it.
* filter requirenment: side pass filter should be able to make up a bandpass filter.
### method
Modulation
$$S_1:\Phi_{VSB}={M(\omega-\omega_c)+M(\omega+\omega_c)}H_t(\omega):H_t is\;transmitter\;shaping\;filter\\
S_2:pass\;2\Phi_{VSB}cos(\omega_c t)through\;filter\;H_o(\omega)\\
S_3:Spectrum\;of\;the\;demodulated\;signal\\
[\Phi_{VSB}(\omega+\omega_c)+\Phi_{VSB}(\omega-\omega_c)]H_o(\omega)\\
s_4:low\;frequency\;terms\\
M(\omega)\{H_t(\omega+\omega_c)+H_t(\omega-\omega_c)\}H_o(\omega)\\
require:\{H_t(\omega+\omega_c)+H_t(\omega-\omega_c)\}H_o(\omega)=1$$

## Local carrier synchronization
### Math
$$\Phi(t)=m(t)cos[(\omega_c+\Delta \omega)t+\delta]\\
Demodulation\\
2\Phi(t)cos\omega_c\\
After\;lowpass\;filtering\\
m(t)cos[\Delta\omega t+\delta]\\
\Delta\omega\;is\;very\;small\\
cos[\Delta\omega t+\delta]=cos\delta-t\Delta\omega sin\delta+O(t)$$

## homework
4.2-3,4.2-4,4.2-8,4.3-2,4.3-5,4.4-6,4.5-2
