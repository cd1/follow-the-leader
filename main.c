#include <stdio.h>

#include "button-pin2.h"
#include "button-pin3.h"
#include "buzzer.h"
#include "notes.h"
#include "players.h"
#include "timer0.h"
#include "uart.h"

const unsigned int BUZZ_ERROR_FREQ = 10;       // Hz
const unsigned int BUZZ_C_FREQ = 100;          // Hz
const unsigned int BUZZ_F_FREQ = 500;          // Hz
const unsigned long BUZZ_DURATION = 500;       // ms
const unsigned long BUZZ_DURATION_ERROR = 50;  // ms

const unsigned long PLAYER_TIMEOUT = 5000;  // ms

int main() {
    button_pin2_setup();
    button_pin3_setup();
    buzzer_setup();
    timer0_setup();
    uart_setup();

    while (1) {
        unsigned int n_players;

        do {
            fprintf(&uart,
                    "Welcome to the follow the leader game! Please enter the "
                    "number of "
                    "players: [2-9]\n");
            fscanf(&uart, "%u", &n_players);
        } while (n_players < 2 || n_players > 9);

        player_list *players = players_new(n_players);
        notes_list *notes = notes_new();

        unsigned long last_button_pin2_press = button_pin2_press;
        unsigned long last_button_pin3_press = button_pin3_press;

        unsigned int round;
        for (round = 1; players_active_count(players) >= 2; round++) {
            fprintf(&uart, "Round %u\n", round);

            int current_player = PLAYER_NONE;
            while (players_active_count(players) >= 2 &&
                   ((current_player = players_next_active(
                         players, current_player)) != PLAYER_NONE)) {
                bool note_mismatch = false;
                unsigned int input_notes_count = 0;
                int last_note = NOTE_NONE;
                bool player_timeout = false;
                unsigned int notes_to_press = notes_size(notes) + 1;
                unsigned long last_timeout_checkpoint = timer0_millis();

                fprintf(&uart, "Player %d\n", current_player + 1);

                while (input_notes_count < notes_to_press && !note_mismatch &&
                       !player_timeout) {
                    if (button_pin2_press > last_button_pin2_press) {
                        last_button_pin2_press = button_pin2_press;
                        last_timeout_checkpoint = button_pin2_press;
                        fprintf(&uart, "C");  // TODO: remove debugging call

                        input_notes_count++;

                        if ((input_notes_count < notes_to_press) &&
                            (notes_get(notes, input_notes_count - 1) !=
                             NOTE_C)) {
                            note_mismatch = true;
                            buzzer_tone(BUZZ_ERROR_FREQ, BUZZ_DURATION_ERROR);
                        } else {
                            buzzer_tone(BUZZ_C_FREQ, BUZZ_DURATION);
                        }

                        last_note = NOTE_C;
                    } else if (button_pin3_press > last_button_pin3_press) {
                        last_button_pin3_press = button_pin3_press;
                        last_timeout_checkpoint = button_pin3_press;
                        fprintf(&uart, "F");  // TODO: remove debugging call

                        input_notes_count++;

                        if ((input_notes_count < notes_to_press) &&
                            (notes_get(notes, input_notes_count - 1) !=
                             NOTE_F)) {
                            note_mismatch = true;
                            buzzer_tone(BUZZ_ERROR_FREQ, BUZZ_DURATION_ERROR);
                        } else {
                            buzzer_tone(BUZZ_C_FREQ, BUZZ_DURATION);
                        }

                        last_note = NOTE_F;
                    }

                    if ((timer0_millis() - last_timeout_checkpoint) >=
                        PLAYER_TIMEOUT) {
                        player_timeout = true;
                    }
                }
                fprintf(&uart, "\n");  // TODO: remove debugging call

                if (note_mismatch) {
                    fprintf(&uart,
                            "Incorrect sequence! You have been eliminated!\n");
                    players_set_inactive(players, current_player);
                } else if (player_timeout) {
                    fprintf(&uart, "Time expired. You have been eliminated!\n");
                    players_set_inactive(players, current_player);
                } else {
                    notes_append(notes, last_note);
                }
            }
        }

        int winner = players_next_active(players, PLAYER_NONE);
        fprintf(&uart, "Player %d won!\n", winner + 1);

        notes_free(notes);
        players_free(players);
    }

    return 0;
}
