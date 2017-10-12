# The Wireless Channel
## Why study wireless channels?
Reciver, Transmitter and channel make up communication system<br/>
Channel system matters a lot. Knowing communication channel is the key to transmit information well.
### Before channel(part 1)
### After channel(part 2)
## What are wireless channels?
### Some drawbacks
Scattering<br/>
Line-of-sight{LOS} path<br/>
Shadowing<br/>
Diffraction<br/>
Reflection<br/>
### Targets
Understand channel well, so that we can design the system better. It is not nessary to know every details about the channels. Making channel into a black box is enough.

We just need to know the
## Three phenomena in wireless channels
### Fading
Fading is the __variation__ of the received signal power due to the environment, multipaths, and mobility.
### Path Loss(Large Scale)
The longer signals go, the weaker signals are.
Hundred of wave lengths.
### Shadowing(Large Scale)
Big objects may cause some smal variation.
### Multipath Fading(Small Scale)
Less than a wave length.
## Multipath fading
$$Base expression: y(t)=h(t,\tau)\\h(\tau)=\sum_nc_ne^{-j\phi_n}\delta(\tau-\tau_n)$$
Phase is the point. Power is not very important in small scale.
$$solid:\phi=2\pi f_c\frac{d_n'}{c},d_n'=d_n-min\{d\}\\
mobile:d_n'\to d_n'+vt\cdot e(\theta_n)\\
\phi=2\pi f_c\frac{d_n'}{c}+2\pi f_De(\theta_n)t,f_d=f_c\frac{v}{c}$$
$$multiple antennas:\phi=2\pi f_c\frac{d_n'}{c}+2\pi f_De(\theta_n)t+2\pi\lambda^{-1}\epsilon\cdot k(\alpha_n)$$
### Duality of Wireless channels
To express the same phenomena in different domains.
* Time domain <-> Doppler domain
* Frequency domain <-> Delay domain
* Space domain <-> Angle domain
* Dispersion --- Selectivity

We have 4*2 ways to describe the channel.
#### Time and Delay
* Time:for different signals($T_s$)
* Delay:for the same signal, may get some echos.(Dealy spread,$De_t$)
$$T_s>De_t$$
No inter-symbol interference (Narrowband[freuency non-selective] channels)
$$T_s<De_t$$
inter-symbol interference (Wideband[frequency Selectivity] channel)

### Dispersion and Selectivity of Wireless channels
Dispersion: spread effect of wireless, which means that wireless channels spread the transmitted signal in a certain domain.

Selectivity: wireless channel changes over a certain domain.

They are also the same thing.
