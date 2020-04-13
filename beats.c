// Assignment 2 20T1 COMP1511: CS bEats
// beats.c
//
// This program was written by NICHOLAS LIU (z5310207)
// on 10~ APRIL 2020
//
// Version 1.0.0: Assignment released.
// Version 1.0.1: Fix default return value of add_musical_note_to_beat.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Add any extra #includes your code needs here.

#include "beats.h"

// Add your own #defines here.

////////////////////////////////////////////////////////////////////////

// You don't have to use the provided struct track, you are free to
// make your own struct instead.
// If you use the provided struct track, you will have to add fields
// to store other information.

struct track {
    struct beat *curr; // the current beat the track is on
    struct beat *head;
    int selection;
    int beatCount;
};

// You don't have to use the provided struct beat, you are free to
// make your own struct instead.
// If you use the provided struct beat, you may add fields
// to it to store other information.

struct beat {
    // You may choose to add or change fields in this struct.
    struct note *notes;
    struct beat *next;
};

// You don't have to use the provided struct note, you are free to
// make your own struct instead.
// If you use the provided struct note, you add fields
// to it to store other information.

struct note {
    // You may choose to add or change fields in this struct.
    int octave;
    int key;
    struct note *next;
};

// Add any other structs you define here.

////////////////////////////////////////////////////////////////////////

// Add prototypes for any extra functions you create here.

// Return a malloced Beat with fields initialized.
Beat create_beat(void) {
    Beat new_beat = malloc(sizeof (struct beat));
    assert(new_beat != NULL);

    new_beat->next = NULL;
    new_beat->notes = NULL;

    // You do not need to change this function, unless you change
    // the implementation of struct beat.

    return new_beat;
}

// You need to implement the following functions.
// You can find descriptions of what each function should do in beats.h

////////////////////////////////////////////////////////////////////////
//                         Stage 1 Functions                          //
////////////////////////////////////////////////////////////////////////

// Add a note to the end of a beat.
int add_note_to_beat(Beat beat, int octave, int key) {
    // If octave isn't valid, i.e. octave isn't 0~9
    if (octave < 0 || octave > 9) {
        return INVALID_OCTAVE;
    }
    // If key isn't valid, i.e. key isn't 0~10 
    if (key < 0 || key > 11) {
        return INVALID_KEY;
    }
    // Create note * lastNote that's meant to be the note before the new note
    struct note *lastNote = beat->notes;
    
    // If the new note is the first note,...
    if (lastNote == NULL) {
        // create the new note * newNote!!
        struct note *newNote = malloc(sizeof(struct note));
        newNote->octave = octave;
        newNote->key = key;
        newNote->next = NULL;
        
        // The new note becomes the first note
        beat->notes = newNote;
        return VALID_NOTE;
    }
    
    // If the new note is not the first note..
    // Push lastNote to the note before the new note
    while (lastNote->next != NULL) {
        lastNote = lastNote->next;
    }
    
    // If new note is not higher than the note before
    if (octave < lastNote->octave) {
        return NOT_HIGHEST_NOTE;
    } else if (octave == lastNote->octave && key <= lastNote->key) {
        return NOT_HIGHEST_NOTE;
    }
    
    // The new note passes all the requirements, create the new note * newNote!!
    struct note *newNote = malloc(sizeof(struct note));
    newNote->octave = octave;
    newNote->key = key;
    newNote->next = NULL;
    
    // Make the last note's next pointer point to the new note
    // The new note is added to the beat
    lastNote->next = newNote;
    
    return VALID_NOTE;
}

// Print the contents of a beat.
void print_beat(Beat beat) {
    // create a struct note * "current"
    struct note *current = beat->notes;
    
    // if there's no beats to print
    if (current == NULL) {
        printf("\n");
        return;
    }
    
    // print the first note
    if (current->key < 10) {
        printf("%d 0%d", current->octave, current->key);
    } else if (current->key > 9) {
        printf("%d %d", current->octave, current->key);
    }
    
    // Slide "current" to the next note
    current = current->next;
    
    // Keep printing notes until the end of the beat
    while (current != NULL) {
        if (current->key < 10) {
            printf(" | %d 0%d", current->octave, current->key);
        } else if (current->key > 9) {
            printf(" | %d %d", current->octave, current->key);
        }
        current = current->next;
    } 
    
    // End of beat reached, print new line
    printf("\n");
    return;
}

