/*
 * Vorgabe für die Aufgabe. Nicht modifizieren!
 */ 
#ifndef __VORGABE_H__
#define __VORGABE_H__

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

/* Variablen fuer die beiden Mitarbeiter Threads */
extern pthread_t mitarbeiter_a_thread;
extern pthread_t mitarbeiter_b_thread;

/* Moegliche Status Werte eines Mitarbeiters */
enum STATUS {
	andere_arbeit,
	hole_klausuren, 
	hole_liste, 
	korrigieren};

/* Aktueller Status der beiden Mitarbeiter */
extern enum STATUS mitarbeiter_a_status;
extern enum STATUS mitarbeiter_b_status;

/* Semaphoren */
extern sem_t klausuren;
extern sem_t liste;
extern sem_t status;

/* Deklaration der Funktionen */
void init_semaphores(void);
void *mitarbeiter_a(void *);
void *mitarbeiter_b(void *);
void andere_arbeit_ausfuehren(char);
void check_for_deadlocks(void);
void deadlock_erkennung(void);
void programm_abbruch(int sig);




#endif
