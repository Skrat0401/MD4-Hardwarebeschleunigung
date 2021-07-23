library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;

entity xillydemo is
    port(
        bus_clk              : IN  std_logic;
        reset_32             : IN  std_logic;
        user_w_write_32_data : IN  std_logic_vector(31 DOWNTO 0);
        user_w_write_32_wren : IN  std_logic;
        user_r_read_32_rden  : IN  std_logic;
        user_r_read_32_data  : OUT std_logic_vector(31 DOWNTO 0)
    );
end xillydemo;

architecture sample_arch of xillydemo is


    component fifo_32x512
        port(
            clk   : IN  std_logic;
            srst  : IN  std_logic;
            din   : IN  std_logic_VECTOR(31 downto 0);
            wr_en : IN  std_logic;
            rd_en : IN  std_logic;
            dout  : OUT std_logic_VECTOR(31 downto 0);
            full  : OUT std_logic;
            empty : OUT std_logic);
    end component;

    component fifo_32x512_1
        port(
            clk   : IN  std_logic;
            srst  : IN  std_logic;
            din   : IN  std_logic_VECTOR(31 downto 0);
            wr_en : IN  std_logic;
            rd_en : IN  std_logic;
            dout  : OUT std_logic_VECTOR(31 downto 0);
            full  : OUT std_logic;
            empty : OUT std_logic);
    end component;

    component top_md4_core
        port(
            clk           : in  std_logic;
            rst           : in  std_logic;
            empty_to_md4  : in  std_logic;
            data_to_md4   : in  std_logic_vector(31 downto 0);
            full_from_md4 : in  std_logic;
            wren_from_md4 : out std_logic;
            rd_en_to_md4  : out std_logic;
            hashout       : out std_logic_vector(31 downto 0);
            rounds_needed : in integer;
          --  test_out      : out std_logic_vector(31 downto 0);
            --flag_r_en     : in  std_logic;
           -- tflag : out std_logic;
            flag_w_en     : in  std_logic
        );
    end component top_md4_core;

    -- Synplicity black box declaration
    attribute syn_black_box : boolean;
    attribute syn_black_box of fifo_32x512 : component is true;

    attribute syn_black_box of fifo_32x512_1 : component is true;
    type data_array is array (0 to 15) of std_logic_vector(31 downto 0);
    signal testing_array : data_array := (others => x"00000000");

    type demo_mem is array (0 TO 31) of std_logic_vector(7 DOWNTO 0);
    signal demoarray  : demo_mem;
    signal litearray0 : demo_mem;
    signal litearray1 : demo_mem;
    signal litearray2 : demo_mem;
    signal litearray3 : demo_mem;


    signal quiesce : std_logic;

    signal reset_8  : std_logic;
 

    signal ram_addr  : integer range 0 to 31;
    signal lite_addr : integer range 0 to 31;

    signal user_r_mem_8_rden      : std_logic;
    signal user_r_mem_8_empty     : std_logic;
    signal user_r_mem_8_data      : std_logic_vector(7 DOWNTO 0);
    signal user_r_mem_8_eof       : std_logic;
    signal user_r_mem_8_open      : std_logic;
    signal user_w_mem_8_wren      : std_logic;
    signal user_w_mem_8_full      : std_logic;
    signal user_w_mem_8_data      : std_logic_vector(7 DOWNTO 0);
    signal user_w_mem_8_open      : std_logic;
    signal user_mem_8_addr        : std_logic_vector(4 DOWNTO 0);
    signal user_mem_8_addr_update : std_logic;

    signal user_r_read_32_empty   : std_logic;

    signal user_r_read_32_eof     : std_logic;
    signal user_r_read_32_open    : std_logic;
    signal user_r_read_8_rden     : std_logic;
    signal user_r_read_8_empty    : std_logic;
    signal user_r_read_8_data     : std_logic_vector(7 DOWNTO 0);
    signal user_r_read_8_eof      : std_logic;
    signal user_r_read_8_open     : std_logic;
 
    signal user_w_write_32_full   : std_logic;
 
    signal user_w_write_32_open   : std_logic;
    signal user_w_write_8_wren    : std_logic;
    signal user_w_write_8_full    : std_logic;
    signal user_w_write_8_data    : std_logic_vector(7 DOWNTO 0);
    signal user_w_write_8_open    : std_logic;
    signal user_clk               : std_logic;
    signal user_wren              : std_logic;
    signal user_wstrb             : std_logic_vector(3 DOWNTO 0);
    signal user_rden              : std_logic;
    signal user_rd_data           : std_logic_vector(31 DOWNTO 0);
    signal user_wr_data           : std_logic_vector(31 DOWNTO 0);
    signal user_addr              : std_logic_vector(31 DOWNTO 0);
    signal user_irq               : std_logic;
    signal test_ram_addr : integer;
    signal test_count : integer;
    signal data_counter : integer;

    -- Note that none of the ARM processor's direct connections to pads is
    -- defined as I/O on this module. Normally, they should be connected
    -- as toplevel ports here, but that confuses Vivado 2013.4 to think that
    -- some of these ports are real I/Os, causing an implementation failure.
    -- This detachment results in a lot of warnings during synthesis and
    -- implementation, but has no practical significance, as these pads are
    -- completely unrelated to the FPGA bitstream.

    signal PS_CLK         : std_logic;
    signal PS_PORB        : std_logic;
    signal PS_SRSTB       : std_logic;
    signal DDR_Addr       : std_logic_vector(14 DOWNTO 0);
    signal DDR_BankAddr   : std_logic_vector(2 DOWNTO 0);
    signal DDR_CAS_n      : std_logic;
    signal DDR_CKE        : std_logic;
    signal DDR_CS_n       : std_logic;
    signal DDR_Clk        : std_logic;
    signal DDR_Clk_n      : std_logic;
    signal DDR_DM         : std_logic_vector(3 DOWNTO 0);
    signal DDR_DQ         : std_logic_vector(31 DOWNTO 0);
    signal DDR_DQS        : std_logic_vector(3 DOWNTO 0);
    signal DDR_DQS_n      : std_logic_vector(3 DOWNTO 0);
    signal DDR_DRSTB      : std_logic;
    signal DDR_ODT        : std_logic;
    signal DDR_RAS_n      : std_logic;
    signal DDR_VRN        : std_logic;
    signal DDR_VRP        : std_logic;
    signal MIO            : std_logic_vector(53 DOWNTO 0);
    signal DDR_WEB        : std_logic;
    signal flag           : std_logic;
    signal rdenv2         : std_logic;
    signal rd_en_to_md4   : std_logic;
    signal data_to_md4    : std_logic_VECTOR(31 downto 0);
    signal empty_to_md4   : std_logic;
    signal wr_en_from_md4 : std_logic;
    signal full_from_md4  : std_logic;
    signal data_from_md4  : std_logic_VECTOR(31 downto 0);
    signal flag_r_en      : std_logic;
    signal flag_w_en      : std_logic;
    signal flagcounter    : integer;
    signal test_out : std_logic_vector(31 downto 0);
    signal tflag    : std_logic;

