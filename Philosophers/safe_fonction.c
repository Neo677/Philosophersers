/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_fonction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:07:48 by thobenel          #+#    #+#             */
/*   Updated: 2024/10/30 14:07:50 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*res;

	res = malloc(bytes);
	if (!res)
		error_exit("Error with the malloc");
	return (res);
}

// embed controls on return status
static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (opcode == LOCK || UNLOCK == opcode))
		error_exit("The value specified by mutex is invalid");
	else if (status == EINVAL && opcode == INIT)
		error_exit("The value specified by attribute is invalid");
	else if (status == EDEADLK)
		error_exit("A deadlock if the thread blocked waiting for mutex");
	else if (status == EPERM)
		error_exit("The current thread does not hold a lock on mutex");
	else if (status == ENOMEM)
		error_exit("The process cant allocate engh memory for create mutex");
	else if (status == EBUSY)
		error_exit("Mutex is lock");
}

/*
    Mutex safe = 
        init
        destroy
        lock
        unlock
*/
void	safe_mutex_handle(t_mutex *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("Wrong opcode for mutex handle");
}

//                *****thread*****

static void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_exit("\nSystem lacked necessary RCS to create another thread\n");
	else if (status == EPERM)
		error_exit("\nNot appropriate permission to set the required\n");
	else if (status == EINVAL && opcode == CREATE)
		error_exit("\nThe value specified by attr is invalid.\n");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		error_exit("\nValue not refer to a joinable thread\n");
	else if (status == ESRCH)
		error_exit("\nNo thread found by thread ID\n");
	else if (status == EDEADLK)
		error_exit("\ndeadlock value-the calling thread\n");
}

/*
    One fonction to control thread 
        create, join, detach
	 wrapper fonction   pointeur to thread data type 
	 					pointeur to fonction
						pointeur to data
						pointeur opcode struct  
*/

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
							void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (opcode == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("Wrong opcode for thread_handle:"
			"Use <CREATE> <JOIN> <DETACH>");
}
