/*
 * Vorgabe für Aufgabenteil c (entspricht der Vorlage für Aufgabenteil b).
 * Diese Vorgabe soll für Aufgabenteil c modifiziert werden.
 */

/* Noetige Includes */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>

#include "main.h"

void init_semaphores(void){
	/**
	 * ! ! ! DIESE FUNKTION ANPASSEN ! ! !
	 */
	/*
	 * Semaphoren initialisieren.
	 */

	if(sem_init(&status, 0, 1) == -1){
		perror("Konnte Semaphore status nicht initialisieren");
		exit(EXIT_FAILURE);
	}

	if (sem_init(&klausuren, 0, 1) == -1) {
		perror("Konnte Semaphore klausuren nicht initialisieren");
		exit(EXIT_FAILURE);
	}
	if (sem_init(&liste, 0, 1) == -1) {
		perror("Konnte Semaphore liste nicht initialisieren");
		exit(EXIT_FAILURE);
	}
	/* Ende des zu modifizierenden Bereichs in dieser Funktion */
}


/*
 * Die Funktion der beiden Threads (Mitarbeiter_A und Mitarbeiter_B).
 */
void *mitarbeiter_a(void *arg) {
	char name = 'A';

	printf("Mitarbeiter %c: Ich fange jetzt an.\n", name);
	sleep(1);

	while (1) {
		/**
		 * ! ! ! DIESE FUNKTION AB HIER ANPASSEN ! ! !
		 */
		/**
		 * Der Mitarbeiter führt eine andere Arbeit aus.
		 */

		printf("Mitarbeiter %c: Jetzt arbeite ich an etwas anderem.\n", name);
		
		if(sem_wait(&status) == -1){
			perror("Sem wait");
			exit(EXIT_FAILURE);
		}
		mitarbeiter_a_status = andere_arbeit;
		if(sem_post(&status) == -1){
			perror("Sem post");
			exit(EXIT_FAILURE);
		}

		andere_arbeit_ausfuehren(name);
		 
		/* 
		 * Klausuren holen.
		 */
		printf("Mitarbeiter %c: Ich hole mir jetzt die Klausuren.\n", name);

		if(sem_wait(&status) == -1){
			perror("Sem wait");
			exit(EXIT_FAILURE);
		}
		mitarbeiter_a_status = hole_klausuren;
		if(sem_post(&status) == -1){
			perror("Sem post");
			exit(EXIT_FAILURE);
		}

		if(sem_wait(&klausuren) == -1) {
			perror("Fehler beim Reservieren der Klausuren");
			exit(EXIT_FAILURE);
		}
		sleep(4);
		printf("Mitarbeiter %c: Ich habe die Klausuren.\n", name);

		/* 
		 * Liste  holen.
		 */
		printf("Mitarbeiter %c: Ich hole mir jetzt die Liste.\n", name);

		if(sem_wait(&status) == -1){
			perror("Sem wait");
			exit(EXIT_FAILURE);
		}
		mitarbeiter_a_status = hole_liste;
		if(sem_post(&status) == -1){
			perror("Sem post");
			exit(EXIT_FAILURE);
		}

		if(sem_wait(&liste) == -1) {
			perror("Fehler beim Reservieren der Liste");
			exit(EXIT_FAILURE);
		}
		sleep(3);
		printf("Mitarbeiter %c: Ich habe die Liste.\n", name);
		
		/* 
		 * Korrigieren.
		 */
		printf("Mitarbeiter %c: Ich korrigiere jetzt.\n", name);

		if(sem_wait(&status) == -1){
			perror("Sem wait");
			exit(EXIT_FAILURE);
		}
		mitarbeiter_a_status = korrigieren;
		if(sem_post(&status) == -1){
			perror("Sem post");
			exit(EXIT_FAILURE);
		}

		sleep(5);
		
		/* 
		 * Liste zurueckbringen.
		 */
		printf("Mitarbeiter %c: Jetzt bringe ich die Liste zurueck.\n", name);
		if (sem_post(&liste) == -1) {
			perror("Konnte Semaphore liste nicht freigeben");
			exit(EXIT_FAILURE);
		}
		
		/* 
		 * Klausuren zurueckbringen.
		 */
		 printf("Mitarbeiter %c: Jetzt bringe ich die Klausuren zurueck.\n", name);
		if (sem_post(&klausuren) == -1) {
			perror("Konnte Semaphore klausuren nicht freigeben");
			exit(EXIT_FAILURE);
		}
		/* Ende des zu modifizierenden Bereichs in dieser Funktion */
	}
	pthread_exit(NULL);
}

