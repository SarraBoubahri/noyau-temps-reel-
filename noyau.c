 /*----------------------------------------------------------------------------*
 * fichier : noyau.c                                                          *
 * mini noyau temps reel fonctionnant sur MC9328MXL                           *
 * ce fichier definit toutes les fonctions du noyau                           *
 *----------------------------------------------------------------------------*/

#include <stdint.h>

#include "hwsupport/stm32h7xx.h"
#include "io/serialio.h"
#include "kernel/noyau.h"
#include "kernel/noyau_file.h"

/*--------------------------------------------------------------------------*
 *           Constantes pour la création du contexte CPU initial            *
 *--------------------------------------------------------------------------*/
#define THUMB_ADDRESS_MASK (0xfffffffe) /* Masque pointeurs de code Thumb   */
#define TASK_EXC_RETURN (0xfffffff9)    /* Valeur de retour d'exception :   */
                                        /* msp active, mode Thread          */
#define TASK_PSR (0x01000000)           /* PSR initial                      */

/*--------------------------------------------------------------------------*
 *            Variables internes du noyau                                   *
 *--------------------------------------------------------------------------*/
static int compteurs[MAX_TACHES]; /* Compteurs d'activations                */
NOYAU_TCB  _noyau_tcb[MAX_TACHES]; /* tableau des contextes                 */
volatile uint16_t _tache_c;     /* numéro de tache courante                 */
uint32_t _tos;                  /* adresse du sommet de pile des tâches     */

/*--------------------------------------------------------------------------*
 * fonctions du noyau                                                       *
 *--------------------------------------------------------------------------*/

/*
 * termine l'execution du noyau
 * entre  : sans
 * sortie : sans
 * description : termine l'execution du noyau, execute en boucle une
 *               instruction vide
 */
 void noyau_exit(void) {
    /* Q2.1 : desactivation des interruptions */                         
    /* affichage du nombre d'activation de chaque tache !                   */
    printf("Sortie du noyau\n");
    for (int j = 0; j < MAX_TACHES; j++) {
        printf("\nActivations tache %d : %d", j, compteurs[j]);
    }
    /* Q2.2 : Que faire quand on termine l'execution du noyau ? */

}

/*
 * termine l'execution d'une tache
 * entre  : sans
 * sortie : sans
 * description : une tâche dont l'execution se termine n'est plus exécutée
 *               par le noyau
 *               cette fonction doit être appelée à la fin de chaque tâche
 */
 void fin_tache(void) {
    /* Q2.3 :             Début section critique                             */

    /* Q2.4 : la tâche est enlevée de la file des tâches et ... ?            */
    /* 4 instructions */




}

/*
 * demarrage du system en mode multitache
 * entre  : adresse de la tache a lancer
 * sortie : sans
 * description : active la tache et lance le scheduler
 */
 void start(TACHE_ADR adr_tache) {
    uint16_t j;
    register unsigned int sp asm("sp");

    /* Q2.5 : initialisation de l'etat des taches                            */
    for (j = 0; j < MAX_TACHES; j++) {
        
    }
    /* Q2.6 : initialisation de la tache courante */
    _tache_c = ????;
    /* initialisation de la file circulaire de gestion des tâches           */                  
    file_init();                     
    /* Q2.7 : initialisation de la variable _tos sommet de la pile           */
    /* Haut de la pile des tâches avec réservation  pour le noyau           */
    _tos = ?????;

    /* Q2.8 : on interdit les interruptions  */
    
    /* Q2.9 : initialisation du timer system a 100 Hz   (voir cortex.c)        */
    
    /* Q2.10 : initialisation de l'interruption systick  (voir cortex.c) */
    
    /* Q2.11 : creation et activation de la premiere tache                          */
    
    /* Q2.12 : on autorise les interruptions */

}

/*
 * creation d'une nouvelle tache
 * entre  : adresse de la tache a creer
 * sortie : numero de la tache cree
 * description : la tache est creee en lui allouant une pile et un numero
 *               en cas d'erreur, le noyau doit etre arrete
 * Err. fatale: priorite erronnee, depassement du nb. maximal de taches 
 */
 uint16_t cree(TACHE_ADR adr_tache){
    /* pointeur d'une case de _contexte         */
    NOYAU_TCB *p;               
    /* Q2.13 : numero de la derniere tache créée */ 
    static uint16_t tache = -1; 
    
    /* Q2.14: debut section critique */
    
    /* Q2.15 : generation du numero de la tache suivante */
                
    /* Q2.16 : arret du noyau si plus de MAX_TACHES^*/
    
    

    /* creation du contexte de la nouvelle tache */
    p = &_noyau_tcb[tache];    
    /* Q2.17 : allocation d'une pile a la tache */ 
     
    /* Q2.18 : decrementation du pointeur de pile general, afin que la prochaine tache */
	/* n'utilise pas la pile allouee pour la tache courante */
            
    /* Q2.19 : memorisation de l'adresse de debut de la tache */
   
    /* Q2.20 : mise a jour de l'etat de la tache a CREE */
    
    /* Q2.21 : fin section critique */
    

    return (tache); /* tache est un uint16_t */
}

