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
    bigdiv <= bigdiv + 32'D1
    smalldiv <= 32'D0
    if(select == 2'B01)
      select <= 2'B10
    else
      select <= 2'B01
    end
  else
    smalldiv <= smalldiv + 32'D1

  if(bigdiv >= 32'D200)
    begin
    bigdiv <= 32'D0
    if(direction)
      begin
      if(num[0] < 4'D9 & num[0] >= 4'D0)
        num[0] <= num[0] + 4'D1
      else
        begin
        num[0] <= 4'D0
        if(num[1] >= 4'D0 & num[1] < 4'D9)
          num[1] <= num[1] + 4'D1
        else
          num[1] <= 4'D0
        end
      end
      else
      begin
      if(num[0] <= 4'D9 & num[0] > 4'D0)
        num[0] <= num[0] - 4'D1
      else
        begin
        num[0] <= 4'D9
        if(num[1] <= 4'D9 & num[1] > 4'D0)
          num[1] <= num[1] - 4'D1
        else
          num[1] <= 4'D9
      end
    end

    if(select == 2'B01)
      buffer <= num[0]
    else
      buffer <= num[1]

    case(buffer)
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
