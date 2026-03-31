/*----------------------------------------------------------------------------*
 * fichier : noyau_file.c                                                     *
 * gestion de la file d'attente des taches pretes et actives                  *
 * la file est rangee dans un tableau. ce fichier definit toutes              *
 * les primitives de base                                                     *
 *----------------------------------------------------------------------------*/

#include <stdint.h>
#include "kernel/noyau_file.h"

// recuperation du bon fichier selon l'architecture pour la fonction printf
#include "io/serialio.h"
#include <stdio.h>
#include <assert.h>


/*----------------------------------------------------------------------------*
 * variables communes a toutes les procedures                                 *
 *----------------------------------------------------------------------------*/

static uint16_t _file[MAX_TACHES];
static uint16_t _queue;

/*----------------------------------------------------------------------------*
 * fonctions de gestion de la file                                            *
 *----------------------------------------------------------------------------*/

void file_init(void) {
    _queue = F_VIDE;
}

void file_ajoute(uint16_t n) {
    uint16_t courant;

    if (_queue == F_VIDE) {
        _queue = n;
        _file[n] = n;
        return;
    }

    courant = _queue;

    while (_file[courant] != _queue) {
        courant = _file[courant];
    }

    _file[courant] = n;
    _file[n] = _queue;
}

void file_retire(uint16_t t) {
    uint16_t courant, precedent;

    if (_queue == F_VIDE) {
        return;
    }

    if (_queue == t && _file[_queue] == _queue) {
        _queue = F_VIDE;
        return;
    }

    courant = _queue;
    precedent = _queue;

    while (_file[courant] != t && _file[courant] != _queue) {
        courant = _file[courant];
    }

    if (_file[courant] != t) {
        return;
    }

    precedent = courant;

    if (t == _queue) {
        _queue = _file[t];
    }

    _file[precedent] = _file[t];
}

uint16_t file_suivant(void) {
    uint16_t t;

    if (_queue == F_VIDE) {
        return F_VIDE;
    }

    t = _queue;
    _queue = _file[_queue];
    return t;
}

void file_affiche_queue() {
    printf("_queue = %d\n", _queue);
}

void file_affiche() {
    int i;

    printf("Tache | ");
    for (i = 0; i < MAX_TACHES; i++) {
        printf("%03d | ", i);
    }

    printf("\nSuivant | ");
    for (i = 0; i < MAX_TACHES; i++) {
        printf("%03d | ", _file[i]);
    }
    printf("\n");
}

/*
                                     TEST
 */

void test_file_init() {
    file_init();
    printf("test_file_init OK\n");
}

void test_file_ajoute() {
    file_init();

    file_ajoute(1);


    file_ajoute(2);


    printf("test_file_ajoute OK\n");
}

void test_file_suivant() {
    file_init();

    file_ajoute(1);
    file_ajoute(2);
    file_ajoute(3);

    int t = file_suivant();


    t = file_suivant();


    t = file_suivant();


    printf("test_file_suivant OK\n");
}

void test_file_retire() {
    file_init();

    file_ajoute(1);
    file_ajoute(2);
    file_ajoute(3);

    file_retire(2);



    printf("test_file_retire OK\n");
}

int main() {

    printf("===== TEST FILE =====\n");

    // TEST 1 : initialisation
    file_init();
    file_affiche_queue();

    // TEST 2 : ajout
    printf("\n--- Ajout ---\n");
    file_ajoute(1);
    file_affiche();

    file_ajoute(2);
    file_affiche();

    file_ajoute(3);
    file_affiche();

    // TEST 3 : suivant
    printf("\n--- Suivant ---\n");
    printf("Suivant: %d\n", file_suivant());
    file_affiche_queue();

    printf("Suivant: %d\n", file_suivant());
    file_affiche_queue();

    printf("Suivant: %d\n", file_suivant());
    file_affiche_queue();

    // TEST 4 : retrait
    printf("\n--- Retire ---\n");
    file_retire(2);
    file_affiche();

    file_retire(1);
    file_affiche();

    file_retire(3);
    file_affiche();

    // TEST 5 : cas limite (file vide)
    printf("\n--- File vide ---\n");
    printf("Suivant: %d\n", file_suivant());

    printf("\n===== FIN TEST =====\n");

    return 0;
}

