
#include "libft.h"

int		ft_cmpui_e(const void *a, const void *b)
{
	return (*(unsigned int*)a == *(unsigned int*)b);
}

int		ft_cmpui_l(const void *a, const void *b)
{
	return (*(unsigned int*)a < *(unsigned int*)b);
}

int		ft_cmpui_le(const void *a, const void *b)
{
	return (*(unsigned int*)a <= *(unsigned int*)b);
}

int		ft_cmpui_g(const void *a, const void *b)
{
	return (*(unsigned int*)a > *(unsigned int*)b);
}

int		ft_cmpui_ge(const void *a, const void *b)
{
	return (*(unsigned int*)a >= *(unsigned int*)b);
}