begin

  
    -- Xillybus Lite

    user_irq <= '0';                    -- No interrupts for now

    lite_addr <= conv_integer(user_addr(6 DOWNTO 2));

    process(user_clk)
    begin
        if (user_clk'event and user_clk = '1') then
            if (user_wstrb(0) = '1') then
                litearray0(lite_addr) <= user_wr_data(7 DOWNTO 0);
            end if;

            if (user_wstrb(1) = '1') then
                litearray1(lite_addr) <= user_wr_data(15 DOWNTO 8);
            end if;

            if (user_wstrb(2) = '1') then
                litearray2(lite_addr) <= user_wr_data(23 DOWNTO 16);
            end if;

            if (user_wstrb(3) = '1') then
                litearray3(lite_addr) <= user_wr_data(31 DOWNTO 24);
            end if;

            if (user_rden = '1') then
                user_rd_data <= litearray3(lite_addr) & litearray2(lite_addr) & litearray1(lite_addr) & litearray0(lite_addr);
            end if;
        end if;
    end process;

    --  A simple inferred RAM test

    ram_addr <= conv_integer(user_mem_8_addr);

    process(bus_clk)
    begin
        if (bus_clk'event and bus_clk = '1') then
            if (user_w_mem_8_wren = '1') then
                demoarray(ram_addr) <= user_w_mem_8_data;
            end if;
            if (user_r_mem_8_rden = '1') then
                user_r_mem_8_data <= demoarray(ram_addr);
            end if;
        end if;
    end process;
    
--    another :   process(bus_clk, reset_32)
--    begin
--    if reset_32 = '1' then
--    test_ram_addr <= 0;
--        elsif (bus_clk'event and bus_clk = '1') then
--            if (user_w_write_32_wren = '1') then
--                testing_array(test_ram_addr) <= user_w_write_32_data;
--                test_ram_addr <= test_ram_addr + 1;
--            end if;
--            if (user_r_read_32_rden = '1') then
--                user_r_read_32_data <= testing_array(test_ram_addr);
--                test_ram_addr <= test_ram_addr + 1;
--            end if;
--        end if;
--    end process;
--    another :   process(bus_clk, reset_32)
--    begin
--    if reset_32 = '1' then
--    test_ram_addr <= 0;
--    test_count <= 0;
--        elsif (bus_clk'event and bus_clk = '1') then
--        if (wr_en_from_md4 = '1') then
--            if test_count = 0 then
--                testing_array(0) <= test_out;
--             --   user_r_read_32_data<= test_out;
--            end if;
--            if test_count = 1 then
--                testing_array(1) <= test_out;
--              --  user_r_read_32_data<= test_out;
--            end if;
--            if test_count = 2 then
--                testing_array(2) <= test_out;
--             --   user_r_read_32_data<= test_out;
--            end if;
--            if test_count = 3 then
--                testing_array(3) <= test_out;
--              --  user_r_read_32_data<= test_out;
--                test_count <= 0;
--            end if;
--                testing_array(test_ram_addr) <= test_out;
--                test_ram_addr <= test_ram_addr + 1;
--                test_count <= test_count + 1;       
--            end if;          
--        end if;
--    end process;
    
    
    user_r_mem_8_empty <= '0';
    user_r_mem_8_eof   <= '0';
    user_w_mem_8_full  <= '0';

    --  32-bit loopback

    open_handle : process(bus_clk, user_w_write_32_wren, reset_32)
    begin
        if reset_32 = '1' then
            flag_w_en <= '0';
            data_counter <= 0;
        end if;
        if (user_w_write_32_wren'event and user_w_write_32_wren = '1') then
            flag_w_en <= '1';
        end if;
        if (rising_edge(bus_clk) and user_w_write_32_wren = '1') then
            data_counter <= data_counter + 1;
        end if;

    end process;

    md4_core_handler : component top_md4_core
        port map(
       --     test_out => test_out,
            clk           => bus_clk,
            rst           => reset_32,
            empty_to_md4  => empty_to_md4,
            data_to_md4   => data_to_md4,
            full_from_md4 => full_from_md4,
            wren_from_md4 => wr_en_from_md4,
            rd_en_to_md4  => rd_en_to_md4,
            hashout       => data_from_md4,
            rounds_needed => data_counter,
         --   flag_r_en     => flag_r_en,
         --   tflag => tflag,
            flag_w_en     => flag_w_en
        );

    fifo_32_to_md4 : fifo_32x512
        port map(
            clk   => bus_clk,
            srst  => reset_32,
            din   => user_w_write_32_data,
            wr_en => user_w_write_32_wren,
            rd_en => rd_en_to_md4,
            dout  => data_to_md4,
            full  => user_w_write_32_full,
            empty => empty_to_md4
        );

    fifo_32_from_md4 : fifo_32x512_1
        port map(
            clk   => bus_clk,
            srst  => reset_32,
            din   => data_from_md4,
            wr_en => wr_en_from_md4,
            rd_en => user_r_read_32_rden,
            dout  => user_r_read_32_data,
            full  => full_from_md4,
            empty =>  user_r_read_32_empty
        );
    
   -- reset_32 <= not (user_w_write_32_open or user_r_read_32_open);

    user_r_read_32_eof <= '0';

    --  8-bit loopback

end sample_arch;