void *mitarbeiter_b(void *arg) {
	char name = 'B';

	printf("Mitarbeiter %c: Ich fange jetzt an.\n", name);

	while (1) {
		/**
		 * ! ! ! DIESE FUNKTION AB HIER ANPASSEN ! ! !
		 */
		/**
		 * Der Mitarbeiter fuehrt eine andere Arbeit aus.
		 */
		printf("Mitarbeiter %c: Jetzt arbeite ich an etwas anderem.\n", name);

		if(sem_wait(&status) == -1){
			perror("Sem wait");
			exit(EXIT_FAILURE);
		}
		mitarbeiter_b_status = andere_arbeit;
		if(sem_post(&status) == -1){
			perror("Sem post");
			exit(EXIT_FAILURE);
		}

		andere_arbeit_ausfuehren(name);
		
		/* 
		 * Liste  holen.
		 */
		printf("Mitarbeiter %c: Ich hole mir jetzt die Liste.\n", name);

		if(sem_wait(&status) == -1){
			perror("Sem wait");
			exit(EXIT_FAILURE);
		}
		mitarbeiter_b_status = hole_liste;
		if(sem_post(&status) == -1){
			perror("Sem post");
			exit(EXIT_FAILURE);
		}

		if(sem_wait(&liste) == -1) {
			perror("Fehler beim Reservieren der Liste");
			exit(EXIT_FAILURE);
		}
		sleep(3);
		printf("Mitarbeiter %c: Ich habe die Liste.\n", name);
		
		/* 
		 * Klausuren holen.
		 */
		printf("Mitarbeiter %c: Ich hole mir jetzt die Klausuren.\n", name);

		if(sem_wait(&status) == -1){
			perror("Sem wait");
			exit(EXIT_FAILURE);
		}
		mitarbeiter_b_status = hole_klausuren;
		if(sem_post(&status) == -1){
			perror("Sem post");
			exit(EXIT_FAILURE);
		}

		if(sem_wait(&klausuren) == -1) {
			perror("Fehler beim Reservieren der Klausuren");
			exit(EXIT_FAILURE);
		}
		sleep(4);
		printf("Mitarbeiter %c: Ich habe die Klausuren.\n", name);
		
		/* 
		 * Korrigieren.
		 */
		printf("Mitarbeiter %c: Ich korrigiere jetzt.\n", name);

		if(sem_wait(&status) == -1){
			perror("Sem wait");
			exit(EXIT_FAILURE);
		}
		mitarbeiter_b_status = korrigieren;
		if(sem_post(&status) == -1){
			perror("Sem post");
			exit(EXIT_FAILURE);
		}

		sleep(5);
		
		/* 
		 * Klausuren zurueckbringen.
		 */
		 printf("Mitarbeiter %c: Jetzt bringe ich die Klausuren zurueck.\n", name);
		if (sem_post(&klausuren) == -1) {
			perror("Konnte Semaphore klausuren nicht freigeben");
			exit(EXIT_FAILURE);
		} 
		
		/* 
		 * Liste zurueckbringen.
		 */
		printf("Mitarbeiter %c: Jetzt bringe ich die Liste zurueck.\n", name);
		if (sem_post(&liste) == -1) {
			perror("Konnte Semaphore liste nicht freigeben");
			exit(EXIT_FAILURE);
		}
		 
		/* Ende des zu modifizierenden Bereichs in dieser Funktion */
	}
	pthread_exit(NULL);
}


/*
 * Die Funktion des Vaterprozesses.
 * Hier findet die deadlock_erkennung und -beseitigung statt.
 */
void check_for_deadlocks(void) { 
	/* Diese beiden Variablen könnten für euch nützlich sein: */
	enum STATUS aktueller_status_a;
	enum STATUS aktueller_status_b;
		
	/**
	 * ! ! ! HIER EUREN CODE EINFÜGEN ! ! !
	 */

	if(sem_wait(&status) == -1){
		perror("Sem wait");
		exit(EXIT_FAILURE);
	}
	aktueller_status_a = mitarbeiter_a_status;
	aktueller_status_b = mitarbeiter_b_status;
	if(sem_post(&status) == -1){
			perror("Sem post");
			exit(EXIT_FAILURE);
	}

	if(aktueller_status_a == hole_liste && aktueller_status_b == hole_klausuren){
		printf("Verklemmung!");
	}
	else{
		printf("Alles ist im Ordnung.");
	}

	/* Ende des zu modifizierenden Bereichs in dieser Funktion */
	return;
}
