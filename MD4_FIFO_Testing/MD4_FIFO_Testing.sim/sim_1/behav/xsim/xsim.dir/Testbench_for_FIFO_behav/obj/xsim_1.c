/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                         */
/*  \   \        Copyright (c) 2003-2013 Xilinx, Inc.                 */
/*  /   /        All Right Reserved.                                  */
/* /---/   /\                                                         */
/* \   \  /  \                                                        */
/*  \___\/\___\                                                       */
/**********************************************************************/

#if defined(_WIN32)
 #include "stdio.h"
#endif
#include "iki.h"
#include <string.h>
#include <math.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                         */
/*  \   \        Copyright (c) 2003-2013 Xilinx, Inc.                 */
/*  /   /        All Right Reserved.                                  */
/* /---/   /\                                                         */
/* \   \  /  \                                                        */
/*  \___\/\___\                                                       */
/**********************************************************************/

#if defined(_WIN32)
 #include "stdio.h"
#endif
#include "iki.h"
#include <string.h>
#include <math.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
typedef void (*funcp)(char *, char *);
extern int main(int, char**);
extern void execute_2(char*, char *);
extern void execute_3(char*, char *);
extern void execute_4(char*, char *);
extern void execute_5(char*, char *);
extern void execute_6(char*, char *);
extern void execute_7(char*, char *);
extern void execute_8(char*, char *);
extern void execute_9(char*, char *);
extern void execute_188(char*, char *);
extern void execute_189(char*, char *);
extern void execute_190(char*, char *);
extern void execute_55(char*, char *);
extern void execute_56(char*, char *);
extern void execute_57(char*, char *);
extern void execute_58(char*, char *);
extern void execute_59(char*, char *);
extern void execute_60(char*, char *);
extern void execute_61(char*, char *);
extern void execute_62(char*, char *);
extern void execute_63(char*, char *);
extern void execute_187(char*, char *);
extern void execute_73(char*, char *);
extern void execute_74(char*, char *);
extern void execute_75(char*, char *);
extern void execute_76(char*, char *);
extern void execute_71(char*, char *);
extern void execute_72(char*, char *);
extern void execute_70(char*, char *);
extern void vlog_const_rhs_process_execute_0_fast_no_reg_no_agg(char*, char*, char*);
extern void execute_559(char*, char *);
extern void execute_560(char*, char *);
extern void execute_561(char*, char *);
extern void execute_562(char*, char *);
extern void execute_563(char*, char *);
extern void execute_564(char*, char *);
extern void execute_575(char*, char *);
extern void execute_576(char*, char *);
extern void execute_577(char*, char *);
extern void execute_578(char*, char *);
extern void execute_580(char*, char *);
extern void execute_581(char*, char *);
extern void execute_582(char*, char *);
extern void execute_583(char*, char *);
extern void execute_587(char*, char *);
extern void execute_588(char*, char *);
extern void execute_596(char*, char *);
extern void execute_600(char*, char *);
extern void execute_601(char*, char *);
extern void execute_602(char*, char *);
extern void execute_603(char*, char *);
extern void execute_605(char*, char *);
extern void execute_606(char*, char *);
extern void execute_607(char*, char *);
extern void execute_608(char*, char *);
extern void execute_614(char*, char *);
extern void execute_615(char*, char *);
extern void execute_620(char*, char *);
extern void execute_626(char*, char *);
extern void execute_630(char*, char *);
extern void execute_631(char*, char *);
extern void execute_634(char*, char *);
extern void execute_635(char*, char *);
extern void execute_638(char*, char *);
extern void execute_639(char*, char *);
extern void execute_642(char*, char *);
extern void execute_643(char*, char *);
extern void execute_646(char*, char *);
extern void execute_647(char*, char *);
extern void execute_650(char*, char *);
extern void execute_651(char*, char *);
extern void execute_193(char*, char *);
extern void execute_131(char*, char *);
extern void vlog_simple_process_execute_0_fast_no_reg_no_agg(char*, char*, char*);
extern void execute_209(char*, char *);
extern void execute_213(char*, char *);
extern void execute_313(char*, char *);
extern void vlog_simple_process_execute_1_fast_no_reg_no_agg(char*, char*, char*);
extern void execute_539(char*, char *);
extern void execute_542(char*, char *);
extern void execute_543(char*, char *);
extern void execute_544(char*, char *);
extern void execute_547(char*, char *);
extern void execute_548(char*, char *);
extern void execute_549(char*, char *);
extern void execute_550(char*, char *);
extern void execute_551(char*, char *);
extern void execute_81(char*, char *);
extern void execute_82(char*, char *);
extern void execute_83(char*, char *);
extern void execute_84(char*, char *);
extern void execute_85(char*, char *);
extern void execute_86(char*, char *);
extern void execute_87(char*, char *);
extern void execute_88(char*, char *);
extern void execute_89(char*, char *);
extern void execute_90(char*, char *);
extern void execute_91(char*, char *);
extern void execute_92(char*, char *);
extern void execute_93(char*, char *);
extern void execute_94(char*, char *);
extern void execute_95(char*, char *);
extern void execute_96(char*, char *);
extern void execute_126(char*, char *);
extern void execute_127(char*, char *);
extern void execute_128(char*, char *);
extern void execute_129(char*, char *);
extern void execute_130(char*, char *);
extern void execute_425(char*, char *);
extern void execute_426(char*, char *);
extern void execute_429(char*, char *);
extern void execute_491(char*, char *);
extern void execute_492(char*, char *);
extern void execute_493(char*, char *);
extern void execute_496(char*, char *);
extern void execute_500(char*, char *);
extern void execute_513(char*, char *);
extern void execute_514(char*, char *);
extern void execute_515(char*, char *);
extern void execute_523(char*, char *);
extern void execute_524(char*, char *);
extern void execute_525(char*, char *);
extern void execute_526(char*, char *);
extern void execute_527(char*, char *);
extern void execute_528(char*, char *);
extern void execute_529(char*, char *);
extern void execute_530(char*, char *);
extern void execute_531(char*, char *);
extern void execute_532(char*, char *);
extern void execute_533(char*, char *);
extern void execute_534(char*, char *);
extern void execute_535(char*, char *);
extern void execute_536(char*, char *);
extern void execute_101(char*, char *);
extern void execute_102(char*, char *);
extern void execute_103(char*, char *);
extern void execute_104(char*, char *);
extern void execute_105(char*, char *);
extern void execute_106(char*, char *);
extern void execute_112(char*, char *);
extern void execute_113(char*, char *);
extern void execute_117(char*, char *);
extern void execute_118(char*, char *);
extern void execute_119(char*, char *);
extern void execute_120(char*, char *);
extern void execute_121(char*, char *);
extern void execute_122(char*, char *);
extern void execute_123(char*, char *);
extern void execute_124(char*, char *);
extern void execute_430(char*, char *);
extern void execute_431(char*, char *);
extern void execute_432(char*, char *);
extern void execute_433(char*, char *);
extern void execute_435(char*, char *);
extern void execute_436(char*, char *);
extern void execute_439(char*, char *);
extern void execute_442(char*, char *);
extern void execute_443(char*, char *);
extern void execute_444(char*, char *);
extern void execute_445(char*, char *);
extern void execute_446(char*, char *);
extern void execute_449(char*, char *);
extern void execute_450(char*, char *);
extern void execute_451(char*, char *);
extern void execute_452(char*, char *);
extern void execute_453(char*, char *);
extern void execute_454(char*, char *);
extern void execute_455(char*, char *);
extern void execute_456(char*, char *);
extern void execute_457(char*, char *);
extern void execute_458(char*, char *);
extern void execute_459(char*, char *);
extern void execute_460(char*, char *);
extern void execute_461(char*, char *);
extern void execute_462(char*, char *);
extern void execute_463(char*, char *);
extern void execute_464(char*, char *);
extern void execute_465(char*, char *);
extern void execute_466(char*, char *);
extern void execute_467(char*, char *);
extern void execute_468(char*, char *);
extern void execute_469(char*, char *);
extern void execute_470(char*, char *);
extern void execute_471(char*, char *);
extern void execute_472(char*, char *);
extern void execute_473(char*, char *);
extern void execute_474(char*, char *);
extern void execute_475(char*, char *);
extern void execute_476(char*, char *);
extern void execute_477(char*, char *);
extern void execute_478(char*, char *);
extern void execute_479(char*, char *);
extern void execute_480(char*, char *);
extern void execute_481(char*, char *);
extern void execute_1018(char*, char *);
extern void execute_1019(char*, char *);
extern void execute_1020(char*, char *);
extern void execute_1021(char*, char *);
extern void execute_1022(char*, char *);
extern void execute_1023(char*, char *);
extern void execute_1034(char*, char *);
extern void execute_1035(char*, char *);
extern void execute_1036(char*, char *);
extern void execute_1037(char*, char *);
extern void execute_1039(char*, char *);
extern void execute_1040(char*, char *);
extern void execute_1041(char*, char *);
extern void execute_1042(char*, char *);
extern void execute_1046(char*, char *);
extern void execute_1047(char*, char *);
extern void execute_1055(char*, char *);
extern void execute_1059(char*, char *);
extern void execute_1060(char*, char *);
extern void execute_1061(char*, char *);
extern void execute_1062(char*, char *);
extern void execute_1064(char*, char *);
extern void execute_1065(char*, char *);
extern void execute_1066(char*, char *);
extern void execute_1067(char*, char *);
extern void execute_1073(char*, char *);
extern void execute_1074(char*, char *);
extern void execute_1079(char*, char *);
extern void execute_1085(char*, char *);
extern void execute_1089(char*, char *);
extern void execute_1090(char*, char *);
extern void execute_1093(char*, char *);
extern void execute_1094(char*, char *);
extern void execute_1097(char*, char *);
extern void execute_1098(char*, char *);
extern void execute_1101(char*, char *);
extern void execute_1102(char*, char *);
extern void execute_1105(char*, char *);
extern void execute_1106(char*, char *);
extern void execute_1109(char*, char *);
extern void execute_1110(char*, char *);
extern void vlog_transfunc_eventcallback(char*, char*, unsigned, unsigned, unsigned, char *);
extern void transaction_32(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_33(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_34(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_35(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_36(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_37(char*, char*, unsigned, unsigned, unsigned);
extern void vhdl_transfunc_eventcallback(char*, char*, unsigned, unsigned, unsigned, char *);
extern void transaction_59(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_67(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_73(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_107(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_108(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_109(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_110(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_111(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_112(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_127(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_148(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_163(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_164(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_165(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_166(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_167(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_168(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_169(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_170(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_1118(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_1119(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_1120(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_1121(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_1122(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_1123(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_1124(char*, char*, unsigned, unsigned, unsigned);
extern void transaction_1125(char*, char*, unsigned, unsigned, unsigned);
funcp funcTab[269] = {(funcp)execute_2, (funcp)execute_3, (funcp)execute_4, (funcp)execute_5, (funcp)execute_6, (funcp)execute_7, (funcp)execute_8, (funcp)execute_9, (funcp)execute_188, (funcp)execute_189, (funcp)execute_190, (funcp)execute_55, (funcp)execute_56, (funcp)execute_57, (funcp)execute_58, (funcp)execute_59, (funcp)execute_60, (funcp)execute_61, (funcp)execute_62, (funcp)execute_63, (funcp)execute_187, (funcp)execute_73, (funcp)execute_74, (funcp)execute_75, (funcp)execute_76, (funcp)execute_71, (funcp)execute_72, (funcp)execute_70, (funcp)vlog_const_rhs_process_execute_0_fast_no_reg_no_agg, (funcp)execute_559, (funcp)execute_560, (funcp)execute_561, (funcp)execute_562, (funcp)execute_563, (funcp)execute_564, (funcp)execute_575, (funcp)execute_576, (funcp)execute_577, (funcp)execute_578, (funcp)execute_580, (funcp)execute_581, (funcp)execute_582, (funcp)execute_583, (funcp)execute_587, (funcp)execute_588, (funcp)execute_596, (funcp)execute_600, (funcp)execute_601, (funcp)execute_602, (funcp)execute_603, (funcp)execute_605, (funcp)execute_606, (funcp)execute_607, (funcp)execute_608, (funcp)execute_614, (funcp)execute_615, (funcp)execute_620, (funcp)execute_626, (funcp)execute_630, (funcp)execute_631, (funcp)execute_634, (funcp)execute_635, (funcp)execute_638, (funcp)execute_639, (funcp)execute_642, (funcp)execute_643, (funcp)execute_646, (funcp)execute_647, (funcp)execute_650, (funcp)execute_651, (funcp)execute_193, (funcp)execute_131, (funcp)vlog_simple_process_execute_0_fast_no_reg_no_agg, (funcp)execute_209, (funcp)execute_213, (funcp)execute_313, (funcp)vlog_simple_process_execute_1_fast_no_reg_no_agg, (funcp)execute_539, (funcp)execute_542, (funcp)execute_543, (funcp)execute_544, (funcp)execute_547, (funcp)execute_548, (funcp)execute_549, (funcp)execute_550, (funcp)execute_551, (funcp)execute_81, (funcp)execute_82, (funcp)execute_83, (funcp)execute_84, (funcp)execute_85, (funcp)execute_86, (funcp)execute_87, (funcp)execute_88, (funcp)execute_89, (funcp)execute_90, (funcp)execute_91, (funcp)execute_92, (funcp)execute_93, (funcp)execute_94, (funcp)execute_95, (funcp)execute_96, (funcp)execute_126, (funcp)execute_127, (funcp)execute_128, (funcp)execute_129, (funcp)execute_130, (funcp)execute_425, (funcp)execute_426, (funcp)execute_429, (funcp)execute_491, (funcp)execute_492, (funcp)execute_493, (funcp)execute_496, (funcp)execute_500, (funcp)execute_513, (funcp)execute_514, (funcp)execute_515, (funcp)execute_523, (funcp)execute_524, (funcp)execute_525, (funcp)execute_526, (funcp)execute_527, (funcp)execute_528, (funcp)execute_529, (funcp)execute_530, (funcp)execute_531, (funcp)execute_532, (funcp)execute_533, (funcp)execute_534, (funcp)execute_535, (funcp)execute_536, (funcp)execute_101, (funcp)execute_102, (funcp)execute_103, (funcp)execute_104, (funcp)execute_105, (funcp)execute_106, (funcp)execute_112, (funcp)execute_113, (funcp)execute_117, (funcp)execute_118, (funcp)execute_119, (funcp)execute_120, (funcp)execute_121, (funcp)execute_122, (funcp)execute_123, (funcp)execute_124, (funcp)execute_430, (funcp)execute_431, (funcp)execute_432, (funcp)execute_433, (funcp)execute_435, (funcp)execute_436, (funcp)execute_439, (funcp)execute_442, (funcp)execute_443, (funcp)execute_444, (funcp)execute_445, (funcp)execute_446, (funcp)execute_449, (funcp)execute_450, (funcp)execute_451, (funcp)execute_452, (funcp)execute_453, (funcp)execute_454, (funcp)execute_455, (funcp)execute_456, (funcp)execute_457, (funcp)execute_458, (funcp)execute_459, (funcp)execute_460, (funcp)execute_461, (funcp)execute_462, (funcp)execute_463, (funcp)execute_464, (funcp)execute_465, (funcp)execute_466, (funcp)execute_467, (funcp)execute_468, (funcp)execute_469, (funcp)execute_470, (funcp)execute_471, (funcp)execute_472, (funcp)execute_473, (funcp)execute_474, (funcp)execute_475, (funcp)execute_476, (funcp)execute_477, (funcp)execute_478, (funcp)execute_479, (funcp)execute_480, (funcp)execute_481, (funcp)execute_1018, (funcp)execute_1019, (funcp)execute_1020, (funcp)execute_1021, (funcp)execute_1022, (funcp)execute_1023, (funcp)execute_1034, (funcp)execute_1035, (funcp)execute_1036, (funcp)execute_1037, (funcp)execute_1039, (funcp)execute_1040, (funcp)execute_1041, (funcp)execute_1042, (funcp)execute_1046, (funcp)execute_1047, (funcp)execute_1055, (funcp)execute_1059, (funcp)execute_1060, (funcp)execute_1061, (funcp)execute_1062, (funcp)execute_1064, (funcp)execute_1065, (funcp)execute_1066, (funcp)execute_1067, (funcp)execute_1073, (funcp)execute_1074, (funcp)execute_1079, (funcp)execute_1085, (funcp)execute_1089, (funcp)execute_1090, (funcp)execute_1093, (funcp)execute_1094, (funcp)execute_1097, (funcp)execute_1098, (funcp)execute_1101, (funcp)execute_1102, (funcp)execute_1105, (funcp)execute_1106, (funcp)execute_1109, (funcp)execute_1110, (funcp)vlog_transfunc_eventcallback, (funcp)transaction_32, (funcp)transaction_33, (funcp)transaction_34, (funcp)transaction_35, (funcp)transaction_36, (funcp)transaction_37, (funcp)vhdl_transfunc_eventcallback, (funcp)transaction_59, (funcp)transaction_67, (funcp)transaction_73, (funcp)transaction_107, (funcp)transaction_108, (funcp)transaction_109, (funcp)transaction_110, (funcp)transaction_111, (funcp)transaction_112, (funcp)transaction_127, (funcp)transaction_148, (funcp)transaction_163, (funcp)transaction_164, (funcp)transaction_165, (funcp)transaction_166, (funcp)transaction_167, (funcp)transaction_168, (funcp)transaction_169, (funcp)transaction_170, (funcp)transaction_1118, (funcp)transaction_1119, (funcp)transaction_1120, (funcp)transaction_1121, (funcp)transaction_1122, (funcp)transaction_1123, (funcp)transaction_1124, (funcp)transaction_1125};
const int NumRelocateId= 269;

void relocate(char *dp)
{
	iki_relocate(dp, "xsim.dir/Testbench_for_FIFO_behav/xsim.reloc",  (void **)funcTab, 269);
	iki_vhdl_file_variable_register(dp + 393752);
	iki_vhdl_file_variable_register(dp + 393808);


	/*Populate the transaction function pointer field in the whole net structure */
}

void sensitize(char *dp)
{
	iki_sensitize(dp, "xsim.dir/Testbench_for_FIFO_behav/xsim.reloc");
}

	// Initialize Verilog nets in mixed simulation, for the cases when the value at time 0 should be propagated from the mixed language Vhdl net

void wrapper_func_0(char *dp)

{

	iki_vlog_schedule_transaction_signal_fast_vhdl_value_time_0(dp + 399232, dp + 419320, 0, 0, 0, 0, 1, 1);

	iki_vlog_schedule_transaction_signal_fast_vhdl_value_time_0(dp + 399288, dp + 419376, 0, 0, 0, 0, 1, 1);

	iki_vlog_schedule_transaction_signal_fast_vhdl_value_time_0(dp + 399344, dp + 419432, 0, 31, 0, 31, 32, 1);

	iki_vlog_schedule_transaction_signal_fast_vhdl_value_time_0(dp + 399384, dp + 419488, 0, 0, 0, 0, 1, 1);

	iki_vlog_schedule_transaction_signal_fast_vhdl_value_time_0(dp + 405680, dp + 419544, 0, 0, 0, 0, 1, 1);

	iki_vlog_schedule_transaction_signal_fast_vhdl_value_time_0(dp + 399232, dp + 601632, 0, 0, 0, 0, 1, 1);

	iki_vlog_schedule_transaction_signal_fast_vhdl_value_time_0(dp + 399288, dp + 601688, 0, 0, 0, 0, 1, 1);

	iki_vlog_schedule_transaction_signal_fast_vhdl_value_time_0(dp + 405944, dp + 601744, 0, 31, 0, 31, 32, 1);

	iki_vlog_schedule_transaction_signal_fast_vhdl_value_time_0(dp + 405832, dp + 601800, 0, 0, 0, 0, 1, 1);

	iki_vlog_schedule_transaction_signal_fast_vhdl_value_time_0(dp + 399440, dp + 601856, 0, 0, 0, 0, 1, 1);

}

void simulate(char *dp)
{
		iki_schedule_processes_at_time_zero(dp, "xsim.dir/Testbench_for_FIFO_behav/xsim.reloc");
	wrapper_func_0(dp);

	iki_execute_processes();

	// Schedule resolution functions for the multiply driven Verilog nets that have strength
	// Schedule transaction functions for the singly driven Verilog nets that have strength

}
#include "iki_bridge.h"
void relocate(char *);

void sensitize(char *);

void simulate(char *);

extern SYSTEMCLIB_IMP_DLLSPEC void local_register_implicit_channel(int, char*);
extern void implicit_HDL_SCinstantiate();

extern void implicit_HDL_SCcleanup();

extern SYSTEMCLIB_IMP_DLLSPEC int xsim_argc_copy ;
extern SYSTEMCLIB_IMP_DLLSPEC char** xsim_argv_copy ;

int main(int argc, char **argv)
{
    iki_heap_initialize("ms", "isimmm", 0, 2147483648) ;
    iki_set_sv_type_file_path_name("xsim.dir/Testbench_for_FIFO_behav/xsim.svtype");
    iki_set_crvs_dump_file_path_name("xsim.dir/Testbench_for_FIFO_behav/xsim.crvsdump");
    void* design_handle = iki_create_design("xsim.dir/Testbench_for_FIFO_behav/xsim.mem", (void *)relocate, (void *)sensitize, (void *)simulate, 0, isimBridge_getWdbWriter(), 0, argc, argv);
     iki_set_rc_trial_count(100);
    (void) design_handle;
    return iki_simulate_design();
}
