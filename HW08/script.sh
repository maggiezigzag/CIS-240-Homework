make

./trace public-test_basic_out_mine.txt public-test_basic.obj
cmp public-test_basic_out_mine.txt public-test_basic.txt

./trace public-branch0_out_mine.txt public-branch0.obj
cmp public-branch0_out_mine.txt public-branch0.txt

./trace public-BR_arith_out_mine.txt public-BR_arith.obj
cmp public-BR_arith_out_mine.txt public-BR_arith.txt

./trace public-test_checkers_img_out_mine.txt public-test_checkers_img.obj
cmp public-test_checkers_img_out_mine.txt public-test_checkers_img.txt

./trace public-test_trap_rti_ldr_str_out_mine.txt public-test_trap_rti_ldr_str.obj
cmp public-test_trap_rti_ldr_str_out_mine.txt public-test_trap_rti_ldr_str.txt

./trace wireframe_mine.txt os.obj wireframe.obj
cmp wireframe_mine.txt wireframe.txt

