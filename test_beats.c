// Assignment 2 20T1 COMP1511: CS bEats
// test_beats.c
//
// This program was written by NICHOLAS LIU (z5310207)
// on 10th~17th APRIL 2020
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
    // Create a tracks for each test
    Track test_track1 = create_track();
    Track test_track2 = create_track();
    Track test_track3 = create_track();
    
    // Create some stock beats first and add notes to it
    Beat beat1 = create_beat();
    add_note_to_beat(beat1, 1, 1);
    
    Beat beat2 = create_beat();
    add_note_to_beat(beat2, 2, 4);
    
    Beat beat3 = create_beat();
    add_note_to_beat(beat3, 4, 8);

    // Test 1: Adding a beat to track when there's 1 beat
    add_beat_to_track(test_track1, beat1);
    // Check if the Stage 02 commands work as they should
    if (count_beats_left_in_track(test_track1) != 1) {
        return DOES_NOT_MEET_SPEC;
    }
    if (select_next_beat(test_track1) != TRACK_PLAYING) {
        return DOES_NOT_MEET_SPEC;
    }
    
    // Test 2: Adding 2 beat to track
    add_beat_to_track(test_track2, beat1);
    add_beat_to_track(test_track2, beat2);
    // Check if the Stage 02 commands work as they should
    if (count_beats_left_in_track(test_track2) != 2) {
        return DOES_NOT_MEET_SPEC;
    }
    if (select_next_beat(test_track2) != TRACK_PLAYING) {
        return DOES_NOT_MEET_SPEC;
    }
    
    // Test 3: Adding 3 beats to a track
    add_beat_to_track(test_track3, beat1);
    add_beat_to_track(test_track3, beat2);
    add_beat_to_track(test_track3, beat3);
    // Check if the Stage 02 commands work as they should
    if (count_beats_left_in_track(test_track3) != 3) {
        return DOES_NOT_MEET_SPEC;
    }
    if (select_next_beat(test_track3) != TRACK_PLAYING) {
        return DOES_NOT_MEET_SPEC;
    }

    return MEETS_SPEC;
}

// Test function for `remove_selected_beat`
int test_remove_selected_beat(void){
    // Create a track for the test
    Track test_track1 = create_track();
    
    // Create some stock beats first and add notes to it
    Beat beat1 = create_beat();
    add_note_to_beat(beat1, 1, 1);
    Beat beat2 = create_beat();
    add_note_to_beat(beat2, 2, 4);
    Beat beat3 = create_beat();
    add_note_to_beat(beat3, 4, 8);
    Beat beat4 = create_beat();
    add_note_to_beat(beat3, 5, 9);
    Beat beat5 = create_beat();
    add_note_to_beat(beat3, 6, 10);
    
    // Setting up test_track1
    add_beat_to_track(test_track1, beat1);
    add_beat_to_track(test_track1, beat2);
    add_beat_to_track(test_track1, beat3);
    add_beat_to_track(test_track1, beat4);
    add_beat_to_track(test_track1, beat5);
    select_next_beat(test_track1);
    
    // Test 1: Removing first beat from a track of 5 beats
    remove_selected_beat(test_track1);
    if (count_beats_left_in_track(test_track1) != 3) {
        return DOES_NOT_MEET_SPEC;
    }
    // Test 2: Removing second beat from a track of 4 beats left
    select_next_beat(test_track1);
    remove_selected_beat(test_track1);
    if (count_beats_left_in_track(test_track1) != 1) {
        return DOES_NOT_MEET_SPEC;
    }
    
    // Test 3: Seeing how many beats are left is there's no current beat
    // after removing 2 beats from test_track1 which originally had 5
    select_next_beat(test_track1);
    select_next_beat(test_track1);
    if (count_beats_left_in_track(test_track1) != 3) {
        return DOES_NOT_MEET_SPEC;
    }
    
    return MEETS_SPEC;
}

// Test function for `add_musical_note_to_beat`
int test_add_musical_note_to_beat(void){
    // Create a beat for the test
    Beat test_beat = create_beat();
    
    // Create some musical notes
    char note1[5] = {-1, 'E', '#', '#', '\0'};
    char note2[5] = {'2', 'Z', '#', '#', '\0'};
    char note3[5] = {'#', '4', 'A', '#', '\0'};
    char note4[5] = {'4', 'A', '#', '#', '\0'};
    char note5[5] = {'4', 'E', '#', '#', '\0'};
    char note6[7] = {'3', 'F', '#', '#', '#', '#', '\0'};
    char note7[8] = {'6', 'G', '#', '#', '#', '#', '#', '\0'};
    char note8[10] = {'1', 'B', '#', '#', '#', '#', '#', '#', '#', '\0'};
    
    // Test 1: Rejecting invalid octaves
    if (add_musical_note_to_beat(test_beat, note1) != INVALID_MUSICAL_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 2: Rejecting invalid keys
    if (add_musical_note_to_beat(test_beat, note2) != INVALID_MUSICAL_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 3: Rejecting notes in the wrong order
    if (add_musical_note_to_beat(test_beat, note3) != INVALID_MUSICAL_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    
    // Test 4: Accepting a valid note
    if (add_musical_note_to_beat(test_beat, note4) != VALID_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    
    // Test 5: Accepting 5 notes and see if the count functions
    // pick it up
    add_musical_note_to_beat(test_beat, note4);
    add_musical_note_to_beat(test_beat, note5);
    add_musical_note_to_beat(test_beat, note6);
    add_musical_note_to_beat(test_beat, note7);
    add_musical_note_to_beat(test_beat, note8);
    if (count_notes_in_octave(test_beat, 4) != 3) {
        return DOES_NOT_MEET_SPEC;
    }
    if (count_notes_in_octave(test_beat, 1) != 1) {
        return DOES_NOT_MEET_SPEC;
    }
    
    return MEETS_SPEC;
}
