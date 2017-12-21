<<<<<<< HEAD
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
=======
module counter(
  input direction;
  input clk;
  output [1:0] select;
  output [6:0] digital;
);
reg [12:0] smalldiv;
reg [7:0] bigdiv;
reg [6:0] digital;
reg [1:0] select;
reg [3:0] number [1:0];

wire [6:0] tempdital[0:1];

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
      bigdiv = bigdiv + 4'D1;
    end
  else
    smalldiv = smalldiv + 13'D1;
  if(select == 2'B10)
    digital <= tempdital[0];
  else
    digital <= tempdital[1];
end

tempdital[0] =
>>>>>>> 830aba0cc8f023f79162cba046a591e221ad8d5a
