#  实验十五 CPLD可编程数字逻辑实验

<div style="text-align:center">实验人:杨庆龙<br/>学号:1500012956</div>

## 实验目的
学习可编程逻辑器件CPLD的应用

## 实验原理
### 系统整体结构
主要包括系统电源，CPLD主控核心，输入子系统以及输出子系统等4个部分组成。其中，主控核心是lattice的100-PIN TQFP封装的LC4128V75TN100；系统电源为由外接+9V和-5V提供，用于产生LC4128的3.3V电源以及运放LM358等的+5V和-5V电源；输入子系统由ADC以及按键组成；输出子系统由DAC，LED以及数码管组成。
### 主控制核心
实验中CPLD采用lattice的100-PIN TQFP封装的LC4128V75TN100，其功能块框图如图5所示，引脚图如图6所示。LC4000系列具有128个宏单元和先进高速I/O口，足以满足一般的开发实验的需要。
### 输入子系统
输入子系统有模数转换ADC、跳线开关以及按键等组成。
### 输出子系统
输入子系统由数模转换DAC、LED以及数码管等三个部分组成。
## 实验内容
### 实验九程序移植
重新选择器件，重新配置约束文件，再测量相应管脚的波形
### 数码管显示驱动
1. 同时点亮两个数码管，每秒钟数码管显示加1或者减1，依次显示00-99数码。
2. 通过SW跳线开关控制控制计数器是按照加或者减的方式进行计时。<br/>
提示：<br/>
系统时钟为10M有源晶振提供，可通过分频获得1Hz的显示计数频率。
熟悉数码管的控制逻辑；可通过调节数码管单次点亮的时间来加深对时序控制的理解；两个数码管采用轮流点亮的方法，利用人眼的视觉残留效果，从而达到“同时”点亮两个数码管的目的。注意：每个数码管要轮流点亮，不能出现闪烁现象！
## 实验结果
### 实验九程序移植
将扩展版实验九的代码导入该次实验的项目内，重新分配引脚如下
|定义|引脚编号|
|:---:|:---:|
|clk|89|
|button|3|
|[1:0]C|87,86|
|[3:0]Q|85,84,81,80|

即，将10MHz时钟作为系统运行时钟，将跳线开关作为button，使用LED输出口输出计数器状态和Q的值，但由于并未焊接LED，所以只能将示波器探头直接接到电路板的相应位置进行观察。通过短接跳线开关，即可切换系统工作状态。观察不同状态下的输出口可得
###### 00态下的系统输出
![00态下的系统输出](exm9photo/00.jpg)
###### 01态下的系统输出
![01态下的系统输出](exm9photo/01.jpg)
###### 10态下的系统输出
![10态下的系统输出](exm9photo/10.jpg)
###### 11态下的系统输出
![11态下的系统输出](exm9photo/11.jpg)

可以看到，除了系统工作频率太高导致方波形状略有变形外，系统工作符合设计要求。
### 数码管显示驱动
#### 设计
要利用视觉暂留实现双数码管显示，而又考虑到数码管从选通到发光需要一定的时间，所以交替选通的频率又不能太高，因此，考虑选用200Hz的信号交替选通。又再在200Hz信号的基础上分出1Hz的计数时钟信号，进而再根据跳线开关改变计数值。
#### 结果
该系统能够在跳线开关接上的情况下每秒减计数一次，在跳线开关断开连接的情况下每秒加计数一次。该系统对溢出的处理方法为，下溢出后将数值改为最大值99，上溢出后将数值改为最小值00。
## 实验记录
![](exm9photo/end.jpg)
## 源码
### 实验九
```
module top(
    input clk,
    input button,
    output [1:0] C,
    output [3:0] Q
    );
    reg [3:0]Q;
    reg [1:0]C;
    reg before;

    always@(posedge clk)
    begin
        if(~before&button)
	         begin
	          C[0]<=~C[0];
	           if((C[1]&~C[0])|(~C[1]&C[0]))
	            C[1]<=1;
	           else
	            C[1]<=0;
	         end
	      Q[0]<=((~Q[1]&~Q[2]&~(Q[0]&~Q[3]))&(~C[0]&~C[1]))|((~Q[3]&~(Q[2]&Q[1]&~Q[0]))&(C[0]&~C[1]))|((~Q[3]&~(~Q[2]&Q[1]&Q[0]))&(~C[0]&C[1])) |(((Q[0]&~Q[3])|(Q[3]&~Q[0])|(~Q[0]&~Q[1]&~Q[2]&~Q[3]))&(C[0]&C[1]));
	      Q[1]<=Q[0];
	      Q[2]<=Q[1];
	      Q[3]<=Q[2];
        before<=button;
    end
endmodule

```

### 数码管显示驱动
```
module counter(
  input direction,
  input clk,
  output [1:0] select,
  output [6:0] digital
);
reg [31:0] smalldiv;
reg [31:0] bigdiv;
reg [6:0] digital;
reg [3:0] buffer;
reg [1:0] select;
reg [3:0] num [1:0];

always@(posedge clk)
begin
  if(smalldiv >= 32'D49999)
    begin
    bigdiv <= bigdiv + 32'D1;
    smalldiv <= 32'D0;
    if(select == 2'B01)//以200Hz的频率改变选通数码管
      select <= 2'B10;
    else
      select <= 2'B01;
    end
  else
    smalldiv <= smalldiv + 32'D1;

  if(bigdiv >= 32'D200)//以1Hz的频率改变计数
    begin
    bigdiv <= 32'D0;
    if(direction)//断开，加计数
      begin
      if(num[0] < 4'D9 & num[0] >= 4'D0)
        num[0] <= num[0] + 4'D1;
      else
        begin
        num[0] <= 4'D0;
        if(num[1] >= 4'D0 & num[1] < 4'D9)
          num[1] <= num[1] + 4'D1;
        else
          num[1] <= 4'D0;
        end
      end
      else
      begin
      if(num[0] <= 4'D9 & num[0] > 4'D0)
        num[0] <= num[0] - 4'D1;
      else//接上，减计数
        begin
        num[0] <= 4'D9;
        if(num[1] <= 4'D9 & num[1] > 4'D0)
          num[1] <= num[1] - 4'D1;
        else
          num[1] <= 4'D9;
      end
    end

    if(select == 2'B01)//根据选通数码管选择输出不同数字
      buffer <= num[0];
    else
      buffer <= num[1];

    case(buffer)//译码
    4'd0: digital <= 7'h3f;				//显示0
    4'd1: digital <= 7'h06;                //显示1
    4'd2: digital <= 7'h5b;                //显示2
    4'd3: digital <= 7'h4f;                //显示3
    4'd4: digital <= 7'h66;                //显示4
    4'd5: digital <= 7'h6d;                //显示5
    4'd6: digital <= 7'h7d;                //显示6
    4'd7: digital <= 7'h07;                //显示7
    4'd8: digital <= 7'h7f;                //显示8
    4'd9: digital <= 7'h67;                //显示9
    endcase
end
endmodule

```
