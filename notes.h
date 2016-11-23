#ifndef NOTES_H
#define NOTES_H

#include <stdio.h>

extern const int NOTE_NONE;
extern const int NOTE_C;
extern const int NOTE_F;

extern const unsigned int MAX_NOTES_SIZE;

typedef struct {
    int *notes;
    unsigned int size;
} notes_list;

notes_list *notes_new();
void notes_append(notes_list *, int /* note */);
unsigned int notes_size(notes_list *);
int notes_get(notes_list *, int /* index */);
void notes_free(notes_list *);

#endif
