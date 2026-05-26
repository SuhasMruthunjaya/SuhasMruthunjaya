`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/20/2025 01:36:59 PM
// Design Name: 
// Module Name: ovc_protect_ip_tb
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
import axi_vip_pkg::*;
import ovc_protect_axi_ovc_protect_0_pkg::*;

xil_axi_resp_t 	resp;
bit[31:0]  addr, data, base_addr = 32'h44A0_0000;

module ovc_protect_ip_tb();

 // Clock signal
  bit               axi_clock;
  bit               ovc_clock;                        

  // Reset signal
  bit               axi_reset;
  bit               ovc_reset;
  
  // other signals
  bit               trigger_ovc_tb;
  bit               trigger_ovc_tb_sync;
  bit               ovc_event_tb;
  bit               ovc_release_tb;
  bit[5:0]          status_tb;
  bit[35:0]         current_adc_spi = 36'h800800800;
  
  bit[11:0]         ovc_low_limit_p = 12'hdd1;
  bit[11:0]         ovc_low_limit_n = 12'h22f;
  bit[11:0]         ovc_time_tb = 12'h280;
  bit[29:0][11:0]   current_U = {12'h104, 12'hf98, 12'hf98, 12'hf98 ,12'hf98 ,12'hf98, 12'hf98, 12'hf98,12'hf98,
                                         12'hf98, 12'hf98, 12'hefb, 12'hdff, 12'ha64, 12'ha64, 12'ha64, 12'ha64, 12'h9ff,12'h9d1, 12'hdd1,
                                         12'hdd1, 12'hdd1, 12'hdd1,12'hdd1, 12'hdd1, 12'ha64, 12'ha64, 12'h9ff, 12'h9d1, 12'h800};
  bit[29:0][11:0]   current_V = {12'h800, 12'h800, 12'h800, 12'h800, 12'h800, 12'h800, 12'h800, 12'h800, 12'h104, 12'h2ff,
                                         12'ha64, 12'ha64, 12'ha64, 12'h9ff, 12'h9d1, 12'hdd1, 12'hfeb, 12'hefb, 12'ha55, 12'ha55,
                                         12'ha55, 12'ha55, 12'ha55, 12'ha55, 12'ha55, 12'ha55, 12'hdd1, 12'h9ff, 12'h9d1, 12'h800};    
  bit[29:0][11:0]   current_W = {12'h104, 12'hf98, 12'hf98, 12'hf98 ,12'hf98 ,12'hf98, 12'hf98, 12'hf98,12'hf98,
                                         12'hf98, 12'hf98, 12'hefb, 12'hdff, 12'ha64, 12'ha64, 12'ha64, 12'ha64, 12'h9ff,12'h9d1, 12'hdd1,
                                         12'hdd1, 12'hdd1, 12'hdd1,12'hdd1, 12'hdd1, 12'ha64, 12'ha64, 12'h9ff, 12'h9d1, 12'h800};    
   
   integer k = 0;
                                         
   // instantiate DUT
   ovc_protect_wrapper DUT
       (.aclk(axi_clock),
        .aresetn(axi_reset),
        .current_raw_adc(current_adc_spi),
        .ovc_clk(ovc_clock),
        .ovc_event(ovc_event_tb),
        .ovc_release(ovc_release_tb),
        .ovc_reset_n(ovc_reset),
        .ovc_status(status_tb),
        .trigger_ovc(trigger_ovc_tb_sync));       
        
    initial begin
        axi_reset <= 1'b0;
        repeat (5) @(negedge axi_clock);
        axi_reset <= 1'b1;
    end   
    
    initial begin
        ovc_reset <= 1'b0;
        repeat (5) @(negedge ovc_clock);
        ovc_reset <= 1'b1;
    end  
    
    always #4 axi_clock <= ~axi_clock; 
    always #7.8125 ovc_clock <= ~ovc_clock; 
                                                                                                                 
    // declare the agent for the master VIP
    ovc_protect_axi_ovc_protect_0_mst_t      master_agent;     
    
    // trigger generation
    initial begin
        trigger_ovc_tb = 0;
        while(1) begin
            #500;
            trigger_ovc_tb = 1;
            
            #15.625;
            trigger_ovc_tb = 0;
            
            #500ns;
        end
        
    end
    
    initial begin
        trigger_ovc_tb_sync <= #15.625 trigger_ovc_tb;
    end
    
    initial begin 
        for (k = 0; k<30; k++) begin
            @(posedge trigger_ovc_tb) 
            current_adc_spi[11:0]  <= current_U[k];
            current_adc_spi[23:12] <= current_V[k];
            current_adc_spi[35:24] <= current_W[k];
        end
    end    
    
    always_ff @(posedge ovc_clock) begin 
        if (ovc_event_tb == 1'b1 && status_tb == 6'b000000) begin
            ovc_release_tb <= 1'b1;
        end else begin
            ovc_release_tb <= 1'b0;
        end
    end
    
    initial begin
    
        master_agent = new("master vip agent", DUT.ovc_protect_i.axi_ovc_protect.inst.IF); 
        // start the clock
        master_agent.start_master();   
        
                // read out IP Core ID
        # 200ns
        addr = 32'h00000000;
        master_agent.AXI4LITE_READ_BURST(base_addr + addr,0,data,resp);
        
        // read out IP Core version
        # 200ns
        addr = 32'h00000004;
        master_agent.AXI4LITE_READ_BURST(base_addr + addr,0,data,resp);   
        
        // read out current limits
        # 200ns
        addr = 32'h00000008;
        master_agent.AXI4LITE_READ_BURST(base_addr + addr,0,data,resp);
        
        // read out current settings
        # 200ns
        addr = 32'h0000000C;
        master_agent.AXI4LITE_READ_BURST(base_addr + addr,0,data,resp); 
        
        // write out current limits
        # 200ns
        addr = 32'h00000008;
        data = 32'h07CF0651;
        master_agent.AXI4LITE_WRITE_BURST(base_addr + addr,0,data,resp);
        
        // write out current settings
        # 200ns
        addr = 32'h0000000C;
        data = 32'h02810801;
        master_agent.AXI4LITE_WRITE_BURST(base_addr + addr,0,data,resp); 
        
                // read out current limits
        # 200ns
        addr = 32'h00000008;
        master_agent.AXI4LITE_READ_BURST(base_addr + addr,0,data,resp);
        
        // read out current settings
        # 200ns
        addr = 32'h0000000C;
        master_agent.AXI4LITE_READ_BURST(base_addr + addr,0,data,resp); 
        
        // write out current limits
        # 200ns
        addr = 32'h00000008;
        data = 32'h00000000;
        master_agent.AXI4LITE_WRITE_BURST(base_addr + addr,0,data,resp);
        
        // write out current settings
        # 200ns
        addr = 32'h0000000C;
        data = 32'h00000000;
        master_agent.AXI4LITE_WRITE_BURST(base_addr + addr,0,data,resp);       
        
        // write out current limits
        # 200ns
        addr = 32'h00000008;
        data = 32'h00000000;
        master_agent.AXI4LITE_WRITE_BURST(base_addr + addr,0,data,resp);
        
        // write out current settings
        # 200ns
        addr = 32'h0000000C;
        data = 32'h00000000;
        master_agent.AXI4LITE_WRITE_BURST(base_addr + addr,0,data,resp); 
        
        // write out current limits
        # 200ns
        addr = 32'h00000008;
        data = 32'h00000000;
        master_agent.AXI4LITE_WRITE_BURST(base_addr + addr,0,data,resp);
        
        // write out current settings
        # 200ns
        addr = 32'h0000000C;
        data = 32'h00000000;
        master_agent.AXI4LITE_WRITE_BURST(base_addr + addr,0,data,resp);   
        
        // write out current limits
        # 200ns
        addr = 32'h00000008;
        data = 32'h00000000;
        master_agent.AXI4LITE_WRITE_BURST(base_addr + addr,0,data,resp);
        
        // write out current settings
        # 200ns
        addr = 32'h0000000C;
        data = 32'h00000000;
        master_agent.AXI4LITE_WRITE_BURST(base_addr + addr,0,data,resp); 
        
        // write out current limits
        # 200ns
        addr = 32'h00000008;
        data = 32'h00000000;
        master_agent.AXI4LITE_WRITE_BURST(base_addr + addr,0,data,resp);
        
        // write out current settings
        # 200ns
        addr = 32'h0000000C;
        data = 32'h00000000;
        master_agent.AXI4LITE_WRITE_BURST(base_addr + addr,0,data,resp); 
        
        // write out current limits
        # 200ns
        addr = 32'h00000008;
        data = 32'h00000000;
        master_agent.AXI4LITE_WRITE_BURST(base_addr + addr,0,data,resp);
        
        // write out current settings
        # 200ns
        addr = 32'h0000000C;
        data = 32'h00000000;
        master_agent.AXI4LITE_WRITE_BURST(base_addr + addr,0,data,resp); 
         
        // write out current limits
        # 200ns
        addr = 32'h00000008;
        data = 32'h00000000;
        master_agent.AXI4LITE_WRITE_BURST(base_addr + addr,0,data,resp);
        
        // write out current settings
        # 200ns
        addr = 32'h0000000C;
        data = 32'h00000000;
        master_agent.AXI4LITE_WRITE_BURST(base_addr + addr,0,data,resp);      
    end                               

endmodule
