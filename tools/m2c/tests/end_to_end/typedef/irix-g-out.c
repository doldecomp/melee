void test(s32 arg0, s32 *arg1) {
    s32 temp_s0;
    s32 temp_s1;

    temp_s1 = func_00400090(arg0, arg1);
    temp_s0 = func_00400090(arg0, &arg0);
    func_00400090(*arg1, arg1);
}
