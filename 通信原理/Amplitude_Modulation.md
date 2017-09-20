# Amplitude Modulation
## Outline
* Double sideband suppressed carrier
* Amplitude Modulation
* Quadrature amplitude Modulation
* single sideband Modulation
* Vestigial sideband Modulation
* Local carrier synchronization

## DAB-SC
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
