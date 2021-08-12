library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
--------------------------
entity top_md4_core is
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
        flag_w_en     : in  std_logic
       
    );
end entity top_md4_core;

architecture RTL of top_md4_core is
    signal data              : std_logic_vector(31 downto 0);
    signal address           : std_logic_vector(4 downto 0);
    signal ram_addr          : unsigned(5 downto 0);
    signal busy              : std_logic;
    signal clr               : std_logic;
    signal done              : std_logic;
    signal md4_msg           : std_logic_vector(127 downto 0);
    signal start             : std_logic;
    signal we                : std_logic;
    signal addr_b_uppper_bit : std_logic;
    signal array_full        : std_logic;
    signal counter           : integer;
    signal rd_en_to_md4_buff : std_logic;
    signal Clock_cycles      : unsigned(31 downto 0); 
    signal test_int1         : std_logic_vector(31 downto 0); 
    signal test_int2         : std_logic_vector(31 downto 0); 
    signal test_int3         : std_logic_vector(31 downto 0); 
    signal test_int4         : std_logic_vector(31 downto 0); 
    signal test1             : std_logic_vector(31 downto 0); 
    signal test2             : std_logic_vector(31 downto 0); 
    signal test3             : std_logic_vector(31 downto 0); 
    signal test4             : std_logic_vector(31 downto 0);
    signal core_rounds       : integer;
    signal core_rounds_done  : integer;

    type data_array is array (0 to 47) of std_logic_vector(31 downto 0);
    signal cache_array : data_array := (others => x"00000000");
    type state_type is (INIT, GIVE, ST, CLEAR);
    signal state       : state_type;
    constant A_IN : unsigned(31 downto 0) := x"67452301";
    constant B_IN : unsigned(31 downto 0) := x"efcdab89";
    constant C_IN : unsigned(31 downto 0) := x"98badcfe";
    constant D_IN : unsigned(31 downto 0) := x"10325476";
--    constant cache_array : data_array := (
--        x"00008061",
--        x"00000000",
--        x"00000000",
--        x"00000000",
--        x"00000000",
--        x"00000000",
--        x"00000000",
--        x"00000000",
--        x"00000000",
--        x"00000000",
--        x"00000000",
--        x"00000000",
--        x"00000000",
--        x"00000000",
--        x"00000008",
--        x"00000000");
    
    component md4_core
        port(
            clk               : in  std_logic;
            rst               : in  std_logic;
            clr               : in  std_logic;
            start             : in  std_logic;
            busy              : out std_logic;
            done              : out std_logic;
            address           : in  std_logic_vector(4 downto 0);
            data              : in  std_logic_vector(31 downto 0);
            we                : in  std_logic;
            addr_b_uppper_bit : in  std_logic;
            A_INIT            : in  unsigned(31 downto 0);
            B_INIT            : in  unsigned(31 downto 0);
            C_INIT            : in  unsigned(31 downto 0);
            D_INIT            : in  unsigned(31 downto 0);
      --   test1             : out std_logic_vector(31 downto 0); 
      --  test2             : out std_logic_vector(31 downto 0); 
       -- test3             : out std_logic_vector(31 downto 0); 
       -- test4             : out std_logic_vector(31 downto 0);
            md4_msg           : out std_logic_vector(127 downto 0)
        );
    end component md4_core;

