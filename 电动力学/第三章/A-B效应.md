# A-B效应
1959年提出，1960年被证实
## 内容
电子双缝干涉实验，双缝距离为d，屏上位置用y确定。在挡板后放置一个线圈，改变线圈磁通量，干涉图样会发生整体平移。
* $\phi$影响电子相位，进而影响干涉条纹，$\vec{A}$具有可观测的宏观现象
## 自由运动的电子波函数
$$\psi_0(\vec{x})=e^{\frac{i\vec{p}\cdot\vec{x}}{\hbar}},\vec{p}=m\vec{v}$$
线圈不通电时，有相位差
$$\Delta\phi_0=\frac{1}{\hbar}(\int_{c2}\vec{p_2}\cdot\vec{dl}-\int_{c1}\vec{p_1}\cdot\vec{dl})=\frac{1}{\hbar}p\Delta l=\frac{1}{\hbar}pd\frac{Y}{L}$$
线圈通电时，用正则动量表示波函数
$$\psi_0(\vec{x})=e^{\frac{i}{\hbar}\int\vec{P}\cdot\vec{dl}}\\
\vec{P}=\vec{p}-e\vec{A}=m\vec{v}-e\vec{A}\\
\Delta\phi=\Delta\phi_0-\frac{e}{\hbar}(\int_{c2}\vec{A}\cdot\vec{dl}-\int_{v1}\vec{A}\cdot\vec{dl})=\Delta\phi_0-\frac{e}{\hbar}\oint_C\vec{A}\cdot\vec{dl}(远场条件)=\Delta\phi_0-\frac{e}{\hbar}\Phi$$
* 由于 $\vec{A}$ 引起附加相位差，所以干涉条纹形状不变，只是出现y方向的平移，令相位差为0，可以解得偏移量为 $y_0=\frac{e\Phi L}{mvd}$
* 电子在磁场中的会有相同的相因子，$e^{i\frac{e}{\hbar}\oint_c\vec{A}\cdot\vec{dl}}$，由于c是任意的，所以当c趋于0时，就和局域场的结果差不多
