/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:12:01 by thobenel          #+#    #+#             */
/*   Updated: 2024/10/23 19:12:03 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Déclaration globale du mutex et du solde du compte
// pthread_mutex_t mutex;
// int account_balance = 0;

#define NC "\e[0m"
#define YELLOW "\e[33m"
#define BYELLOW "\e[1;33m"
#define RED "\e[31m"
#define GREEN "\e[32m"

#define TIMES_TO_COUNT 21000


typedef struct s_count
{
    pthread_mutex_t count_mutex;
    unsigned int count;
} t_count;

typedef struct s_lock
{
	pthread_mutex_t lock1;
	pthread_mutex_t lock2;
	unsigned int count;
}				t_lock;

// void	*routine_of_thread(void	*data)
// {
// 	pthread_t id;
// 	t_count *counter;
// 	unsigned int i;

// 	id = pthread_self();
// 	counter = (t_count *)data;

// 	pthread_mutex_lock(&counter->count_mutex);
// 	printf("%sthread [%ld]: compte au depart = %u.%s\n", YELLOW, id, counter->count, NC);
// 	pthread_mutex_unlock(&counter->count_mutex);

// 	i = 0;
// 	while(i < TIMES_TO_COUNT)
// 	{
// 		pthread_mutex_lock(&counter->count_mutex);
// 		counter->count++;
// 		pthread_mutex_unlock(&counter->count_mutex);
// 		i++;
// 	}
// 	pthread_mutex_lock(&counter->count_mutex);
// 	printf("%sthread [%ld]: Compte final = %u.%s\n", BYELLOW, id, counter->count, NC);
// 	pthread_mutex_unlock(&counter->count_mutex);
// 	return (NULL);
// }

void	*thread_routine_1(void *data)
{
	pthread_t id;
	t_lock *locker;

	id = pthread_self(); // recup id du thread
	locker = (t_lock *)data;

	printf("%sthread [%ld]: veut verouiller lock 1%s\n", YELLOW, id, NC);
	pthread_mutex_lock(&locker->lock1);

	printf("%sthread [%ld]: possed lock 1%s\n", BYELLOW, id, NC);
	printf("%sthread [%ld]: veut verouiller lock 2%s\n", YELLOW, id, NC);
	pthread_mutex_lock(&locker->lock2);
	printf("%sthread [%ld]: possede lock 2%s\n", BYELLOW, id, NC);
	locker->count += 1;
	printf("%sthread [%ld]: deverouiller lock 2%s\n", BYELLOW, id, NC);
	pthread_mutex_unlock(&locker->lock2);
	printf("%sthread [%ld]: deverouiller lock 1%s\n", BYELLOW, id, NC);
	pthread_mutex_unlock(&locker->lock1);
	printf("%sthread [%ld]: termine %s\n", YELLOW, id, NC);
	return (NULL);
}

void	*thread_routine_2(void *data)
{
	pthread_t id;
	t_lock *locker;

	id = pthread_self(); // recup id du thread
	locker = (t_lock *)data;

	printf("%sthread [%ld]: veut verouiller lock 2%s\n", YELLOW, id, NC);
	pthread_mutex_lock(&locker->lock2);

	printf("%sthread [%ld]: possed lock 2%s\n", BYELLOW, id, NC);
	printf("%sthread [%ld]: veut verouiller lock 1%s\n", YELLOW, id, NC);
	pthread_mutex_lock(&locker->lock1);
	printf("%sthread [%ld]: possede lock 1%s\n", BYELLOW, id, NC);
	locker->count += 1;
	printf("%sthread [%ld]: deverouiller lock 1%s\n", BYELLOW, id, NC);
	pthread_mutex_unlock(&locker->lock1);
	printf("%sthread [%ld]: deverouiller lock 2%s\n", BYELLOW, id, NC);
	pthread_mutex_unlock(&locker->lock2);
	printf("%sthread [%ld]: termine %s\n", YELLOW, id, NC);
	return (NULL);
}

int main(void)
{
	pthread_t id1;
	pthread_t id2;

	t_lock locker;

	locker.count = 0;
	pthread_mutex_init(&locker.lock1, NULL);
	pthread_mutex_init(&locker.lock2, NULL);

	pthread_create(&id1, NULL, thread_routine_1, &locker);
	printf("Main: creation du premier thread [%ld]\n", id1);
	pthread_create(&id2, NULL, thread_routine_2, &locker);
	printf("Main: creation du second thread [%ld]\n", id2);

	pthread_join(id1, NULL);
	printf("Main: Union du premier thread [%ld]\n", id1);
	pthread_join(id2, NULL);
	printf("Main: Union du second thread [%ld]\n", id2);

	if (locker.count == 2)
		printf("%sMain: OK: Le compte est de %d\n", GREEN, locker.count);
	else
		printf("%sMain: ERREUR: Le compte est de %d\n", RED, locker.count);

	pthread_mutex_destroy(&locker.lock1);
	pthread_mutex_destroy(&locker.lock2);
	return (0);
}

// int main(void)
// {
// 	pthread_t id_1;
// 	pthread_t id_2;

// 	t_count counter;

// 	counter.count = 0;

// 	pthread_mutex_init(&counter.count_mutex, NULL);
// 	printf("Main: le compte attendu est %s%u%s\n", GREEN, 2 * TIMES_TO_COUNT, NC);

// 	pthread_create(&id_1, NULL, routine_of_thread, &counter);
// 	printf("Main: Creation du premier thread [%ld]\n", id_1);
// 	pthread_create(&id_2, NULL, routine_of_thread, &counter);
// 	printf("Main: Creation du premier thread [%ld]\n", id_2);

// 	pthread_join(id_1, NULL);
// 	printf("Main: Union du premier thread [%ld]\n", id_1);
// 	pthread_join(id_2, NULL);
// 	printf("Main: Union du deuxieme thread [%ld]\n", id_2);

// 	if (counter.count != (2 * TIMES_TO_COUNT))
// 		printf("%sMain: Erreur ! Le compte est de %u%s\n", RED, counter.count, NC);
// 	else
// 		printf("%sMain: Ok. Le compte est de %u%s\n", GREEN, counter.count, NC);
// 	pthread_mutex_destroy(&counter.count_mutex);
// 	return (0);
// }


// // Fonction pour lire le solde du compte
// int read_montant() {
//     int montant;
//     pthread_mutex_lock(&mutex);
//     montant = account_balance;
//     pthread_mutex_unlock(&mutex);
//     return montant;
// }

// void *depot(void *arg) {
//     int *montant = (int *)arg;

//     pthread_mutex_lock(&mutex);
//     account_balance += *montant;
//    // printf("Nouveau solde après dépôt de %d: %d\n", *montant, account_balance);
//     pthread_mutex_unlock(&mutex);

//     return NULL;
// }

// int main() {
//     pthread_t thread1, thread2, thread3;

//     // Initialiser le mutex
//     pthread_mutex_init(&mutex, NULL);

//     int depot1 = 53;
//     int depot2 = 5;
//     int depot3 = 5;

//     // Créer les threads
//     pthread_create(&thread1, NULL, depot, (void *)&depot1);
// 	pthread_create(&thread2, NULL, depot, (void *)&depot2);
// 	pthread_create(&thread3, NULL, depot, (void *)&depot3);

//     int transfert = read_montant();
//     printf("depot = %d\n", depot1);
//     printf("depot = %d\n", depot2);
//     printf("depot = %d\n", depot3);

// 	printf("montant = %d\n", );
//     // Attendre que les threads se terminent
//     pthread_join(thread1, NULL);
//     pthread_join(thread2, NULL);
//     pthread_join(thread3, NULL);




//     // Détruire le mutex
//     pthread_mutex_destroy(&mutex);

//     int total = read_montant();
//     printf("total montant = %d\n", total);

//     return 0;
// }