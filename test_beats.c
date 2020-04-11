// Assignment 2 20T1 COMP1511: CS bEats
// test_beats.c
//
// This program was written by NICHOLAS LIU (z5310207)
// on 10~ APRIL 2020
//
// Version 1.0.0: Assignment released.
#include <stdio.h>
#include <stdlib.h>

#include "test_beats.h"
#include "beats.h"


// Test function for `add_note_to_beat`
int test_add_note_to_beat(void) {
    // Test 1: Rejecting negative inputs.
    Beat test_beat = create_beat();
    if (add_note_to_beat(test_beat, -1, -1) != INVALID_OCTAVE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, -1, 0) != INVALID_OCTAVE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 1, -1) != INVALID_KEY) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 2: Rejecting inputs that are too high
    if (add_note_to_beat(test_beat, 22, 5) != INVALID_OCTAVE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 4, 2019) != INVALID_KEY) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 4, 12) != INVALID_KEY) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 3: Seeing if new notes are higher
    add_note_to_beat(test_beat, 5, 2);
    if (add_note_to_beat(test_beat, 4, 3) != NOT_HIGHEST_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 5, 2) != NOT_HIGHEST_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 6, 3) != VALID_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    
    return MEETS_SPEC;
}

// Test function for `count_notes_in_octave`
int test_count_notes_in_octave(void){
    // Test 1: Counting invalid octaves.
    Beat test_beat = create_beat();
    add_note_to_beat(test_beat, 1, 1);
    if (count_notes_in_octave(test_beat, -1) != 0) {
        return DOES_NOT_MEET_SPEC;
    }
    if (count_notes_in_octave(test_beat, 11) != 0) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 2: Counting valid octaves.
    if (count_notes_in_octave(test_beat, 2) != 0) {
        return DOES_NOT_MEET_SPEC;
    }
    if (count_notes_in_octave(test_beat, 1) != 1) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 3: Counting valid octaves for higher order beats
    add_note_to_beat(test_beat, 2, 2);
    add_note_to_beat(test_beat, 2, 3);
    add_note_to_beat(test_beat, 2, 4);
    if (count_notes_in_octave(test_beat, 1) != 1) {
        return DOES_NOT_MEET_SPEC;
    }
    if (count_notes_in_octave(test_beat, 2) != 3) {
        return DOES_NOT_MEET_SPEC;
    }
    
    return MEETS_SPEC;
}

// Test function for `add_beat_to_track`
int test_add_beat_to_track(void){
    // Test 1: ???
    // TODO: Write Test 1

    // Test 2: ???
    // TODO: Write Test 2

    // Test 3: ???
    // TODO: Write Test 3

    return MEETS_SPEC;
}

// Test function for `remove_selected_beat`
int test_remove_selected_beat(void){
    // Test 1: ???
    // TODO: Write Test 1

    // Test 2: ???
    // TODO: Write Test 2

    // Test 3: ???
    // TODO: Write Test 3

    return MEETS_SPEC;
}

// Test function for `add_musical_note_to_beat`
int test_add_musical_note_to_beat(void){
    // Test 1: ???
    // TODO: Write Test 1

    // Test 2: ???
    // TODO: Write Test 2

    // Test 3: ???
    // TODO: Write Test 3

    return MEETS_SPEC;
}
