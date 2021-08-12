library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
----------------------------------------------------------------------------------
-- expecting 512 bit junk of data (padded and length information already added) 
-- in the dual port memory
-- 
----------------------------------------------------------------------------------
entity md4_core is
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
        A_INIT            : in  unsigned(31 downto 0); -- := x"67452301";
        B_INIT            : in  unsigned(31 downto 0); -- := x"efcdab89";
        C_INIT            : in  unsigned(31 downto 0); -- := x"98badcfe";
        D_INIT            : in  unsigned(31 downto 0); -- := x"10325476";
        test1             : out std_logic_vector(31 downto 0); 
        test2             : out std_logic_vector(31 downto 0); 
        test3             : out std_logic_vector(31 downto 0); 
        test4             : out std_logic_vector(31 downto 0); 

        md4_msg           : out std_logic_vector(127 downto 0) -- byte15, byte 14, ... byte 0
    );
end entity md4_core;
architecture RTL of md4_core is
    --		signal md4_a   :  unsigned(31 downto 0);
    --		signal md4_b   :  unsigned(31 downto 0);
    --		signal md4_c   :  unsigned(31 downto 0);
    --		signal md4_d   :  unsigned(31 downto 0);
    signal addr_b : std_logic_vector(3 downto 0);
    signal data_b : std_logic_vector(data'range);

    --signal addr_a : std_logic_vector(address'range);
    --signal di     : std_logic_vector(data'range);
    signal data_a : std_logic_vector(data'range);

    signal a  : unsigned(31 downto 0);
    signal b  : unsigned(31 downto 0);
    signal c  : unsigned(31 downto 0);
    signal d  : unsigned(31 downto 0);
    signal aa : unsigned(31 downto 0);
    signal bb : unsigned(31 downto 0);
    signal cc : unsigned(31 downto 0);
    signal dd : unsigned(31 downto 0);

    --This constant represents the square root of 2
    constant ROUND2_ADD : unsigned(31 downto 0) := x"5a827999";

    --This constant represents the square root of 3
    constant ROUND3_ADD : unsigned(31 downto 0) := x"6ed9eba1";

    type rotate_round is array (0 to 3) of natural;
    constant ROTATE_ROUND1 : rotate_round := (3, 7, 11, 19);
    constant ROTATE_ROUND2 : rotate_round := (3, 5, 9, 13);
    constant ROTATE_ROUND3 : rotate_round := (3, 9, 11, 15);

    type addr_table is array (0 to 15) of natural; --std_logic_vector(3 downto 0);

    constant ADDR_TRANSLATE_TABLE_R2 : addr_table := (0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15);
    constant ADDR_TRANSLATE_TABLE_R3 : addr_table := (0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15);

    function F(x, y, z : in unsigned) return unsigned is
    begin
        return ((x and y) or ((not x) and z));
    end function F;

    function G(x, y, z : unsigned) return unsigned is
    begin
        return ((x and y) or (x and z) or (y and z));
    end function G;

    function H(x, y, z : unsigned) return unsigned is
    begin
        return (x xor y xor z);
    end function H;
    signal addrb_intern : std_logic_vector(4 downto 0);
        component ram
        generic(
            addr_width : natural := 9;
            data_width : natural := 8
        );
        port(
            clk       : in  std_logic;
            addra     : in  std_logic_vector(addr_width - 1 downto 0);
            write_ena : in  std_logic;
            dina      : in  std_logic_vector(data_width - 1 downto 0);
            douta     : out std_logic_vector(data_width - 1 downto 0);
            addrb     : in  std_logic_vector(addr_width - 1 downto 0);
            write_enb : in  std_logic;
            dinb      : in  std_logic_vector(data_width - 1 downto 0);
            doutb     : out std_logic_vector(data_width - 1 downto 0)
        );
    end component ram;
begin
    dp_ram_inst : component ram
        generic map(
            addr_width => 5,
            data_width => 32
        )
        port map(
            clk       => clk,
            addra     => address,
            write_ena => we,
            dina      => data,
            douta     => data_a,
            addrb     => addrb_intern,
            write_enb => '0',
            dinb      => (others => '0'),
            doutb     => data_b
        );
addrb_intern <= addr_b_uppper_bit & addr_b;
   -- /* ROTATE_LEFT rotates x left n bits.
 --*/
    --#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))
    --ROL

    --/* FF, GG and HH are transformations for rounds 1, 2 and 3 */
    --/* Rotation is separate from addition to prevent recomputation */

    --#define FF(a, b, c, d, x, s) { \
    --    (a) += F ((b), (c), (d)) + (x); \
    --    (a) = ROTATE_LEFT ((a), (s)); \
    --  }
    --#define GG(a, b, c, d, x, s) { \
    --    (a) += G ((b), (c), (d)) + (x) + (UINT4)0x5a827999; \
    --    (a) = ROTATE_LEFT ((a), (s)); \
    --  }
    --#define HH(a, b, c, d, x, s) { \
    --    (a) += H ((b), (c), (d)) + (x) + (UINT4)0x6ed9eba1; \
    --    (a) = ROTATE_LEFT ((a), (s)); 
    --  }

    fsm_p : process(clk, rst) is
        type state_type is (INIT, IDLE, ROUND1, ROUND2, ROUND3, CALC_MD4, FINISHED
        );
        variable state         : state_type;
        variable cnt           : unsigned(1 downto 0);
        variable cnt_round_ops : natural range 0 to 15;
        variable tmp_func      : unsigned(31 downto 0);
        variable tmp_add       : unsigned(31 downto 0);
        variable tmp_rotate    : natural range 0 to 19;

    begin
        if rst = '1' then
            cnt           := "00";
            cnt_round_ops := 0;
            busy          <= '0';
            state         := INIT;
            tmp_func      := x"00000000";
            tmp_add       := x"00000000";
            done          <= '0';
            a <= x"00000000";
            b <= x"00000000";
            c <= x"00000000";
            d <= x"00000000";
            aa <= x"00000000";
            bb <= x"00000000";
            cc <= x"00000000";
            dd <= x"00000000";
            addr_b        <= x"0";
            md4_msg       <= (others => '0');
            test1 <=  x"00000000";
            test2<=  x"00000000";
            test3<=  x"00000000";
            test4<=  x"00000000";

        elsif rising_edge(clk) then
            busy <= '0';
            done <= '0';
            case state is
                when INIT =>
                    cnt           := "00";
                    cnt_round_ops := 0;
                    addr_b        <= x"0";
                    md4_msg       <= (others => '0');
                    aa            <= A_INIT;
                    bb            <= B_INIT;
                    cc            <= C_INIT;
                    dd            <= D_INIT;
                    state         := IDLE;

                when IDLE =>
                    cnt           := "00";
                    cnt_round_ops := 0;
                    addr_b        <= x"0";
                    if (clr = '1') then
                        state := INIT;
                    elsif (start = '1') then
                        busy  <= '1';
                        a     <= aa;    --    <= a;
                        b     <= bb;    --    <= b;
                        c     <= cc;    --    <= c;
                        d     <= dd;    --    <= d;
                        state := ROUND1;
                    end if;

                when ROUND1 =>
                   -- /* Let [abcd k s] denote the operation
            		-- a = (a + F(b,c,d) + X[k]) <<< s. */
                    if cnt_round_ops = 15 then
                        addr_b <= x"0"; --std_logic_vector(to_unsigned(cnt_round_ops,5)+1);
                    else
                        addr_b <= std_logic_vector(to_unsigned(cnt_round_ops, 4) + 1);
                    end if;

                    busy <= '1';
                    if cnt = 0 then
                        tmp_func := F(b, c, d);
                        tmp_add  := a + unsigned(data_b);
                        if cnt_round_ops = 2 then
                            test1 <= std_logic_vector(data_b);
                        end if;
                        if cnt_round_ops = 3 then
                            test2 <= std_logic_vector(data_b);
                        end if;
                        if cnt_round_ops = 4 then
                            test3 <= std_logic_vector(data_b);
                        end if;
                        if cnt_round_ops = 5 then
                            test4 <= std_logic_vector(data_b);
                        end if;
                    elsif cnt = 1 then
                        tmp_add := tmp_add + tmp_func;
                    elsif cnt = 2 then
                        null;
                        tmp_rotate := ROTATE_ROUND1(cnt_round_ops mod 4);
                    else
                        a <= d;
                        b <= tmp_add rol tmp_rotate; --ROTATE_ROUND1(cnt_round_ops mod 4);
                        c <= b;
                        d <= c;
--                        if cnt_round_ops = 5 then
--                       test1 <= std_logic_vector(a);
--                       test2<= std_logic_vector(b);
--                       test3<= std_logic_vector(c);
--                       test4<= std_logic_vector(d);
--                        end if;
                        
                        if cnt_round_ops < 15 then
                            cnt_round_ops := cnt_round_ops + 1;
                        else
                            state         := ROUND2;
                            cnt_round_ops := 0;
                      -- test1 <= std_logic_vector(a);
                      -- test2<= std_logic_vector(b);
                      -- test3<= std_logic_vector(c);
                      -- test4<= std_logic_vector(d);
                        end if;

                    end if;

                    cnt := cnt + 1;

                when ROUND2 =>
                    -- a = (a + G(b,c,d) + X[k] + 5A827999) <<< s.

                    if cnt_round_ops = 15 then
                        addr_b <= x"0"; --std_logic_vector(to_unsigned(cnt_round_ops,5)+1);
                    else
                        addr_b <= std_logic_vector(to_unsigned(ADDR_TRANSLATE_TABLE_R2(cnt_round_ops + 1), 4));
                    end if;

                    busy <= '1';
                    if cnt = 0 then
                        tmp_func := G(b, c, d);
                        tmp_add  := a + unsigned(data_b);
                    elsif cnt = 1 then
                        tmp_add := tmp_add + tmp_func;
                    elsif cnt = 2 then
                        tmp_add    := tmp_add + ROUND2_ADD;
                        tmp_rotate := ROTATE_ROUND2(cnt_round_ops mod 4);
                    else
                        a <= d;
                        b <= tmp_add rol tmp_rotate;
                        c <= b;
                        d <= c;
                        if cnt_round_ops < 15 then
                            cnt_round_ops := cnt_round_ops + 1;
                        else
                            state         := ROUND3;
                            cnt_round_ops := 0;
                        end if;

                    end if;

                    cnt := cnt + 1;

                when ROUND3 =>
                    if cnt_round_ops = 15 then
                        addr_b <= x"0";
                    else
                        addr_b <= std_logic_vector(to_unsigned(ADDR_TRANSLATE_TABLE_R3(cnt_round_ops + 1), 4));
                    end if;
                    busy <= '1';
                    if cnt = 0 then
                        tmp_func := H(b, c, d);
                        tmp_add  := a + unsigned(data_b);
                    elsif cnt = 1 then
                        tmp_add := tmp_add + tmp_func;
                    elsif cnt = 2 then
                        tmp_add    := tmp_add + ROUND3_ADD;
                        tmp_rotate := ROTATE_ROUND3(cnt_round_ops mod 4);
                    else
                        a <= d;
                        b <= tmp_add rol tmp_rotate;
                        c <= b;
                        d <= c;
                        if cnt_round_ops < 15 then
                            cnt_round_ops := cnt_round_ops + 1;
                        else
                            state         := CALC_MD4;
                            cnt_round_ops := 0;
                        end if;

                    end if;

                    cnt := cnt + 1;
                when CALC_MD4 =>
                    busy <= '1';
                    if cnt = 0 then
                  --      test1 <= std_logic_vector(aa);
                        aa <= aa + a;
                    elsif cnt = 1 then
           --  test2<= std_logic_vector(bb);
                        bb <= bb + b;
                    elsif cnt = 2 then
                 --    test3<= std_logic_vector(cc);
                        cc <= cc + c;
                    else
                 --    test4<= std_logic_vector(dd);
                        dd    <= dd + d;
                        state := FINISHED;
                    end if;
                    cnt  := cnt + 1;
                when FINISHED =>
                    md4_msg <= std_logic_vector(dd & cc & bb & aa);

                    busy  <= '0';
                    done  <= '1';
                    state := IDLE;
            end case;
        end if;
    end process fsm_p;

end architecture RTL;
