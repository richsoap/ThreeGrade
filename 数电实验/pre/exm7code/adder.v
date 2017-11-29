`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/29 22:40:09
// Design Name: 
// Module Name: adder
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


module adder(
    input button,
    output [1:0] C
    );
    
    reg [1:0]C;
    
    always@(posedge button)
    begin
        C[0] <= ~C[0];
        C[1] <= (~C[1]&C[0])|(~C[0]&C[1]);
    end
        
endmodule
