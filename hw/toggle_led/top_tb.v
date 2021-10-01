`timescale 10ns /10ps
`define GSIM 1

module top_tb;
    reg clk;
    reg reset;
    wire led;
    reg led_exp;

    top DUT (.clk(clk), .reset(reset), .led(led));

    always @(posedge clk)
        led_exp <= ~led_exp;

    initial begin
        clk = 0;
        reset = 1;
        #40 reset = 0;
        led_exp = 0;
        #100 $finish;
    end

    always
        #15 clk = !clk;

    always @(posedge clk)
        if (led_exp !== led) begin
            $display("Mismatch at time : %d", $time);
            $display("  Expected : %d", led_exp);
            $display("  Actual   : %d", led);
            $fatal;
        end

    initial begin
        $dumpfile("top_tb.vcd");
        $dumpvars(0, top_tb);
        $display("\t\ttime,\tclk,\treset,\tled");
        $monitor("%d,\t%b,\t%b,\t%b", $time, clk, reset, led);
    end
  
endmodule
