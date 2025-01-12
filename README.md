Philosophers

Philosophers est un projet de l’école 42 qui met en œuvre un problème classique de concurrence : le problème des philosophes mangeant. Ce projet consiste à gérer plusieurs threads (philosophes) partageant des ressources limitées (fourchettes) de manière synchronisée, tout en évitant les blocages (deadlocks) et les conditions de compétition (race conditions).

Fonctionnalités
	Gestion de plusieurs philosophes via des threads.
	Synchronisation des accès aux ressources avec des mutex.
	Simulation d’un dîner où chaque philosophe mange, pense et dort.
	Gestion des cas limites tels que la famine ou les ressources insuffisantes.
	Respect des délais pour chaque action selon les paramètres fournis.
 

03/11/24 : Comprendre les concepts fondamentaux (threads et mutex)

Au début, j’ai dû comprendre ce qu’est un thread et comment il fonctionne. En résumé, un thread est une unité d’exécution légère qui permet d’exécuter plusieurs tâches en parallèle dans un même processus. Cela signifie que chaque philosophe est représenté par un thread, ce qui permet à chacun d’agir indépendamment.

Ensuite, j’ai découvert les mutex (mutual exclusion). Ce sont des objets utilisés pour protéger les sections critiques, c’est-à-dire les parties du code où plusieurs threads accèdent aux mêmes ressources partagées. Dans ce projet, les mutex sont utilisés pour gérer les fourchettes afin qu’elles ne soient pas prises simultanément par deux philosophes.

Fonctions utilisées :
	1.	pthread_create
Crée un thread pour chaque philosophe :

pthread_create(&thread_id, NULL, routine, &philosopher);

Ici, chaque philosophe exécute une routine définie pour manger, penser et dormir.

	2.	pthread_mutex_init
Initialise un mutex pour chaque fourchette :

pthread_mutex_init(&fork_mutex, NULL);


	3.	pthread_mutex_lock / pthread_mutex_unlock
Ces fonctions permettent à un philosophe de prendre et de relâcher une fourchette :

pthread_mutex_lock(&fork_mutex);
// Philosophe mange
pthread_mutex_unlock(&fork_mutex);


	4.	pthread_join
Attend la fin de l’exécution d’un thread :

pthread_join(thread_id, NULL);

11/11/24 

Implémentation de la routine des philosophes

Une fois les concepts maîtrisés, j’ai écrit la routine de base pour chaque philosophe. Chaque philosophe doit :
	1.	Prendre les deux fourchettes.
	2.	Manger.
	3.	Reposer les fourchettes.
	4.	Penser.

Cette routine a été implémentée dans la fonction routine, qui est exécutée par chaque thread.

16/11/24: Gestion de la synchronisation

J’ai ajouté une gestion stricte de la synchronisation pour éviter les problèmes suivants :
	Deadlock : Les philosophes bloquent en attendant indéfiniment une fourchette.
	Race condition : Deux philosophes essaient d’accéder à la même fourchette en même temps.

J’ai également ajouté un système de surveillance dans la fonction monitor, qui vérifie si un philosophe est mort de faim.

Fichiers principaux
	main.c : Point d’entrée du programme, initialisation des données.
	philo.h : Définition des structures et des prototypes.
	dinner_start.c : Lancement de la simulation des philosophes.
	routine.c : Routine des actions des philosophes.
	monitor.c : Surveillance de l’état des philosophes (famine, mort, etc.).
	safe_fonction.c : Fonctions sécurisées pour les actions critiques.
	write.c : Gestion des messages affichés.
	synchro_utils.c : Utilitaires pour la gestion des mutex et synchronisations.

Compilation

Pour compiler le projet, utilisez la commande suivante :
make

Cela génère l’exécutable philo.

Exécution

Lancez le programme avec les arguments suivants :
./philo <nb_philosophes> <time_to_die> <time_to_eat> <time_to_sleep> [nb_repasts]

Exemple :
./philo 5 800 200 200

Cela simule 5 philosophes, avec :
	800 ms avant qu’un philosophe ne meure de faim.
	200 ms pour manger.
	200 ms pour dormir.

Concepts clés

Threads

Un thread permet d’exécuter une tâche indépendante. Chaque philosophe est un thread qui exécute sa routine.

Mutex

Les mutex assurent que les fourchettes (ressources partagées) sont utilisées de manière sécurisée. Cela empêche deux philosophes de prendre la même fourchette.

Règles du Makefile
	make : Compile le projet.
	make clean : Supprime les fichiers objets.
	make fclean : Supprime les fichiers objets et l’exécutable.
	make re : Réexécute un nettoyage complet suivi d’une recompilation.

Crédits

Projet réalisé dans le cadre de l’école 42.

Merci de lire ce README !
Le projet Philosophers a été un défi intellectuel passionnant, et j’espère que vous prendrez autant de plaisir à explorer ce projet que j’en ai eu à le développer. Si vous avez des questions ou des suggestions, n’hésitez pas à me les partager. Bonne simulation ! 😊

N’hésitez pas à ajuster ou enrichir ce fichier en fonction de votre expérience ! 😊
