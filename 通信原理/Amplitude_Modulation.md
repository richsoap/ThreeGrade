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
Positive frequency is meaningful, nagative frequenency is meaningless.
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
* S2,bandpass filter to remove part of the signal
* Hilbert Transform:$H(\omega)=-jsgn(\omega) \$
###

###
