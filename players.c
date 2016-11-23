#include <stdlib.h>

#include "players.h"

const int PLAYER_NONE = -1;

player_list *players_new(unsigned int size) {
    player_list *list = malloc(sizeof(player_list));
    list->players = malloc(sizeof(bool) * size);
    list->size = size;

    players_reset(list);

    return list;
}

unsigned int players_active_count(player_list *list) {
    unsigned int active_players = 0;

    int i;
    for (i = 0; i < list->size; i++) {
        if (list->players[i]) {
            active_players++;
        }
    }

    return active_players;
}

int players_next_active(player_list *list, int current_player) {
    int i;
    for (i = current_player + 1; i < list->size; i++) {
        if (list->players[i]) {
            return i;
        }
    }

    return PLAYER_NONE;
}

void players_set_inactive(player_list *list, int player) {
    list->players[player] = false;
}

void players_reset(player_list *list) {
    int i;
    for (i = 0; i < list->size; i++) {
        list->players[i] = true;
    }
}

void players_free(player_list *list) {
    free(list->players);
    free(list);
}