/*
 * ajout d'une tache pouvant etre executee a la liste des taches eligibles
 * entre  : numero de la tache a ajouter
 * sortie : sans
 * description : ajouter la tache dans la file d'attente des taches eligibles
 *               en cas d'erreur, le noyau doit etre arrete
 */
 void active(uint16_t tache){
    NOYAU_TCB *p = &_noyau_tcb[tache]; /* acces au contexte tache             */

    /* Q2.22 : verifie que la tache n'est pas dans l'etat NCREE, sinon arrete le noyau*/
    
    


    /* Q2.23 : debut section critique */
    
    
    /* Q2.24 : activation de la tache seulement si elle est a l'état CREE */
    if (p->status == CREE) {        /* n'active que si receptif             */
        /* Q228 : Créer un contexte initial en haut de la pile de la nouvelle tâche */
                                    /* Réserver la Place pour le contexte sur la pile de la tâche  */
                                    /* Aligner au multiple de 8 inférieur   */
        /* initialisation d'un pointeur sur le début de l'espace de sauvegarde du contexte */
        CONTEXTE_CPU_BASE *c = (CONTEXTE_CPU_BASE*) p->sp_ini; 
                                    /* Adresse de la tâche dans pc, attention au bit de poids faible*/
                                    /* Adresse de retour de la tâche dans lr */
                                    /* veleur initiale de retour d'exeption dans lr_exc */
                                    /* veleur initiale des flags dans psr */
        
    
                                    /* changement d'etat, mise a l'etat PRET*/
                                    /* ajouter la tache dans la liste       */
                                    /* activation d'une tache prete         */
    }
    /* Q2.25 : fin section critique */
                 
}

/*--------------------------------------------------------------------------*
 *                  ORDONNANCEUR preemptif optimise                         *
 * Entrée : pointeur de contexte CPU de la tâche courante                   *
 * Sortie : pointeur de contexte CPU de la nouvelle tâche courante          *
 * Descrip: sauvegarde le pointeur de contexte de la tâche courante,        *
 *      Élit une nouvelle tâche et retourne son pointeur de contexte.       *
 *      Si aucune tâche n'est éligible, termine l'exécution du noyau.       *
 *--------------------------------------------------------------------------*/
uint32_t task_switch(uint32_t sp)
{
    NOYAU_TCB *p = &_noyau_tcb[_tache_c]; /* acces au contexte tache courante */

    /* Q2.26 : sauvegarde du pointeur sur le contexte sauvegardé sur la pile 
       dans le contexte de la tache */
                   
    /* on bascule sur la nouvelle tache a executer */
    /* Q2.27 : recherche la prochaine tache a executer */

    /* Q2.28 : acces contexte suivant                   */
   
    /* Q2.29 : verifie qu'une tache suivante existe, sinon arret du noyau */
    



    /* incrémentation du compter d'activation de la nouvelle tache */
    compteurs[_tache_c]++;   
    /* Q2.30 : retourner la bonne valeur de pointeur de pile 
     Deux cas possible en fonction du statut de la tâche */





}

/*--------------------------------------------------------------------------*
 *              --- Gestionnaire d'exception PEND SVC ---                   *
 * Descrip: Appelé lors de l'exception PEND SVC provoquée par pendsv_trigger*
 *      Sauvegarde le contexte CPU sur la pile de la tâche et provoque une  *
 *      commutation de contexte.                                            *
 *------------------------------------------------------------------------- */
void __attribute__((naked)) _pend_svc(void) {
    /* Q2.31 : sauvegarde du complément de contexte et appel de
                 l'ordonnaceur */
    __asm__ __volatile__ (
                                    /* Sauvegarder le complément de  contexte    
                                       sur la pile                          */
                                    /* r0 = 1er paramètre de task_switch    */
                                    /* Commutation de contexte              */
                                    /* r0 = valeur de retour de task_switch
                                       dans ? */
                                    /* Restituer le contexte                */
                                    /* Retour d'exception                   */
    );
}

/*--------------------------------------------------------------------------*
 *                  --- Provoquer une commutation ---                       *
 *                                                                          *
 * Descrip: planifie une exception PEND SVC pour forcer une commutation     *
 *      de tâche                                                            *
 *--------------------------------------------------------------------------*/
void schedule(void)
{
    pendsv_trigger();
}



/*
 * endort la tache courante
 * entre  : sans
 * sortie : sans
 * description : endort la tache courante et lance l'execution d'une nouvelle
 *               tache
 */
 void dort(void) {
   
}

/*
 * reveille une tache
 * entre  : numero de la tache a reveiller
 * sortie : sans
 * description : reveille une tache
 *               en cas d'erreur, le noyau doit etre arrete
 */
 void reveille(uint16_t t) {
    
}
