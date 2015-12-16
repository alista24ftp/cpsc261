#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NAPTIME 25000 
#define NPHILOSOPHERS 5
#define NMEALS 3
#define VERBOSE 1

typedef struct philosophers {
	int id;
} philosopher;

typedef struct chopsticks {
	int isFree;
	pthread_mutex_t lock;// = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t forkcond;
} chopstick;

chopstick f[NPHILOSOPHERS];
philosopher phil[NPHILOSOPHERS];

//initialize all forks to be free for use
void init(void){
	int i;
	for(i=0; i<NPHILOSOPHERS; i++){
		f[i].isFree = 1; //1 - free, 0 - used
		f[i].lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
		f[i].forkcond = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
		phil[i].id = i;
	}
}

int indexOfLfork(philosopher p){
	return p.id;
}

int indexOfRfork(philosopher p){
	return (p.id + 1) % NPHILOSOPHERS;
}

void takeNap(void){
	usleep(random() % NAPTIME);
}

int pickup(int index){
	pthread_mutex_lock(&(f[index].lock));
	if(!f[index].isFree){
		pthread_mutex_unlock(&(f[index].lock));
		return 1;
	}
	f[index].isFree = 0; //no longer free to use
	pthread_mutex_unlock(&(f[index].lock));
	return 0;
}

void putdown(int index){
	pthread_mutex_lock(&(f[index].lock));
	f[index].isFree = 1; //now free to use
	pthread_mutex_unlock(&(f[index].lock));
	
}

const long DOLOCK = 1;

void *activity(void *args){
	int i;
	philosopher p;
	p.id = *(int *)args;
	int randfork[2] = {indexOfLfork(p), indexOfRfork(p)};
	int randnum, fork1, fork2;

	for(i=0; i<NMEALS; i++) {

		randnum = rand() % 2;
		fork1 = randfork[randnum];
		fork2 = randfork[(randnum + 1) % 2];
		
		takeNap();
		if(pickup(fork1) > 0){
			i--;
			continue;
		}
#if VERBOSE==1
		printf("philosopher %d picked up fork %d\n", p.id, fork1);
#endif
		takeNap();
		if(pickup(fork2) > 0){
			putdown(fork1);
			printf("philosopher %d gives up and tries again...\n", p.id);
			i--;
			continue;
		}
#if VERBOSE == 1
		printf("philosopher %d picked up fork %d\n", p.id, fork2);
		printf("philosopher %d eats\n", p.id);
#endif
		takeNap();
		putdown(fork1);
		putdown(fork2);
#if VERBOSE == 1
		printf("philosopher %d put down both forks and finishes meal %d\n", p.id, i);
#endif
	}

#if VERBOSE == 1
	printf("philosopher %d exits\n", p.id);
#endif
	pthread_exit((void *)0);
}

int main(int argc, char **argv){
	int i;
	pthread_t threads[NPHILOSOPHERS];

	srandom(time(0));
	init();
	
	for(i=0; i<NPHILOSOPHERS; i++){
		pthread_create(&threads[i], NULL, activity, &(phil[i].id));
	}

	for(i=0; i<NPHILOSOPHERS; i++){
		pthread_join(threads[i], NULL);
	}
	
	return 0;
}
