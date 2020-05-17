from MIDIControl import choose_song as cs
from textToSpeech import speak as s
import time
import os

def selecting_song(avail_songs,cor_seq): # main
    s("To select a song, a melody will be played.")
    s("You can navigate between all available songs with the first and third tile.")
    s("If you are okay with the song, press the second tile.")
    s("Once selected, you will be able to play.")
    s("Some L E Ds will show you where to press.")

    time.sleep(0.5)

    cs.play_song(0, avail_songs)
    return cs.select_or_next_song(avail_songs,cor_seq)

def initialise_song_list(doc_path):
    songs = []
    cor_sequences = []
    file = open(doc_path,"r")
    f1 = file.readlines()
    from_song_to_seq = False
    for i in f1:
        if from_song_to_seq:
            to_add = i.translate({ord('\n'): None})
            to_add_list = list_string_to_int_list(to_add)
            cor_sequences.append(to_add_list)
        else:
            if i == "---\n":
                from_song_to_seq = True
            else:
                to_add = i.translate({ord('\n'): None})
                songs.append(to_add)
    
    return songs, cor_sequences

def list_string_to_int_list(str):
    to_list = []
    nr = ''
    for e in str[1:-1]:
        if e!=',':
            nr += e
        else:
            to_list.append(int(nr))
            nr = ''
    return to_list
