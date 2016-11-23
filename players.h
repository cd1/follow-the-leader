#ifndef PLAYERS_H
#define PLAYERS_H

#include <stdbool.h>

extern const int PLAYER_NONE;

typedef struct {
    bool *players;
    unsigned int size;
} player_list;

player_list *players_new(unsigned int);
unsigned int players_active_count(player_list *);
int players_next_active(player_list *, int);
void players_set_inactive(player_list *, int);
void players_reset(player_list *);
void players_free(player_list *);

#endif
