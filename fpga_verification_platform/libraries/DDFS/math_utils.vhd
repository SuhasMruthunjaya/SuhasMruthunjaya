----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/15/2025 11:02:49 AM
-- Design Name: 
-- Module Name: math_utils - 
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

package math_utils is
  function clog2(n : natural) return natural;
end package;

package body math_utils is
  function clog2(n : natural) return natural is
    variable result : natural := 0;
    variable value  : natural := n - 1;
  begin
    while value > 0 loop
      value := value / 2;
      result := result + 1;
    end loop;
    return result;
  end function;
end package body;

