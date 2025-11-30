#ifndef UTILS_H
#define UTILS_H

#if defined(__ASSEMBLER__)
# define   U(_x)	(_x)
# define  UL(_x)	(_x)
# define ULL(_x)	(_x)
# define   L(_x)	(_x)
# define  LL(_x)	(_x)
#else
# define  U_(_x)	(_x##U)
# define   U(_x)	U_(_x)
# define  UL_(_x)	(_x##UL)
# define  UL(_x)	UL_(_x)
# define  ULL_(_x)	(_x##ULL)
# define  ULL(_x)	ULL_(_x)
# define  L_(_x)	(_x##L)
# define  L(_x)	L_(_x)
# define  LL_(_x)	(_x##LL)
# define  LL(_x)	LL_(_x)

#endif

#endif // UTILS_H