begin
    md4_core_inst : md4_core
        port map(
            clk               => clk,
            rst               => rst,
            clr               => clr,
            start             => start,
            busy              => busy,
            done              => done,
            address           => address,
            data              => data,
            we                => we,
            addr_b_uppper_bit => addr_b_uppper_bit,
            A_INIT            => A_IN,--x"67452301",
            B_INIT            => B_IN,--x"efcdab89",
            C_INIT            => C_IN,--x"98badcfe",
            D_INIT            => D_IN,--x"10325476",

      --      test1 => test1,
       --     test2 => test2,
       --     test3 => test3,
        --    test4 => test4,
            md4_msg           => md4_msg
        );

    md4_msg_out : process(clk, rst) is
        type state_msg_type is (IDLE, PART1, PART2, PART3, PART4, COUNT);
        variable state_msg   : state_msg_type;
        variable int_msg_md4 : std_logic_vector(127 downto 0);
    begin
        if rst = '1' then
            hashout     <= (others => '0');
            int_msg_md4 := (others => '0');
            wren_from_md4 <= '0';
          --  tflag <= '0';
            state_msg := IDLE;
        elsif rising_edge(clk) then
            case state_msg is
                when IDLE =>
                    int_msg_md4 := md4_msg;
                    wren_from_md4 <= '0';
                    if done = '1' then                      
                        state_msg     := PART1;
                    end if;
                when PART1 =>
                    hashout   <= int_msg_md4(127 downto 96);--test_int1;--test1
              --      test_out <= x"00000001";--int_msg_md4(127 downto 96);
                    wren_from_md4 <= '1';
                    state_msg := PART2;                  
                when PART2 =>
                    hashout   <= int_msg_md4(95 downto 64);--test_int2;--test2;
               --     test_out <= x"00000010";--int_msg_md4(95 downto 64);
                    state_msg := PART3;
                when PART3 =>
                    hashout   <= int_msg_md4(63 downto 32);--test_int3;--test3;--
               --     test_out <= x"00000100";
                    state_msg := PART4;
                when PART4 =>
                    hashout       <= int_msg_md4(31 downto 0);--test_int4;--test4;--
                 --   test_out <= test_int4;--cache_array(1);
                 --   tflag <= '1';
                    state_msg     := COUNT;
                when COUNT =>
                    hashout       <= std_logic_vector(Clock_cycles); --x"00000001";
                    state_msg     := IDLE;           
            end case;
        end if;
    end process md4_msg_out;

    read : process(clk, rst)
    begin
        if rst = '1' then
            rd_en_to_md4      <= '0';
            rd_en_to_md4_buff <= '0';
        elsif (rising_edge(clk)) then
            if (empty_to_md4 = '1') then
                rd_en_to_md4      <= '0';
                rd_en_to_md4_buff <= '0';
            elsif (flag_w_en = '1') then
                rd_en_to_md4      <= '1';
                rd_en_to_md4_buff <= '1';
            end if;
        end if;
    end process;

    ram : process(clk, rst) is
    begin
        if rst = '1' then
            ram_addr   <= "000000";
            array_full <= '0';
            cache_array <= (others => x"00000000");
            core_rounds <= 5; -- damit Array_full aktic wird
        elsif (rising_edge(clk)) then
            if (ram_addr < "110010" and rd_en_to_md4_buff = '1') then -- max 0xF
                if(ram_addr > "000000") then
               cache_array((to_integer(ram_addr))- 1) <= data_to_md4;    
                end if;
            ram_addr                          <= ram_addr + 1;
            end if;
            if ((ram_addr = "110000" and rounds_needed = 48) or (ram_addr = "100000" and rounds_needed = 32) or (ram_addr = "010000" and rounds_needed = 16)) then
                array_full <= '1';
                core_rounds <= ((rounds_needed / 16) - 1);
            end if;
            if core_rounds_done = core_rounds then--state = ST then--done = '1' or busy = '1' then
                array_full <= '0';
            end if;
            if empty_to_md4 = '1' then--and core_rounds < 5 then
                ram_addr <= "000000";
            end if;
        end if;
    end process ram;

    handle : process(clk, rst) is
    begin
        if rst = '1' then
            state <= INIT;
            Clock_cycles <=  x"00000000";
            test_int1 <=  x"00000000";
            test_int2 <=  x"00000000";
            test_int3 <=  x"00000000";
            test_int4 <=  x"00000000";
        elsif rising_edge(clk) then
            case state is
                when INIT =>
                    addr_b_uppper_bit <= '0';
                    address           <= "00000";
                    we                <= '0';
                    clr               <= '0';
                    start             <= '0';
                    counter           <= 0;
                    core_rounds_done <= 0;                   
                    data <= x"00000000";
                    if busy = '1' then
                        Clock_cycles <= Clock_cycles + 1;
                    end if;
                    if array_full = '1' then
                        state <= GIVE;
                    end if;
                when GIVE =>
                    Clock_cycles <= Clock_cycles + 1;
                    we <= '1';
                    if (counter < 16) then
                        address <= std_logic_vector(to_unsigned(counter, 5));
                        if core_rounds_done = 0 then
                            data    <= cache_array(counter);
                        elsif core_rounds_done = 1 then
                            data    <= cache_array(counter + 16);
                        elsif core_rounds_done = 2 then
                            data    <= cache_array(counter + 32);
                        end if;
                        
                        counter <= counter + 1;
                    else
                        counter <= 0;
                        we      <= '0';
                        state   <= ST;
                    end if;
                when ST =>
                    Clock_cycles <= Clock_cycles + 1;
                    if (counter < 3) then
                        counter <= counter + 1;
                        start   <= '1';
                    else
                        start <= '0';
                    end if;
                    if (busy = '0' and counter = 3) then
                        core_rounds_done <= core_rounds_done + 1;
                        counter <= 0;
                        if core_rounds_done = core_rounds then
                            state   <= CLEAR;
                        else 
                            state   <= GIVE;
                        end if;
                    end if;
                when CLEAR =>
                    Clock_cycles <= Clock_cycles + 1;
                    clr   <= '1';
                    state <= INIT;
            end case;        
        end if;
    end process handle;

end architecture RTL;
