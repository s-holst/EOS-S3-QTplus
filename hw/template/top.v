`default_nettype none

module top ( // IO connections to pads. Uncomment matching lines in io.pcf and configure IOMUX appropriately. 
        input pad6, // USR button
        output pad18 // blue LED
    );
    
    wire clk0, rst0, clk1, rst1;
    wire sys_clk0, sys_rst0, sys_clk1, sys_rst1;

    wire [16:0] i_wb_adr;
    wire [31:0] i_wb_dat;
    wire i_wb_rst, i_wb_cyc, i_wb_stb, i_wb_wen;
    wire pkfb0_push;

    reg o_wb_ack;
    reg [31:0] o_wb_dat;

    // Connections to the EOS S3 platform apart from pads defined above.
    qlal4s3b_cell_macro s3io (
        .Sys_Clk0     ( sys_clk0 ), // output | C16, configured to 12MHz by software
        .Sys_Clk0_Rst ( sys_rst0 ), // output
        .Sys_Clk1     ( sys_clk1 ), // output | C21, configured to 1MHz by software
        .Sys_Clk1_Rst ( sys_rst1 ), // output

        .Device_ID ( 16'hF01D ), // input[15:0] | sets MISC->FB_DESIGN_ID

        .WBs_ADR      ( i_wb_adr ), // output[16:0] | Address Bus
        .WBs_CYC      ( i_wb_cyc ), // output       | Cycle Chip Select
        .WBs_BYTE_STB (          ), // output[3:0]  | Byte Select
        .WBs_WE       ( i_wb_wen ), // output       | Write Enable
        .WBs_RD       (          ), // output       | Read Enable
        .WBs_STB      ( i_wb_stb ), // output       | Strobe Signal
        .WBs_WR_DAT   ( i_wb_dat ), // output[31:0] | Write Data Bus
        .WB_CLK       ( clk1     ), // input        | C40 driven by FPGA, 10MHz max.
        .WB_RST       ( i_wb_rst ), // output       | Reset driven by CRU->FB_MISC_SW_RST_CTL[0]
        .WBs_RD_DAT   ( o_wb_dat ), // input[31:0]  | Read Data Bus
        .WBs_ACK      ( o_wb_ack ), // input        | Transfer Cycle Ack.

        .SDMA_Req    ( 0 ), // input[3:0]
        .SDMA_Sreq   ( 0 ), // input[3:0]
        .SDMA_Done   (   ), // output[3:0]
        .SDMA_Active (   ), // output[3:0]
        
        .FB_msg_out ( 0 ), // input[3:0]
        .FB_Int_Clr ( 0 ), // input[7:0]
        .FB_Start   (   ), // output
        .FB_Busy    ( 0 ), // input
        
        .Sys_PKfb_Clk    ( clk0 ), // input    | C41 driven by FPGA, 20MHz max. (or 10MHz? [TRM page 341])
        .Sys_PKfb_Rst    (   ), // output      | Reset driven by CRU->FB_MISC_SW_RST_CTL[1]
        .FB_PKfbData     ( counter ), // input[31:0]
        .FB_PKfbPush     ( { 3'b0, pkfb0_push } ), // input[3:0]  | always @(negedge Sys_PKfb_Clk) if 1, then push FB_PKfbData to FIFO x.
        .FB_PKfbSOF      ( 0 ), // input
        .FB_PKfbEOF      ( 0 ), // input
        .FB_PKfbOverflow (   ), // output

        .Sensor_Int ( ), // output[7:0]
        .TimeStamp  ( ), // output[23:0]
        
        .Sys_Pclk      (   ), // output       | C02
        .Sys_Pclk_Rst  (   ), // output
        .Sys_PSel      ( 0 ), // input
        .SPIm_Paddr    ( 0 ), // input[15:0]
        .SPIm_PEnable  ( 0 ), // input
        .SPIm_PWrite   ( 0 ), // input
        .SPIm_PWdata   ( 0 ), // input[31:0]
        .SPIm_Prdata   (   ), // output[31:0]
        .SPIm_PReady   (   ), // output
        .SPIm_PSlvErr  (   ), // output
        
        // Unused signals (FBIO connections are handled by io.pcf):
        .FBIO_In         (   ), // output[13:0]
        .FBIO_In_En      (   ), // input[13:0]
        .FBIO_Out        (   ), // input[13:0]
        .FBIO_Out_En     (   ), // input[13:0]
        .SFBIO           (   ), // inout[13:0]
        .Device_ID_6S    ( 0 ), // input
        .Device_ID_4S    ( 0 ), // input
        .SPIm_PWdata_26S ( 0 ), // input
        .SPIm_PWdata_24S ( 0 ), // input
        .SPIm_PWdata_14S ( 0 ), // input
        .SPIm_PWdata_11S ( 0 ), // input
        .SPIm_PWdata_0S  ( 0 ), // input
        .SPIm_Paddr_8S   ( 0 ), // input
        .SPIm_Paddr_6S   ( 0 ), // input
        .FB_PKfbPush_1S  ( 0 ), // input
        .FB_PKfbData_31S ( 0 ), // input
        .FB_PKfbData_21S ( 0 ), // input
        .FB_PKfbData_19S ( 0 ), // input
        .FB_PKfbData_9S  ( 0 ), // input
        .FB_PKfbData_6S  ( 0 ), // input
        .Sys_PKfb_ClkS   ( 0 ), // input
        .FB_BusyS        ( 0 ), // input
        .WB_CLKS         ( 0 )  // input
    );

    // Clocks should be buffered.
    gclkbuff clk0_buff ( .A(sys_clk0), .Z(clk0));
    gclkbuff rst0_buff ( .A(sys_rst0), .Z(rst0));
    gclkbuff clk1_buff ( .A(sys_clk1), .Z(clk1));
    gclkbuff rst1_buff ( .A(sys_rst1), .Z(rst1));
    
    reg [31:0] lfsr_state;
    reg [31:0] brightness;
    reg [31:0] increment;

    // Always acknowledge on WB.
    always @(posedge clk1) o_wb_ack <= (i_wb_rst) ? 0 : (i_wb_cyc & i_wb_stb);

    // Handle WB read requests.
    always @(posedge clk1) begin
        case(i_wb_adr[3:2])
            2'b00 : o_wb_dat <= increment;
            2'b01 : o_wb_dat <= brightness;
            2'b10 : o_wb_dat <= lfsr_state;
            default : o_wb_dat <= 32'hdeadbeef;
        endcase
    end

    // Main logic and handle WB write requests.
    always @(posedge clk1) begin
        if (rst1) begin
            increment <= 1 << 12;
            brightness <= 0;
            lfsr_state <= -1;
        end else if (i_wb_stb & i_wb_wen) begin
            case(i_wb_adr[3:2])
                2'b00 : increment <= i_wb_dat;
                2'b01 : brightness <= i_wb_dat;
                2'b10 : lfsr_state <= i_wb_dat;
            endcase
        end else begin
            lfsr_state <= (lfsr_state << 1) ^ ((lfsr_state[31]) ? 32'h8345e9 : 0);
            brightness <= brightness + increment;
        end
    end

    // Sets LED to a certain brightness; USR button inverts.
    assign pad18 = (lfsr_state < brightness) ^ ~pad6;

    // A 12 MHz 32-bit up-counter whose value gets pushed to FIFO 0 on usr button state change.
    reg [31:0] counter;
    reg pad6_buffered, pad6_previous;

    always @(posedge clk0) begin
        if (rst0) begin
            counter <= 0;
            pad6_buffered <= 1;
            pad6_previous <= 1;
        end else begin
            counter <= counter + 1;
            pad6_buffered <= pad6;
            pad6_previous <= pad6_buffered;
        end
    end

    assign pkfb0_push = pad6_buffered ^ pad6_previous;

endmodule
