.include "macros.inc"

.section .ctors, "wa"  # 0x803B7240 - 0x803B7260

# No discernible way to migrate this to C.
# Tried #pragma section ".ctors" "w", and putting it in __start.c
# p.165 https://seniord.ece.iastate.edu/projects/archive/dec0104/Support_Web/reference/CodeWarrior/C_Compilers_Reference.pdf
# https://github.com/parai/gainos-tk/blob/58b929fcbbf1c9f3c0cdb03f6e500e3d3b738e7f/bin/gainos_tk/mpc5634/Project/src/__ppc_eabi_init.c#L126
# https://docs.nxp.com/bundle/GUID-9FAC1C79-3809-474F-B8DF-82BEB5B88419/page/GUID-679CAE63-2DE2-46A3-9321-579AE3F3D7E5.html

.global __ctors
__ctors:
    .4byte __init_cpp_exceptions
    .4byte __sinit_trigf_c
    .4byte NULL
