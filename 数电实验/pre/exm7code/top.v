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

module top(
    input button,
    input clk,
    output [1:0] C,
    output [3:0] Q
    );
    reg [1:0]C;
    reg [3:0]Q;
    
    wire D;
    wire [1:0]tempC;
    wire [3:0]tempQ;
    adder(
        .button(button),
        .C(tempC[1:0])
        );
    feedback(
            .Q(Q[3:0]),
            .C(C[1:0]),
            .D(D)
            );
     move(
      .D(D),
      .clk(clk),
      .Q(tempQ[3:0])
     );
     
   always@(*)
      begin
        C[1:0]<=tempC[1:0];
        Q[3:0]<=tempQ[3:0];
      end
     
    
    
endmodule
