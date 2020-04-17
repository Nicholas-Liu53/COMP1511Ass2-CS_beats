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
    // Create a tracks for each test
    Track test_track1 = create_track();
    Track test_track2 = create_track();
    Track test_track3 = create_track();
    
    // Create some stock beats first and add notes to it
    Beat beat1 = create_beat();
    add_note_to_beat(beat1, 1, 1);
    add_note_to_beat(beat1, 1, 2);
    add_note_to_beat(beat1, 1, 3);
    
    Beat beat2 = create_beat();
    add_note_to_beat(beat2, 2, 4);
    add_note_to_beat(beat2, 2, 5);
    add_note_to_beat(beat2, 2, 6);
    
    Beat beat3 = create_beat();
    add_note_to_beat(beat3, 4, 8);
    add_note_to_beat(beat3, 4, 9);

    // Test 1: Adding a beat to track when there's no current beat
    add_beat_to_track(test_track1, beat1);
    // Check if the Stage 02 commands work as they should
    if (select_next_beat(test_track1) != TRACK_PLAYING) {
        return DOES_NOT_MEET_SPEC;
    }
    if (count_beats_left_in_track(test_track1) != 1) {
        return DOES_NOT_MEET_SPEC;
    }
    // Select beat1 as the current beat,
    select_next_beat(test_track1);
    if (select_next_beat(test_track1) != TRACK_STOPPED) {
        return DOES_NOT_MEET_SPEC;
    }
    if (count_beats_left_in_track(test_track1) != 0) {
        return DOES_NOT_MEET_SPEC;
    }
    
    // Test 2: Adding a beat to track when there is a current beat
    add_beat_to_track(test_track2, beat1);
    select_next_beat(test_track2);
    add_beat_to_track(test_track2, beat2);
    // Check if the Stage 02 commands work as they should
    if (select_next_beat(test_track2) != TRACK_PLAYING) {
        return DOES_NOT_MEET_SPEC;
    }
    if (count_beats_left_in_track(test_track2) != 1) {
        return DOES_NOT_MEET_SPEC;
    }
    select_next_beat(test_track2);
    if (select_next_beat(test_track2) != TRACK_STOPPED) {
        return DOES_NOT_MEET_SPEC;
    }
    if (count_beats_left_in_track(test_track2) != 0) {
        return DOES_NOT_MEET_SPEC;
    }
    
    // Test 3: Adding 3 beats to a track without selecting a current beat
    add_beat_to_track(test_track3, beat1);
    add_beat_to_track(test_track3, beat2);
    add_beat_to_track(test_track3, beat3);
    // Check if the Stage 02 commands work as they should
    if (select_next_beat(test_track3) != TRACK_PLAYING) {
        return DOES_NOT_MEET_SPEC;
    }
    if (count_beats_left_in_track(test_track3) != 3) {
        return DOES_NOT_MEET_SPEC;
    }
    select_next_beat(test_track3);
    if (select_next_beat(test_track3) != TRACK_PLAYING) {
        return DOES_NOT_MEET_SPEC;
    }
    if (count_beats_left_in_track(test_track3) != 2) {
        return DOES_NOT_MEET_SPEC;
    }
    select_next_beat(test_track3);
    if (select_next_beat(test_track3) != TRACK_PLAYING) {
        return DOES_NOT_MEET_SPEC;
    }
    if (count_beats_left_in_track(test_track3) != 1) {
        return DOES_NOT_MEET_SPEC;
    }
    select_next_beat(test_track3);
    if (select_next_beat(test_track3) != TRACK_STOPPED) {
        return DOES_NOT_MEET_SPEC;
    }
    if (count_beats_left_in_track(test_track3) != 0) {
        return DOES_NOT_MEET_SPEC;
    }

    return MEETS_SPEC;
}

// Test function for `remove_selected_beat`
int test_remove_selected_beat(void){
    // Create a tracks for each test
    Track test_track1 = create_track();
    Track test_track2 = create_track();
    Track test_track3 = create_track();
    
    // Create some stock beats first and add notes to it
    Beat beat1 = create_beat();
    add_note_to_beat(beat1, 1, 1);
    add_note_to_beat(beat1, 1, 2);
    add_note_to_beat(beat1, 1, 3);
    
    Beat beat2 = create_beat();
    add_note_to_beat(beat2, 2, 4);
    add_note_to_beat(beat2, 2, 5);
    add_note_to_beat(beat2, 2, 6);
    
    Beat beat3 = create_beat();
    add_note_to_beat(beat3, 4, 8);
    add_note_to_beat(beat3, 4, 9);
    
    // Setting up test_track1
    add_beat_to_track(test_track1, beat1);
    add_beat_to_track(test_track1, beat2);
    add_beat_to_track(test_track1, beat3);
    select_next_beat(test_track1);
    
    // Setting up test_track2
    add_beat_to_track(test_track2, beat1);
    add_beat_to_track(test_track2, beat2);
    add_beat_to_track(test_track2, beat3);
    select_next_beat(test_track2);
    select_next_beat(test_track2);
    select_next_beat(test_track2);
    
    // Setting up test_track3
    add_beat_to_track(test_track3, beat1);
    add_beat_to_track(test_track3, beat2);
    add_beat_to_track(test_track3, beat3);
    select_next_beat(test_track3);
    
    // Test 1: Removing first beat from a track
    remove_selected_beat(test_track1);
    if (count_beats_left_in_track(test_track1) != 2) {
        return DOES_NOT_MEET_SPEC;
    }
    

    // Test 2: For test_track2, removing the last beat from the rack
    if (remove_selected_beat(test_track2) != TRACK_STOPPED) {
        return DOES_NOT_MEET_SPEC;
    }
    remove_selected_beat(test_track2);
    if (count_beats_left_in_track(test_track2) != 2) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 3: For test_track3, removing a track with only 3 beats
    if (remove_selected_beat(test_track3) != TRACK_PLAYING) {
        return DOES_NOT_MEET_SPEC;
    }
    remove_selected_beat(test_track3);
    if (select_next_beat(test_track3) != TRACK_PLAYING) {
        return DOES_NOT_MEET_SPEC;
    }
    if (count_beats_left_in_track(test_track3) != 2) {
        return DOES_NOT_MEET_SPEC;
    }

    return MEETS_SPEC;
}

// Test function for `add_musical_note_to_beat`
int test_add_musical_note_to_beat(void){
    /* // Create some stock beats first
    Beat beat1 = create_beat();    
    Beat beat2 = create_beat();
    Beat beat3 = create_beat(); */
    
    // Create some musical notes
    
    // Test 1: Rejecting invalid notes
    

    // Test 2: ???
    // TODO: Write Test 2

    // Test 3: ???
    // TODO: Write Test 3

    return MEETS_SPEC;
}
