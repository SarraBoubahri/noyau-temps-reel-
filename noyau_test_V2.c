/*----------------------------------------------------------------------------*
 * fichier : noyau_test.c                                                     *
 * programme de test du noyaut                                                *
 *----------------------------------------------------------------------------*/


#include "kernel/noyau.h"
#include "hwsupport/stm_uart.h"
#include "io/serialio.h"
#include "io/TERMINAL.h"

TACHE	tacheA(void);
TACHE	tacheB(void);
TACHE	tacheC(void);
TACHE	tacheD(void);

#define MAX_CARA_LIGNE 80

uint16_t pos_x = 1;
uint16_t pos_y = 10;

TACHE	tacheA(void)
{
  SET_CURSOR_POSITION(3,1);
  puts("------> EXEC tache A");

  active(cree(tacheB));
  active(cree(tacheC));
  active(cree(tacheD));
  fin_tache();
}

TACHE	tacheB(void)
{
  int i=0;
  long j;
  SET_CURSOR_POSITION(4,1);
  puts("------> DEBUT tache B\n");
  SAVE_CURSOR_POSITION();
  while (1) {
    for (j=0; j<300000L; j++);
    if (pos_x > MAX_CARA_LIGNE) {pos_x = 1; pos_y = pos_y+1;}
    SET_CURSOR_POSITION(pos_y,pos_x);
    printf("%s%dm B%4d%s",CODE_BACKGROUND_COLOR, 20, i, CODE_RESET_COLOR);
    pos_x = pos_x + 6;
    i++;
  }
}

TACHE	tacheC(void)
{
  int i=0;
  long j;
  SET_CURSOR_POSITION(5,1);
  puts("------> DEBUT tache C\n");
  SAVE_CURSOR_POSITION();
  while (1) {
    for (j=0; j<600000L; j++);
    if (pos_x > MAX_CARA_LIGNE) {pos_x = 1; pos_y = pos_y+1;}
    SET_CURSOR_POSITION(pos_y,pos_x);

    printf("%s%dm C%4d%s",CODE_BACKGROUND_COLOR, 30, i, CODE_RESET_COLOR);
    pos_x = pos_x + 6;
    i++;
  }
}

TACHE	tacheD(void)
{
  int i=0;
  long j;
  SET_CURSOR_POSITION(6,1);
  puts("------> DEBUT tache C\n");
  SAVE_CURSOR_POSITION();
  while (1) {
    for (j=0; j<1200000L; j++);
    if (pos_x > MAX_CARA_LIGNE) {pos_x = 1; pos_y = pos_y+1;}
    SET_CURSOR_POSITION(pos_y,pos_x);

    printf("%s%dm D%4d%s",CODE_BACKGROUND_COLOR, 127, i, CODE_RESET_COLOR);
    pos_x = pos_x + 6;
    i++;
    if (i==40) noyau_exit();
  }
}

int main()
{
  usart_init(115200);
  CLEAR_SCREEN(1);
  SET_CURSOR_POSITION(1,1);
  puts("Test noyau");
  puts("Noyau preemptif");
  SET_CURSOR_POSITION(5,1)
  SAVE_CURSOR_POSITION();
  start(tacheA);
  return(0);
}
