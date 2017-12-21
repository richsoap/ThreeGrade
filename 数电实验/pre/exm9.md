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
1). 同时点亮两个数码管，每秒钟数码管显示加1或者减1，依次显示00-99数码。<br/>
2). 通过SW跳线开关控制控制计数器是按照加或者减的方式进行计时。<br/>
提示：<br/>
系统时钟为10M有源晶振提供，可通过分频获得1Hz的显示计数频率。
熟悉数码管的控制逻辑；可通过调节数码管单次点亮的时间来加深对时序控制的理解；两个数码管采用轮流点亮的方法，利用人眼的视觉残留效果，从而达到“同时”点亮两个数码管的目的。注意：每个数码管要轮流点亮，不能出现闪烁现象！

```
module counter(
  input direction,
  input clk,
  output [1:0] select,
  output [6:0] digital
);
reg [12:0] smalldiv;
reg [7:0] bigdiv;
reg [6:0] digital;
reg [1:0] select;
reg [3:0] num [1:0];

always@(posedge clk)
begin
  if(smalldiv == 13'D4999)
    begin
    smalldiv <= 13'D0;
    if(bigdiv == 8'D199)
      begin
      bigdiv <= 8'D0;
      if(select == 2'B10)
        begin
        select <= 2'B01;
        end
      else
        begin
        select <= 2'B10;
        end
        if(direction)
          begin
          if(num[0] == 4'D9)
            begin
            num[0] <= 4'D0;
            if(num[1] == 4'D9)
              num[1] <= 4'D0;
            else
              num[1] <= num[1] + 4'D1;
            end
          else
            num[0] <= num[0] + 4'D1;
          end
        else
          begin
          if(num[0] == 4'D0)
            begin
            num[0] <= 4'D9;
            if(num[1] == 4'D0)
              num[1] <= 4'D9;
            else
              num[1] <= num[1] - 4'D1;
            end
          else
            num[0] <= num[0] - 4'D1;
          end
        end
    else
      bigdiv = bigdiv + 8'D1;
    end
  else
    smalldiv = smalldiv + 13'D1;
  if(select == 2'B10)
  begin
    case(num[0])
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
  else
  begin
    case(num[1])
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
end
endmodule

```
