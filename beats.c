// Assignment 2 20T1 COMP1511: CS bEats
// beats.c
//
// This program was written by NICHOLAS LIU (z5310207)
// on 10th~17th APRIL 2020
//
// Version 1.0.0: Assignment released.
// Version 1.0.1: Fix default return value of add_musical_note_to_beat.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Add any extra #includes your code needs here.

#include "beats.h"
#include <string.h>

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
    // if there's no beats to print
    if (beat->notes == NULL) {
        printf("\n");
        return;
    }
    
    // create a struct note * "current"
    struct note *current = beat->notes;
    
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
    if (track->curr == NULL) {
        track->curr = track->head;
        track->selection = 1;
        return TRACK_PLAYING;
    }
    
    // If this beat is the last beat in the track
    if (track->curr->next == NULL) {
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
    // Before we free the beat, we gotta free all the notes in the beat first
    // Create a temporary note
    struct note *tempBeat = beat->notes;
    
    // Free all of the notes starting from first note
    while (beat->notes != NULL) {
        beat->notes = tempBeat->next;
        free(tempBeat);
        tempBeat = beat->notes;
    }
    // Free the notes completely
    free (beat->notes);
    free (beat);
    return;
}

// Free the memory of a track, and any memory it points to.
void free_track(Track track) {
    // Before we free the track we gotta free all the beats in the track first
    // Create a temporary beat
    Beat tempTrack = track->head;
    
    //Free all the beats starting from the first beat
    while (track->head != NULL) {
        track->head = tempTrack->next;
        free_beat(tempTrack);
        tempTrack = track->head;
    }
    // Free the track completely
    free (track->head);
    free (track);
    return;
}

