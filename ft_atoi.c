/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imannouc <imannouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 13:33:48 by imannouc          #+#    #+#             */
/*   Updated: 2021/11/17 19:29:41 by imannouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	n_sign(char c, int *i, int *sign)
{
	int	a;

	a = *i;
	if (c == '-' || c == '+')
	{
		if (c == '-')
			*sign = -1;
		a++;
		*i = a;
	}
}

int	ft_atoi(const char *str)
{
	int				sign;
	unsigned int	result;
	int				i;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] == 32) || (str[i] >= 7 && str[i] <= 13))
		i++;
	n_sign(str[i], &i, &sign);
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		if (result > 2147483647 && sign == -1)
			return (0);
		else if (result > 2147483648 && sign == 1)
			return (-1);
		else
		{
			result = result * 10 + (str[i] - '0');
			i++;
		}
	}
	return (sign * result);
}
