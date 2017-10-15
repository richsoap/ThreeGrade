# Green函数
## 目的
将一般的静电边值问题转化为特殊的静电边值问题
* 一个体电荷的边值问题在静电场中的重要意义：特殊问题的解->一般问题的解
* 已知条件:第一类或第二类边界条件
## 点电荷与电荷密度的转换
位于$\vec{x}$出的体电荷q的密度表示为$q\delta(\vec{x}-\vec{x'})=\rho(\vec{x})$
### 不同坐标系
* 球坐标:$\delta(\vec{r}-\vec{r'})=\frac{1}{r^2}\delta(r-r')\delta(\phi-\phi')\delta(cos\theta-cos\theta')$
* 柱坐标系:$\delta(\vec{r}-\vec{r'})=\frac{1}{\rho}\delta(\rho-\rho')\delta(\phi-\phi')\delta(cos\theta-cos\theta')$
### 均匀分布球壳
$\rho(vec{r'})=\frac{Q}{4\pi R^2}\delta(r'-R)$

### 坐标原点的电偶极子
$\rho(\vec{r'}=-\vec{p}\cdot\nabla'\delta(\vec{r}))$
## 解法
### 第一类
知道边界的值
$$\nabla^2\phi=-\frac{\rho}{\epsilon_0}\\\phi(r)=\phi_0\\\\
\nabla^2G=-\frac{\delta(\vec{x}-\vec{x'})}{\epsilon_0}\\G(r)=0$$
### 第二类
知道边界的梯度的值
$$\nabla^2\phi=-\frac{\rho}{\epsilon_0}\\\frac{\partial\phi}{\partial n}=\phi_{n0}\\\\
\nabla^2G=-\frac{\delta(\vec{x}-\vec{x'}}{\epsilon_0}\\\frac{\partial G}{\partial n}=-\frac{1}{\epsilon_0S}$$
### Green函数$G(\vec{x},\vec{x'})满足的方程$
$$\nabla^2G(\vec{x},\vec{x'})=-\frac{1}{\epsilon_0}\delta(\vec{x}-\vec{x'})\\其中\nabla只作用于\vec{x}$$
### 一些解
#### 无界空间
边界条件:无穷远处电势为0
$$G(\vec{x},\vec{x'})=\frac{1}{4\pi\epsilon_0}\cdot\frac{1}{|\vec{x}-\vec{x'}|}=\frac{1}{4\pi\epsilon_0r}$$
意义:$\vec{x'}$ 处的单位点电荷，在无界空间中的电势<br\>
证明:将该式强行代入Green方程
$$\nabla^2\frac{1}{r}\\r\neq 0,\nabla^2\frac{1}{r}=0\\
r=0,\int\nabla^2\frac{1}{r}dV=lim_{a\to0}\int\nabla^2\frac{1}{r^2+a^2}dV=-4\pi\\\nabla^2\frac{1}{r}=-4\pi\delta(\vec{x}-\vec{x'})$$
#### 上半空间
边界条件:某一平面电势为0
$$G=\frac{1}{4\pi\epsilon_0}[\frac{1}{r_1}-\frac{1}{r_2}]$$
#### 球外空间
边界条件:球壳接地
$$G(\vec{x},\vec{x'})=\frac{1}{4\pi\epsilon_0}[\frac{1}{\sqrt{R^2+R'^2-2RR'cos\theta}}-\frac{1}{\sqrt{(\frac{RR'}{R_0})^2}+R_0^2-2RR'cos\theta}]$$
## Green公式与边值问题的解
* 设区域V中，有两个函数 $\phi_1$与 $\phi_2$,则
$$\int_V(\phi_1\nabla^2\phi_2-\phi_2\nabla^2\phi_1)dV=\oint_s(\phi_1\frac{\partial\phi_2}{\partial n}-\phi_2\frac{\partial\phi_1}{\partial n})dS$$
* 对任意的情况都适用
$$令\phi_1=\phi,满足泊松方程,令\phi_2=G,满足Green方程(有\delta项),又将G中的\vec{x},\vec{x'}对调\\
\int_V[G(\vec{x'},\vec{x})\nabla'^2-\phi(\vec{x'})\nabla'^2G(\vec{x},\vec{x'})]dV'\\
第二项等于\frac{1}{\epsilon_0}\int\phi(\vec{x'})\delta(\vec{x'}-\vec{x})dV'=\frac{1}{\epsilon_0}\phi(\vec{x})$$
综上
$$\phi(\vec{x})=\int_VG(\vec{x},\vec{x'})\rho(\vec{x'})dv'+\epsilon_0\oint_S[G(\vec{x'},\vec{x})\frac{\partial\phi}{\partial n'}-\phi(\vec{x'})\frac{\partial}{\partial n}G(\vec{x'}-\vec{x})]ds'$$
### 对于第一类(齐次)边界条件:G(\vec{x'},\vec{x})=0
### 对于第二类边界条件

## 意义
* 一旦得到某种情况下的格林函数，则所有同类型的分布情况都可以得到解决
* 位于 $\vec{x}$ 处的单位点电荷在 $\vec{x'}$ 处的电势，与 $\vec{x'}$ 处的单位点电荷在 $\vec{x}$ 处的电势相等。

证明的话，设两个源点，然后将其带入Green函数，并用Green公式化开，利用边界条件和delta函数的挑选性质，即可得到相应的结论
