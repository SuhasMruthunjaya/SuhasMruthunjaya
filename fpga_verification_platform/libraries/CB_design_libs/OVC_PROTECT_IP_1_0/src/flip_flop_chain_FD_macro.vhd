--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
--! @file
--! @brief      Module: flip_flop_chain
--! @par        Tools:
--!             - Vivado 2014.4
--!             - ISE 14.3
--!             - ISim 14.3
--!             - Incisive Enterprise Simulator 14.10
--------------------------------------------------------------------------------
--! @file
--! @author     Johannes Kempf <johannes.kempf@schneider-electric.com>
--! @since      2014-04-04
--------------------------------------------------------------------------------
--! @file
--! @details    Description:
--! Generic flip-flop chain.
--------------------------------------------------------------------------------
--! @file
--! @copyright  Copyright (c) 2014 Schneider Electric Automation GmbH, Germany.
--------------------------------------------------------------------------------
-- SVN information section start (do not manually edit this section)
--------------------------------------------------------------------------------
--! @file
--! SVN information about last modifications,
--! for full history see log entries in SVN or ../doc/.
--! $URL: https://sources-svn.eur.gad.schneider-electric.com/svn/he-fpga/FPGA/trunk/design_flow/60_libraries/sync_module/work/rtl/flip_flop_chain_FD_macro.vhd $
--! $Revision: 7975 $
--! $Author: mstollberger $
--! $Date: 2019-01-23 17:37:17 +0100 (Mi, 23 Jan 2019) $
--------------------------------------------------------------------------------
-- SVN information section end
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------


--! Using IEEE library.
library ieee;
--! Use 9-level logic.
use ieee.STD_LOGIC_1164.all;
--! Using Xilinx Macros
Library UNISIM;
use UNISIM.vcomponents.all;


--! @brief Generic flip-flop chain.
--! @details
--! This module simply implements a shift register.
--! @note
--! The flip-flops have to be packed closely together and shouldn't be optimized away
--! if this shift register is used to handle metastability issues on clock domain crossing.
--! Therefore, special synthesis constraints needs to be applied.
entity flip_flop_chain_FD_macro is
  generic (
    INIT_VALUE  : STD_LOGIC;   --! Initial value of synchronization flip-flops ('0' / '1' )
    FF_STAGES   : POSITIVE  --! Number of chained flip-flops.
  );
  port (
    clk_i   : in  STD_LOGIC; --! Clock.
    chain_i : in  STD_LOGIC; --! Input for flip-flop chain.
    chain_o : out STD_LOGIC  --! Output of flip-flop chain.
  );
end entity flip_flop_chain_FD_macro;

--! @brief Behavioral description using synthesizable VHDL syntax.
architecture rtl of flip_flop_chain_FD_macro is
  
  signal sync_chain : STD_LOGIC_VECTOR(FF_STAGES - 1 downto 0) := (others => (INIT_VALUE));  --! Synchronization chain.
  
  --! @brief Last stage of flip-flop chain.
  alias chain_tail  : STD_LOGIC is sync_chain(sync_chain'high);
  
  attribute ASYNC_REG : string;
  attribute KEEP      : string;
  --! Set first reg as asynchronous register to force the placer to keep iming short
  attribute ASYNC_REG of FIRST_FF_INST: label  is "TRUE";
  --! Avoid optimisation of the filpflop signals
  attribute KEEP      of sync_chain:    signal is "TRUE";

begin
  --! @brief Avoids warning about null range by generating a single flip-flop.
  FIRST_FF_INST : FD
  port map (
    Q => sync_chain(0),
    C => clk_i,
    D => chain_i);
 
  --! @brief Generates a shift register.
  shift_register: if sync_chain'length > 1 generate
  begin    
    flip_flop_chain_gen: for I in sync_chain'high downto 1 generate
      --! Set chain regs as asynchronous register to force the placer to keep iming short
      attribute ASYNC_REG of FD_CHAIN_INST: label is "TRUE";
    begin
      FD_CHAIN_INST : FD
      port map (
        Q => sync_chain(I),
        C => clk_i,
        D => sync_chain(I-1));
                
    end generate flip_flop_chain_gen; 
  end generate shift_register;
  
  -- output last stage
  chain_o <= chain_tail;
end architecture rtl;
