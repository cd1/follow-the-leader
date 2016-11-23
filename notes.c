#include <stdlib.h>

#include "notes.h"

const int NOTE_NONE = -1;
const int NOTE_C = 0;
const int NOTE_F = 1;

const unsigned int MAX_NOTES_SIZE = 64;

notes_list *notes_new() {
    notes_list *list = malloc(sizeof(notes_list));
    list->notes = malloc(sizeof(int) * MAX_NOTES_SIZE);
    list->size = 0;

    return list;
}

unsigned int notes_size(notes_list *list) { return list->size; }

int notes_get(notes_list *list, int index) { return list->notes[index]; }

void notes_free(notes_list *list) {
    free(list->notes);
    free(list);
}

void notes_append(notes_list *list, int note) {
    if (list->size >= MAX_NOTES_SIZE) {
        return;
    }

    list->notes[list->size] = note;
    list->size++;
}
