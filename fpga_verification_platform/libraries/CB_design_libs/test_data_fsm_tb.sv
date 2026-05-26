`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 08/28/2025 12:43:39 PM
// Design Name: 
// Module Name: test_data_fsm_tb
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


module test_data_fsm_tb();

// Clock and reset signals
logic main_clk_125M_tb     = 0;
logic clk_125M_tb          = 0;
logic clk_64M_tb           = 0;
logic reset_n              = 0;

// Constants
localparam int c_clkFreq        = 64000000;                    // Freq in Hz
localparam time c_clkPeriod     = 1000000000ns / c_clkFreq;    // Clock Period
localparam time c_clkHalfPer    = c_clkPeriod / 2;             // Clock Half Period
localparam int trigger_Freq     = 1000000;                     // Freq in Hz
localparam time trigger_Period  = 1000000000ns / trigger_Freq; // Clock Period
localparam time trigger_HalfPer = trigger_Period / 2;          // Clock Half Period

localparam int CLK_FREQ   = 125_000_000;
localparam int BAUD_RATE  = 921_600;
localparam int OS_RATE    = 16;
localparam int D_WIDTH    = 8;
localparam int PARITY     = 0;
localparam bit PARITY_EO  = 1'b0;

// UART signals
logic rx;
logic tx;
logic tx_ena_s      = 0;
logic [D_WIDTH-1:0] tx_data_s;
logic rx_busy_s;
logic rx_error_s;
logic [D_WIDTH-1:0] rx_data_s;
logic tx_busy_s;

// Message handling
string command_message = "phv_s_a1";
reg[0:1][7:0] data_message_frequency = '{8'h07, 8'hD0};
reg[0:4][7:0] data_message_duty = '{8'h0F, 8'hA0, 8'h7D, 8'h03, 8'hE8};
logic message_change = 0;
byte xmt_char;
byte rcv_char;

// FSM signals
logic test_mode_active_tb = 1;
logic trigger_current_processing = 0;
logic [35:0] current_adc_spi = 36'h800800800;
logic ovc_release_a1 = 0;
logic ovc_event_a1 = 0;
logic [5:0] ovc_status_a1 = 6'b000000;
logic [2:0] pwm_uvw_top_tb;
logic [2:0] pwm_uvw_bot_tb;

// ADC current arrays
typedef logic [11:0] current_type [0:29];
current_type current_U = '{12'hF68, 12'hee0, 12'he58, 12'hdd0, 12'hd48, 12'hcc0, 12'hc38, 12'hbb0, 12'hb28,
                          12'haa0, 12'ha18, 12'h990, 12'h908, 12'h880, 12'h7f8, 12'h770, 12'h6e8, 12'h660, 12'h5d8, 12'h550,
                          12'h4c8, 12'h440, 12'h3b8, 12'h330, 12'h2a8, 12'h220, 12'h198, 12'h110, 12'h088, 12'h000};

current_type current_V = '{12'h800, 12'h800, 12'h800, 12'h800, 12'h800, 12'h800, 12'h800, 12'h800, 12'h104, 12'h2ff,
                          12'ha64, 12'ha64, 12'ha64, 12'h9ff, 12'h9d1, 12'hdd1, 12'hfeb, 12'hefb, 12'ha55, 12'ha55,
                          12'ha55, 12'ha55, 12'ha55, 12'ha55, 12'ha55, 12'ha55, 12'hdd1, 12'h9ff, 12'h9d1, 12'h800};

current_type current_W = '{12'h800, 12'h800, 12'h800, 12'h800, 12'h800, 12'h800, 12'h800, 12'h800, 12'h800, 12'h800,
                          12'hdd1, 12'hdd1, 12'h104, 12'h104, 12'h2ff, 12'h2ff, 12'h2ff, 12'h2ff, 12'hbbb, 12'haaa,
                          12'h104, 12'h22f, 12'h9ff, 12'haa5, 12'haa5, 12'hfeb, 12'hdd1, 12'hdd1, 12'ha55, 12'h800};
						  

initial begin
  @(posedge clk_125M_tb);
  reset_n = 1;
  forever @(posedge clk_125M_tb); // Wartet unbegrenzt
end


initial begin
  forever #4 main_clk_125M_tb = ~main_clk_125M_tb;
end


initial begin
  forever begin
    trigger_current_processing = 0;
    #trigger_Period;
    @(posedge clk_64M_tb);
    trigger_current_processing = 1;
    @(posedge clk_64M_tb);
    trigger_current_processing = 0;
  end
end



initial begin
  repeat (20) begin
      for (int k = 0; k < 30; k++) begin
        @(posedge trigger_current_processing);
        current_adc_spi[11:0]   = current_U[k];
        current_adc_spi[23:12]  = current_V[k];
        current_adc_spi[35:24]  = current_W[k];
      end
  end
end



always_ff @(posedge clk_64M_tb) begin
  if (ovc_event_a1 == 1'b1 && ovc_status_a1 == 6'b000000)
    ovc_release_a1 <= 1'b1;
  else
    ovc_release_a1 <= 1'b0;
end


test_data_fsm_sim_wrapper DUT_FSM (
  .clk_in              (main_clk_125M_tb),
  .clk_125M            (clk_125M_tb),
  .clk_64M             (clk_64M_tb),
  .test_mode_active    (1'b1),
  .pwm_uvw_top         (pwm_uvw_top_tb),
  .pwm_uvw_bot         (pwm_uvw_bot_tb),
  .phu_adc_a1          (current_adc_spi[11:0]),
  .phv_adc_a1          (current_adc_spi[23:12]),
  .phw_adc_a1          (current_adc_spi[35:24]),
  .phx_data_ready_a1   (trigger_current_processing),
  .ovc_release_a1      (ovc_release_a1),
  .ovc_event_a1        (ovc_event_a1),
  .ovc_status_a1       (ovc_status_a1),
  .pl_uart_rx          (rx),
  .pl_uart_tx          (tx),
  .rst_n_in            (reset_n)
);


uart #(
  .CLK_FREQ  (CLK_FREQ),
  .BAUD_RATE (BAUD_RATE),
  .OS_RATE   (OS_RATE),
  .D_WIDTH   (D_WIDTH),
  .PARITY    (PARITY),
  .PARITY_EO (PARITY_EO)
) STIMULI_UART_inst (
  .clk      (clk_125M_tb),
  .reset_n  (reset_n),
  .tx_ena   (tx_ena_s),
  .tx_data  (tx_data_s),
  .rx       (tx),
  .rx_busy  (rx_busy_s),
  .rx_error (rx_error_s),
  .rx_data  (rx_data_s),
  .tx_busy  (tx_busy_s),
  .tx       (rx)
);


initial begin
  command_message = "pwm_f_a1";
  #150us;
  command_message = "pwm_d_a1";
  #200us;
  command_message = "pwm_f_a1";
  data_message_frequency = '{8'h0F, 8'hA0};
  #150us;
  command_message = "pwm_d_a1";
  data_message_duty = '{8'h1F, 8'h40, 8'hFA, 8'h07, 8'hD0};
  #500us;
  command_message = "pwm_f_a1";
  data_message_frequency = '{8'h1F, 8'h40};
  #150us;
  command_message = "pwm_d_a1";
  data_message_duty = '{8'h3E, 8'h81, 8'hF4, 8'h0F, 8'hA0};
end


initial begin
  repeat (3) begin
      for (int i = 0; i < command_message.len(); i++) begin
        wait (tx_busy_s == 0);
        @(posedge clk_125M_tb);
            tx_data_s = command_message[i];
            xmt_char = command_message[i];
            tx_ena_s = 1;
        @(posedge clk_125M_tb);
        @(posedge clk_125M_tb);
        tx_ena_s = 0;
      end
      #40us;
      for (int i = 0; i < $size(data_message_frequency); i++) begin
        wait (tx_busy_s == 0);
        @(posedge clk_125M_tb);
            tx_data_s = data_message_frequency[i];
            xmt_char = data_message_frequency[i];
            tx_ena_s = 1;
        @(posedge clk_125M_tb);
        @(posedge clk_125M_tb);
        tx_ena_s = 0;
      end 
      #40us;
      for (int i = 0; i < command_message.len(); i++) begin
        wait (tx_busy_s == 0);
        @(posedge clk_125M_tb);
            tx_data_s = command_message[i];
            xmt_char = command_message[i];
            tx_ena_s = 1;
        @(posedge clk_125M_tb);
        @(posedge clk_125M_tb);
        tx_ena_s = 0;
      end
      #40us;
      for (int i = 0; i < $size(data_message_duty); i++) begin
        wait (tx_busy_s == 0);
        @(posedge clk_125M_tb);
            tx_data_s = data_message_duty[i];
            xmt_char = data_message_duty[i];
            tx_ena_s = 1;
        @(posedge clk_125M_tb);
        @(posedge clk_125M_tb);
        tx_ena_s = 0;
      end
      #40us;
  end
end


initial begin
  wait (rx_busy_s == 1);
  for (int i = 0; i < command_message.len(); i++) begin
    wait (rx_busy_s == 0);
    @(posedge clk_125M_tb);
    rcv_char = byte'(rx_data_s);
  end
end


endmodule
