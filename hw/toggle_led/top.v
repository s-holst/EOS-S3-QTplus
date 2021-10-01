module top (clk, reset, led);
    
    input clk;
    input reset;
    output led;
    reg led;                                   

    always @(posedge clk)
        if (reset)
            led <= 0;
        else 
            led <= ~led;

endmodule  
