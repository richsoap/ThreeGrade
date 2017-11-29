`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/29 22:40:09
// Design Name: 
// Module Name: feedback
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


module feedback(
    input [3:0] Q,
    input [1:0] C,
    output D
    );
    
    wire [3:0]inD;
    
    assign inD[0]=~(Q[0]|Q[1]|Q[2]);
    assign inD[1]=~(Q[3])|(Q[3]&~Q[2]&~Q[1]&Q[0]);
    assign inD[2]=~(Q[3])|(Q[3]&Q[2]&~Q[1]&~Q[0]);
    
    assign D=(inD[0]&~C[0]&~C[1])|(inD[1]&C[0]&~C[1])|(inD[2]&~C[0]&C[1])|(inD[3]&C[0]&C[1]);
    
endmodule
