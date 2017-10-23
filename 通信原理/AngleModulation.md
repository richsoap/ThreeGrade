# Angle Modulation
## Frequency False Start
$$A_ccos[(\omega_c+km(t))t+\phi]$$
if k is as small as possible,$\delta \omega$ will very very small.<br/>
However, the result is a cos times a rectangle signal. Therefore, the frequency plot is not a delta, but a sinc.
The small rectangle signal is, the widther bandwidth is.
* carrier frequency is not bandwidth
## Basic Definition
* Basic carrier signal:$A_ccos(2\pi f_c+\phi)$
* Baseband signal:$m(t)$
* Frequency Modulation:$A_ccos(2\pi (f_c+k_fm(t))+\phi)$
* Phase Modulation:$A_ccos(2\pi f_c+\phi_0+k_pm(t))$
* $\omega=\frac{d\phi}{dt},\phi=\int\omega dt$
* $B=2B(\beta+1),\beta=\frac{k_fm_p}{2\pi B}or\frac{k_pm_p'}{2\pi B},B=bandwidth\ of\ signal,m_p'=max(adb(\frac{d m(t)}{dt}))$
* PM depends on both amplitude and bandwidth
* FM depends on the amplitude, but has little to do with the bandwidth
### Frequency Multiplier
A device which can double or triple frequency in an easy way.
## Nonlinear Distortion
### AM
there will be $cos[(\omega_c+3\omega_m)t]$, which is very hard to filted.
### FM
m(t) will always be grouped with $\omega_c$, which is very easy to filted.
## Generation of FM signals
### Narrow band
Change $Acos(\omega_ct+k_pm(t))t$ to $Acos(\omega_ct)-k_pm(t)Asin(\omega_ct)$(BSD)
### Wide band
#### Armstrong
$$Acos(\frac{\omega_c}{N}t+\frac{k_p}{N}m(t))$$
Then use Frequency Multiplier remove N.
#### Direct
Use phase locker
## Demodulation
### $\frac{\phi(t)}{dt}$
Then Envelope detector
###
5.1-3 5.2-1 5.2-7