// Remove the currently selected beat from a track.
int remove_selected_beat(Track track) {
    // Create a struct beat * "beatBefore", which is meant
    // to be the beat before the one we're removing
    Beat beatBefore = track->head;
    
    // If the head of the track is what we're removing
    if (beatBefore == track->curr && track->curr != NULL) {
        track->head = beatBefore->next;
        free_beat(track->curr);
        track->curr = track->head;
    } else if (track->curr != NULL) {
        while (beatBefore->next != track->curr) { // Otherwise...
            beatBefore = beatBefore->next;
        }
        beatBefore->next = track->curr->next;
        free_beat(track->curr);
        track->curr = beatBefore->next;
        track->beatCount--;
    }
    
    // If the track has no more beats to play
    if (track->curr == NULL) {
        return TRACK_STOPPED;
    }
    
    return TRACK_PLAYING;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 4 Functions                          //
////////////////////////////////////////////////////////////////////////

// Add note to beat, given its 'musical notation'.
int add_musical_note_to_beat(Beat beat, char *musical_notation) {
    // Get the octave
    int octave = musical_notation[0] - '0';
    
    // Ensure that the octave is valid
    if (octave < 0 || octave > 9) {
        return INVALID_MUSICAL_NOTE;
    }
    
    // Get the key
    int keyLetter = musical_notation[1];
    int keyNumber = -1;
    if (keyLetter == 'A') {
        keyNumber = 0;
    } else if (keyLetter == 'B') {
        keyNumber = 2;
    } else if (keyLetter == 'C') {
        keyNumber = 3;
    } else if (keyLetter == 'D') {
        keyNumber = 5;
    } else if (keyLetter == 'E') {
        keyNumber = 7;
    } else if (keyLetter == 'F') {
        keyNumber = 8;
    } else if (keyLetter == 'G') {
        keyNumber = 10;
    } else { // if the key is invalid, e.g. there is no 'Z' key
        return INVALID_MUSICAL_NOTE;
    }
    
    // Check if anything that's not a sharp is entered
    int i = 2;
    while (musical_notation[i] != '\0') {
        if (musical_notation [i] != '#') {
            return INVALID_MUSICAL_NOTE;
        }
        i++;
    }
    
    // Create a counter for the number of sharps and count the sharps
    int sharpCount = 0;
    i = 2;
    while (musical_notation[i] == '#') {
        sharpCount++;
        i++;
    }
    
    // Add the number of sharps to the note    
    keyNumber += sharpCount;
    
    // Make adjustments if the keyNumber exceeds 10
    while (!(keyNumber > -1 && keyNumber < 12)) {
        octave++;
        keyNumber -= 12;
    }
    
    // If the note already exists within the beat, we cannot input it
    // Check if the new note has not been already inputted
    
    struct note *noteChecker = beat->notes;
    while (noteChecker != NULL) {
        if (octave == noteChecker->octave && keyNumber == noteChecker->key) {
            return INVALID_MUSICAL_NOTE;
        }
        noteChecker = noteChecker->next;
    }
    
    // We have now acquired the octave and key
    // Time to plug it into a fresh new note
    struct note *newNote = malloc(sizeof(struct note));
    newNote->octave = octave;
    newNote->key = keyNumber;
    newNote->next = NULL;
    
    // Put the new note into the beat that has been inputted
    // Now, after inputting the new note, the beat must be in ascending order
    // Create oneNoteHigher, which is meant to be the note
    // higher than the new note
    struct note *oneNoteHigher = beat->notes;
    // if the beat is empty
    if (oneNoteHigher == NULL) {
        beat->notes = newNote;
        return VALID_NOTE;
    } else if (oneNoteHigher->next == NULL) { // if the beat has one note
        if (oneNoteHigher->octave < newNote->octave) {
            oneNoteHigher->next = newNote;
        } else if (oneNoteHigher->octave > newNote->octave) {
            newNote->next = oneNoteHigher;
            beat->notes = newNote;
        } else if (oneNoteHigher->key < newNote->key) {
            oneNoteHigher->next = newNote;
        } else {
            newNote->next = oneNoteHigher;
            beat->notes = newNote;
        }
        return VALID_NOTE;
    }
    // Create oneNoteLower, which is meant to be the note
    // lower than the newNote
    struct note *oneNoteLower = beat->notes;
    // For if the newNote is meant to be at the end
    struct note *runner = beat->notes;
    int higherCounter = 0;
    while (runner != NULL) {
        if (runner->octave > newNote->octave) {
            higherCounter++;
        }
        if (runner->octave == newNote->octave) {
            if (runner->key > newNote->key) {
                higherCounter++;
            }
        }
        runner = runner->next;
    }
    if (higherCounter == 0) {
        while (oneNoteLower->next != NULL) {
            oneNoteLower = oneNoteLower->next;
        }
        oneNoteLower->next = newNote;
        return VALID_NOTE;
    }
    // For if the newNote is meant to be at the beginning
    if (oneNoteHigher->octave > newNote->octave) {
        newNote->next = oneNoteHigher;
        beat->notes = newNote;
        return VALID_NOTE;
    }
    if (oneNoteHigher->octave == newNote->octave) {
        if (oneNoteHigher->key > newNote->key) {
            newNote->next = oneNoteHigher;
            beat->notes = newNote;
            return VALID_NOTE;
        }
    }
    // For the newNote is somewhere in the middle
    while (oneNoteHigher->octave < newNote->octave) {
        oneNoteHigher = oneNoteHigher->next;
    }
    while (
        oneNoteHigher->octave == newNote->octave && 
        oneNoteHigher->key < newNote->key
    ) {
        oneNoteHigher = oneNoteHigher->next;
    }
    while (oneNoteLower->next != oneNoteHigher) {
        oneNoteLower = oneNoteLower->next;
    }
    newNote->next = oneNoteHigher;
    oneNoteLower->next = newNote;
    
    return VALID_NOTE;
}


////////////////////////////////////////////////////////////////////////
//                         Stage 5 Functions                          //
////////////////////////////////////////////////////////////////////////

// Cut a range of beats to the end of a track.
void cut_range_to_end(Track track, int range_length) {
    
    // "If 'range_length' is less than one, this function should do nothing"
    if (range_length < 1) {
        return;
    }
    
    // If there is no track, do nothing
    if (track == NULL) {
        return;
    }
    
    // If the track has no beats, do nothing
    if (track->head == NULL) {
        return;
    }
    // If the track only has one beat, do nothing
    if (track->head->next == NULL) {
        return;
    }
    
    // If there's no current beat, do nothing
    if (track->curr == NULL) {
        return;
    }
    
    //If the range length is greater than or equal to the track size,
    // do nothing
    if (track->beatCount <= range_length) {
        return;
    }
    
    // Set up the structs we need to perform this function
    Beat beforeCurr = track->head;
    Beat rangeEnd = track->curr;
    Beat trackEnd = track->head;
    Beat afterRange = track->curr;
    int rangeCount = 0;
    
    // Send trackEnd to the last beat of the track
    while (trackEnd->next != NULL) {
        trackEnd = trackEnd->next;
    }
    
    // Send "rangeEnd" to the last beat of the range
    while (rangeCount < range_length - 1) {
        rangeEnd = rangeEnd->next;
        rangeCount++;
    }
    
    // If the range length is greater than how many beats left
    if (rangeEnd == NULL) {
        return;
    }
    
    // The value of track->selection must be adjusted 
    // as track->curr will be moved
    // So create an int "shift"
    int shift = 0;
    // Create beat "shiftCounter" that will slide through the remaining beats
    // after the range
    Beat shiftCounter = rangeEnd;
    while (shiftCounter != trackEnd) {
        shiftCounter = shiftCounter->next;
        shift++;
    }
    
    // Send afterRange to the beat after the range
    afterRange = rangeEnd->next;
    
    
    // If the first track is the current track
    if (rangeEnd == trackEnd) {
        return;
    } else if (beforeCurr == track->curr) {
        track->head = afterRange;
        trackEnd->next = track->curr;
        rangeEnd->next = NULL;
        track->selection += shift;
    } else { // Otherwise
        // Send beforeCurr to the beat before the current beat
        while (beforeCurr->next != track->curr) {
            beforeCurr = beforeCurr->next;
        }
        beforeCurr->next = afterRange;    
        trackEnd->next = track->curr;
        rangeEnd->next = NULL;
        track->selection += shift;  
    }
    
    return;
}

// Reverse a list of beats within a range of a track.
int reverse_range(Track track, int range_length) {
    
    // If 'range_length' is less than or equal to one,
    // this function should do nothing
    if (range_length <= 1) {
        return 0;
    }
    
    // If there is no track, do nothing
    if (track == NULL) {
        return 0;
    }
    
    // If the track has no beats, do nothing
    if (track->head == NULL) {
        return 0;
    }
    // If the track only has one beat, do nothing
    if (track->head->next == NULL) {
        return 0;
    }
    
    // If there's no current beat, do nothing
    if (track->curr == NULL) {
        return 0;
    }
    
    // Set up the structs we need to perform this function
    Beat beforeCurr = track->head;
    Beat rangeEnd = track->curr;
    Beat afterRange = track->curr;
    int rangeCount = 0;
    
    // Create a counter for how many beats reversed
    int reverseCount = 0;
    
    // Send "rangeEnd" to the last beat of the range
    while (rangeCount < range_length - 1 && rangeEnd != NULL) {
        rangeEnd = rangeEnd->next;
        rangeCount++;
    }
    
    // If the range length is greater than how many beats left
    if (rangeEnd == NULL) {
        rangeEnd = track->curr;
        while (rangeEnd->next != NULL) {
            reverseCount++;
            rangeEnd = rangeEnd->next;
        }
    } else {
        reverseCount = rangeCount;
    }
    
    // If the reverseCount ends up being 0,
    // this function should do nothing
    if (reverseCount == 0) {
        return 0;
    }
    
    // Send afterRange to the beat after the range
    afterRange = rangeEnd->next;
    
    // If current beat is the head beat
    if (beforeCurr == track->curr) {
        track->head = rangeEnd;
    } else { // if current beat isn't the head beat
        while (beforeCurr->next != track->curr) {
            beforeCurr = beforeCurr->next;
        }
        beforeCurr->next = rangeEnd;
    }
    
    // Start the reversing process
    // These are called "swap" because we'll be reversing the direction
    // of the pointers of the beat within the reverse range
    Beat swap1 = track->curr;
    Beat swap2 = track->curr;
    
    // Because of the nature of this swapping process,
    // whether the number of beats being reverse is odd or even
    // must be considered to exit the while loops that prolong
    // the process. 
    if (reverseCount % 2 != 0) { // If reverseCount is odd
        while (swap1 != rangeEnd) {
            swap1 = swap1->next;
        }
        while (swap2->next != swap1) {
            swap2 = swap2->next;
        }
        swap1->next = swap2;
        swap1 = track->curr;
        while (swap1 != track->curr || swap2 != track->curr) {
            while (swap1->next != swap2) {
                swap1 = swap1->next;
            }
            swap2->next = swap1;
            swap2 = track->curr;
            while (swap2->next !=swap1) {
                swap2 = swap2->next;
            }
            swap1->next = swap2;
            swap1 = track->curr; 
        }
    } else { // If reverseCount is even
        while (swap1 != rangeEnd) {
            swap1 = swap1->next;
        }
        while (swap1 != track->curr || swap2 != track->curr) {
            while (swap2->next != swap1) {
                swap2 = swap2->next;
            }
            swap1->next = swap2;
            swap1 = track->curr;
            while (swap1->next != swap2) {
                swap1 = swap1->next;
            }
            swap2->next = swap1;
            swap2 = track->curr;
        }
    }
    
    track->curr->next = afterRange;
    track->selection += reverseCount;  
    
    return reverseCount;
}
