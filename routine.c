/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:54:16 by hibenouk          #+#    #+#             */
/*   Updated: 2024/07/30 15:31:00 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

static void eating(t_philo *philo)
{
	if (table_status(philo, GET) == 0)
		return ;
	print_state(philo, EAT);
	eat_time(philo, SET);
	custom_sleep(philo, philo->data->time_to_eat);
}

static void sleeping(t_philo *philo)
{
	if (table_status(philo, GET) == 0)
		return ;
	print_state(philo, SLEEP);
	custom_sleep(philo, philo->data->time_to_sleep);
}

static void thinking(t_philo *philo)
{
	if (table_status(philo, GET) == 0)
		return ;
	print_state(philo, THINK);
	if (philo->data->count & 1)
		custom_sleep(philo, (2 * philo->data->time_to_eat - philo->data->time_to_sleep) * 0.5);
}

void *routine(void *param)
{
	t_philo *philo;

	philo = param;
	while (table_status(philo, GET))
	{
		take_forks(philo);
		eating(philo);
		put_forks(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
