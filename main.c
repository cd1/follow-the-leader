#include <stdbool.h>
#include <stdio.h>

const int BOUNCE_THRESHOLD = 200;  // ms

const int TONE_ERROR = 100;
const int TONE_C = 16;
const int TONE_F = 21;
const int BUZZ_DURATION = 1000;  // ms

const int NO_NOTE = 0;
const int NOTE_C = 1;
const int NOTE_F = 2;

const int NO_PLAYER = -1;
const uint64_t PLAYER_TIMEOUT = 5000;  // ms

const int MAX_NOTES_COUNT = 64;

int main() {
    uart_setup();
    timer0_setup();
    button_pin2_setup();
    button_pin3_setup();
    buzzer_setup();
    sei();

reset:
    int *notes = malloc(MAX_NOTES_COUNT * sizeof(int));
    fprintf(&uart,
            "Welcome to the follow the leader game! Please enter the number of "
            "players: [2-9]\n");

number_of_players:
    uint8_t n_players;
    fscanf(&uart, "%d", &n_players);

    bool *players = malloc(n_players * sizeof(bool));

round_reset:
    uint16_t round = 1;
    int current_player = NO_PLAYER;
    int i;

    for (i = 0; i < MAX_NOTES_COUNT; i++) {
        notes[i] = NO_NOTE;
    }

    for (i = 0; i < n_players; i++) {
        players[i] = true;
    }

round_start:
    while (1) {
        fprintf(&uart, "Round %u\n", round);
        while (1) {
            current_player = find_next_player(players, current_player);
            if (current_player == NO_PLAYER) {
                round++;
                break;
            }

        round_turn:
            fprintf(&uart, "Player %d\n", current_player + 1);
            // wait for the player to input the notes; use a watchdog to abort
            // the player's turn

            while (input_notes_count < round && !note_mismatch &&
                   !player_timeout)
                ;

            if (note_mismatch) {
                buzzer_tone(TONE_ERROR);
                fprintf(&uart,
                        "Incorrect sequence! You have been eliminated!\n");
            } else if (player_timeout) {
                fprintf(&uart, "Time expired. You have been eliminated!\n");
            } else {
                notes[notes_size] = last_note;
                notes_size++;
            }
        }
    }

    free(notes);
    free(players);

    // game over
    while (1)
        ;
}
