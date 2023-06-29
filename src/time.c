/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:16:03 by geudes            #+#    #+#             */
/*   Updated: 2023/06/29 12:25:06 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

struct	s_timeval
{
	unsigned long int	sec;
	long int			nano;
};

void	mytime(struct s_timeval *var)
{
	asm volatile ("mov $96, %rax;"
		"mov -8(%rsp), %rdi;"
		"xor %rsi, %rsi;"
		"syscall");
	(void)var;
}

int main(void)
{
	struct s_timeval	caca;

	mytime(&caca);
	printf("%lu|%ld\n", caca.sec, caca.nano);
}
