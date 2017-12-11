`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2017/11/29 22:40:09
// Design Name:
// Module Name: top
// Project Name:
// Target Devices:
// Tool Versions:
// Description:
//
// Dependencies:
//
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
//
//////////////////////////////////////////////////////////////////////////////////


module top_adder(
    input clk,
    input button,
    output [1:0] C,
    output [3:0] Q
    );
    reg [3:0]Q;
    reg [1:0]C;
    reg before;

    wire D;
    wire [3:0]inD;
    wire [3:0]tempQ;
    wire [1:0]tempC;

    always@(posedge clk)
    begin
        if(~before&button)
          C[1:0]<=tempC[1:0];
        else
          Q[3:0]<=tempQ[3:0];
        before<=button;
    end

    assign inD[0]=~(Q[0]|Q[1]|Q[2]);
    assign inD[1]=~(Q[3])|(Q[3]&~Q[2]&~Q[1]&Q[0]);
    assign inD[2]=~(Q[3])|(Q[3]&Q[2]&~Q[1]&~Q[0]);
    assign inD[3]=(Q[0]^Q[3])|(~Q[0]&~Q[1]&~Q[2]&~Q[3]);
    assign D=(inD[0]&~C[0]&~C[1])|(inD[1]&C[0]&~C[1])|(inD[2]&~C[0]&C[1])|(inD[3]&C[0]&C[1]);

    assign tempQ[0]=D;
    assign tempQ[1]=Q[0];
    assign tempQ[2]=Q[1];
    assign tempQ[3]=Q[2];

    assign tempC[0]=~C[0];
    assign tempC[1]=C[0]^C[1];

    endmodule
