s32 test(s32 arg0)
{
    s32 var_v1;

    var_v1 = 0;
    if (arg0 > 0)
    {
        do
        {
            if (var_v1 == 5)
            {
                var_v1 *= 2;
            }
            else
            {
                var_v1 += 4;
            }
        } while (var_v1 < arg0);
    }
    return var_v1;
}