// Count the number of notes in a beat that are in a given octave.
int count_notes_in_octave(Beat beat, int octave) {
    // Create a counter "count"
    int count = 0;
    
    // Create struct note * "current"
    struct note *current = beat->notes;
    
    // Keep sliding current through every note in the beat
    while (current != NULL) {
        // If note is in the same octave as given octave in input,...
        if (current->octave == octave) {
            // the counter increases
            count++;
        }
        current = current->next;
    }
    
    // Return the number of notes in inputed octave
    return count;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 2 Functions                          //
////////////////////////////////////////////////////////////////////////

// Return a malloced track with fields initialized.
Track create_track(void) {
    // Create a struct track * called newTrack
    Track newTrack = malloc(sizeof(struct track));
    // Assign values to struct beat "curr" and "head"
    newTrack->head = NULL;
    newTrack->curr = NULL;
    newTrack->beatCount = 0;
    newTrack->selection = 0;
    
    return newTrack;
}

// Add a beat after the current beat in a track.
void add_beat_to_track(Track track, Beat beat) {
    // If there is no current beat
    if (track->curr == NULL) {
        beat->next = track->head;
        track->head = beat;
        track->beatCount++;
    } else { // If there is a current beat selected
        // Then beat goes right after the current beat
        beat->next = track->curr->next;
        track->curr->next = beat;
        track->beatCount++;
    }
    
    return;
}

// Set a track's current beat to the next beat.
int select_next_beat(Track track) {
    // If there's no beats on track
    if (track->head == NULL) {
        return TRACK_STOPPED;
    }
    
    // If no beat has been selected yet, select the first beat
    if(track->curr == NULL) {
        track->curr = track->head;
        track->selection = 1;
        return TRACK_PLAYING;
    }
    
    // If this beat is the last beat in the track
    if(track->curr->next == NULL) {
        // Shift to the next beat in the track
        track->curr = track->curr->next;
        track->selection++;
        return TRACK_STOPPED;
    } else {
        // Shift to the next beat in the track
        track->curr = track->curr->next;
        track->selection++;
        return TRACK_PLAYING;
    }
    
    
    return TRACK_STOPPED;
}

// Print the contents of a track.
void print_track(Track track) {
    // Create a counter i that will count the number of beats
    int i = 0;
    
    // Create a struct beat * "currentBeat" that points to the first beat
    Beat currentBeat = track->head;
    i++;
    
    // Run currentBeat through all the beats of the track
    // Up to the beat before the beat being constructed
    while (currentBeat != NULL) {
        if (track->selection != i) {
            printf(" [%d] ", i);
        } else {
            printf(">[%d] ", i);
        }
        
        // Print the notes of the beat using the stage 01 function
        print_beat(currentBeat);
        
        currentBeat = currentBeat->next;
        i++;
    }

    
    return;
}

// Count beats after the current beat in a track.
int count_beats_left_in_track(Track track) {
    // Create a counter "count"
    int count = 0;
    
    // If there is no current track selected
    if (track->curr == NULL) {
        // Create a struct beat * "currentBeat" starting at the head of track
        Beat currentBeat = track->head;
        
        // Slide through the entire track from beat to beat
        // Until the beat before the beat being constructed
        while (currentBeat != NULL) {
            count++;
            currentBeat = currentBeat->next;
        }
        
        return count;

    } else { // If there is a current track selected
        // Create a struct beat * "currentBeat" starting at the
        // beat after the currrent beat
        Beat currentBeat = track->curr->next;
        
        // Slide through the entire track from beat to beat
        // Until the beat before the beat being constructed
        while (currentBeat != NULL) {
            count++;
            currentBeat = currentBeat->next;
        }
    }
    
    return count;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 3 Functions                          //
////////////////////////////////////////////////////////////////////////

// Free the memory of a beat, and any memory it points to.
void free_beat(Beat beat) {
    // Note: there is no printf in this function, as the
    // Stage 1 & 2 autotests call free_beat but don't check whether
    // the memory has been freed (so this function should do nothing in
    // Stage 1 & 2, rather than exit).
    return;
}

// Free the memory of a track, and any memory it points to.
void free_track(Track track) {
    // Note: there is no printf in this function, as the
    // Stage 1 & 2 autotests call free_track but don't check whether
    // the memory has been freed (so this function should do nothing in
    // Stage 1 & 2, rather than print an error).
    return;
}

// Remove the currently selected beat from a track.
int remove_selected_beat(Track track) {
    printf("remove_selected_beat not implemented yet.");
    return TRACK_STOPPED;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 4 Functions                          //
////////////////////////////////////////////////////////////////////////

// Add note to beat, given its 'musical notation'.
int add_musical_note_to_beat(Beat beat, char *musical_notation) {
    printf("add_musical_note_to_beat not implemented yet.");
    return VALID_NOTE;
}


////////////////////////////////////////////////////////////////////////
//                         Stage 5 Functions                          //
////////////////////////////////////////////////////////////////////////

// Cut a range of beats to the end of a track.
void cut_range_to_end(Track track, int range_length) {
    printf("cut_range_to_end not implemented yet.");
    return;
}

// Reverse a list of beats within a range of a track.
int reverse_range(Track track, int range_length) {
    printf("reverse_range not implemented yet.");
    return 0;
}
