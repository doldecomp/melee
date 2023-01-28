f64 blah();                                         /* static */
? blahf();                                          /* static */

f32 test(void) {
    blahf();
    return (f32) blah();
}
