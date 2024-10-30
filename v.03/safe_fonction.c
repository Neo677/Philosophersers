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

/*
    module containing wrapper functions  with embedded controls on return 

*/

void *safe_malloc(size_t bytes)
{
    void    *res;

    res = malloc(bytes);
    if (res ==  NULL)
        error_exit("Error with the malloc");
    return (res);
}

// embed controls on return status
static void handle_mutex_error(int status, t_opcode opcode)
{
    if (status == 0)
        return ;
    if (status == EINVAL &&  (opcode == LOCK || UNLOCK == opcode)) 
        error_exit("The value specified by mutex is invalid");
    else if (status == EINVAL && opcode == INIT)
        error_exit("The value specified by attr is invalid");
    else if (status == EDEADLK)
        error_exit("A deadlock would occur if the thread blocked waiting for mutex.");
    else if (status == EPERM)
        error_exit("The current thread does not hold a lock on mutex");
    else if (status == ENOMEM)
        error_exit("The process cannot allocate enough memory to create another mutex");
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
void    safe_mutex_handle(t_mutex *mutex, t_opcode opcode)
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

// thread error
static void handle_thread_error(int status, t_opcode opcode)
{
    if (status == 0)
        return ;
    if (status == EAGAIN) 
        error_exit("No ressource to create another thread");
    else if (status == EPERM)
        error_exit("The caller does not have appropriates permissions\n");
    else if (status == EINVAL && opcode == CREATE)
        error_exit("The value specified by attr is invalid.");
    else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
        error_exit("The value specified by thread is not joinable\n");
    else if (status == ESRCH)
        error_exit("No thread could be found corresponding to that" "specified by the given thread ID, thread.");
    else if (status == EDEADLK)
        error_exit("A deadlock was detected or the value of" "thread specifies the calling thread.");
}

/*
    One fonction to control thread 
        create, join, detach
	 wrapper fonction    ptr to thread data type / ptr to fonction / ptr to data / ptr opcode struct  
*/                          
//      
void    safe_thread_handle(t_mutex *thread, void *(*foo)(void *), void *data, t_opcode opcode)
{
    if (opcode == CREATE)
        handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
    else if (opcode == JOIN)
        handle_thread_error(pthread_join(*thread, NULL), opcode);
    else if (opcode == DETACH)
        handle_thread_error(pthread_detach(*thread), opcode);
    else
        error_exit("Wrong opcode for thread_handle:" "Use <CREATE> <JOIN> <DETACH>");
}
