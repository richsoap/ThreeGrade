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
* Tx:convert the sequence into a modulated pulse train(signal to pulse)
* Rx:reconstruct the signal by tracking certain parameter of the pulse train
* eg:PAM(amplitude),PWM(width),PPM(position),PCM(code)
### Pulse Modulation
LPF->Sampler->Quantizer->Bit-encoder->PS(->carrier modulation)
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
### Delta modulation
#### challenge
* we don't need so many bits
* difficult to design a many levels
#### for varying slowly(low frequency)
* do not represent each sample independently
* represent the difference between the amplitudes of successive samples
#### for high speed changing
overload distortion
### PCM vs Delta modulation
* PCM:bounds oon the samples
* Delta:bounds on sample differences,wors well for low-frequency data
* Sigma-Delta:can apply Delta-modultaion to $\int m(t)$,$\frac{\partial (PCM)}{\partial t}=Delta$
### Differential PCM
Taylor's formula
## Cocoders and Video Compression
