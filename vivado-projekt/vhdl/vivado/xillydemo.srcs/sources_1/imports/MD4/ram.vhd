-- This core is pending a full rewrite. Documentation will be added along with that.
-- This file is currently only provided to not break cores that depend on it.

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity ram is
    generic(
        addr_width : natural := 9;
        data_width : natural := 8
    );
    port(
        clk       : in  std_logic;
        addra     : in  std_logic_vector(addr_width - 1 downto 0);
        write_ena : in  std_logic;
        dina      : in  std_logic_vector(data_width - 1 downto 0);
        douta     : out std_logic_vector(data_width - 1 downto 0); --@suppress SPS4 : There is no reset available on the DP ram

        addrb     : in  std_logic_vector(addr_width - 1 downto 0);
        write_enb : in  std_logic;
        dinb      : in  std_logic_vector(data_width - 1 downto 0);
        doutb     : out std_logic_vector(data_width - 1 downto 0) --@suppress SPS4 : There is no reset available on the DP ram
    );
end ram;

architecture rtl of ram is
    type mem_type is array ((2 ** addr_width) - 1 downto 0) of std_logic_vector(data_width - 1 downto 0);
    signal mem              : mem_type; --@suppress SPS4 : There is no reset available on the DP ram
    attribute syn_ramstyle  : string;
    attribute syn_ramstyle2 : string;
    attribute syn_ramstyle of mem : signal is "no_rw_check";
    attribute syn_ramstyle2 of mem : signal is "block_ram";
begin

    -- perform write and read operations on ram
    ram_access : process(clk)
    begin
        if rising_edge(clk) then
            if (write_enb = '1') then
                mem(to_integer(unsigned((addrb)))) <= dinb;
                -- Using address bus b.
            end if;
            if (write_ena = '1') then
                mem(to_integer(unsigned((addra)))) <= dina;
                --       Using address bus a.
            end if;

            douta <= mem(to_integer(unsigned((addra))));
            doutb <= mem(to_integer(unsigned((addrb))));
        end if;
    end process ram_access;
end rtl;
