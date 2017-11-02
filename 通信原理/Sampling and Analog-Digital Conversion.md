# Sampling and Analog-Digital Conversion
## Sampling Theorem
### Sampling
converting a continuous-time signal to a sequence of numbers.Sample frequency should be double of signal frequency.
#### Nyquist frequency(not infinite bandwidth)
$$\Omega_N\geq2\Omega_m$$
#### infinite bandwidth
use band-pass filter(Antialiasing filter)
#### time statement
时域是连续函数，再采样之后，能符合幅值条件且连续的函数只有一个。即，gap间的信息被存在相关性里
### Reconstruction
filling the gaps in the sampled data
## Pulse Code Modulation(PCM)
* Tx:convert the sequence into a modulated pulse train
* Rx:reconstruct the signal by tracking certain parameter of the pulse train
* eg:PAM(amplitude),PWM(width),PPM(position),PCM(code)
### Pulse Modulation
LPF->Sampler->Quantizer->Bit-encoder->carrier modulation
### Quantization
#### Uniform Quantization
$$m(t)\in[-m_p,m_p]\\
\Delta m=\frac{2m_p}{L}$$
use advanced modulation
#### Nonuniform Quantization
Not Uniform
### Transmission
### Time division
## Delta Modulation & Differential Pulse Code Modulation

## Cocoders and Video Compression
