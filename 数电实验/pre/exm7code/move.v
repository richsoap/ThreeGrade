`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/29 22:40:09
// Design Name: 
// Module Name: move
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


module move(
    input D,
    input clk,
    output [3:0] Q
    );
    
    reg [3:0]Q;
    
    always@(posedge clk)
    begin
        Q[0]<=D;
        Q[1]<=Q[0];
        Q[2]<=Q[1];
        Q[3]<=Q[2];
    end
    
endmodule
