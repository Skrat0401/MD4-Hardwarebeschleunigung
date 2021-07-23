library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Testbench_for_FIFO is
end entity Testbench_for_FIFO;

architecture RTL of Testbench_for_FIFO is
    component xillydemo
        port(
            bus_clk              : IN  std_logic;
            reset_32             : IN  std_logic;
            user_w_write_32_data : IN  std_logic_vector(31 DOWNTO 0);
            user_w_write_32_wren : IN  std_logic;
            user_r_read_32_rden  : IN  std_logic;
            user_r_read_32_data  : OUT std_logic_vector(31 DOWNTO 0)
        );
    end component xillydemo;
    signal T_bus_clk              : std_logic;
    signal T_reset_32             : std_logic;
    signal T_user_w_write_32_data : std_logic_vector(31 DOWNTO 0);
    signal T_user_w_write_32_wren : std_logic;
    signal T_user_r_read_32_rden  : std_logic;
    signal T_user_r_read_32_data  : std_logic_vector(31 DOWNTO 0);
    type arr is array (0 to 47) of std_logic_vector(31 downto 0);

    constant test_a : arr := (
        x"00008061",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000008",
        x"00000000",
                x"00008061",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000008",
        x"00000000",
                x"00008061",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000000",
        x"00000008",
        x"00000000");

begin
    DUT : component xillydemo
        port map(
            bus_clk              => T_bus_clk,
            reset_32             => T_reset_32,
            user_w_write_32_data => T_user_w_write_32_data,
            user_w_write_32_wren => T_user_w_write_32_wren,
            user_r_read_32_rden  => T_user_r_read_32_rden,
            user_r_read_32_data  => T_user_r_read_32_data
        );
        
        
    test : process is
    begin
        wait for 50 ns;
        T_user_w_write_32_wren <= '1';
        T_user_r_read_32_rden <= '1';
        --wait until rising_edge(T_bus_clk);
        for i in 0 to 47 loop
            T_user_w_write_32_data <= test_a(i);
            wait until rising_edge(T_bus_clk);
        end loop;
        T_user_w_write_32_wren <= '0';
        wait;
    end process;
    
    
    Reset : process
    begin
        T_reset_32 <= '1';
        wait for 50 ns;
        T_reset_32 <= '0';
        wait;
    end process;
    

    clock_driver : process
        constant period : time := 10 ns;
    begin
        T_bus_clk <= '0';
        wait for period / 2;
        T_bus_clk <= '1';
        wait for period / 2;
    end process clock_driver;

end architecture RTL;
