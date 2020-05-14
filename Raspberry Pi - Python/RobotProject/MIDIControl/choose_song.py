# import textToSpeech

import mido
import pygame as pg
#import keyboard
import time

avail_songs = ["MIDIControl/songs/dr_dre.wav","MIDIControl/songs/ne_reviens_pas.wav","MIDIControl/songs/tequila.wav"]
cor_seq = [[50,50,50,50,50],[51,51,51,51,51,51],[52,52,52,52,52,52,52]]


mixer = pg.mixer
mixer.init(buffer=16) # setting buffer to 16 allows to run the sound quicker$
mixer.set_num_channels(100)

def isThisTilePushed(tile):
    port = mido.open_input('Q49 MIDI 1')

    try:
        for msg in port.iter_pending():
                if(msg.type == 'note_on'):
                        if(msg.note%12 == tile):
                            return True
                        else:
                            False
    except AttributeError as error:
        print("Error excepted")
        print(error)
        return False


def select_or_next_song():
    cursor = 0
    port = mido.open_input('Q49 MIDI 1')
    while True:

        try:
            for msg in port.iter_pending():
                    if(msg.type == 'note_on'):
                            print(msg.note)
                            print(msg.note%12)
                            if(msg.note%12 == 0):
                                print("previous song")
                                cursor = cursor - 1
                                if(cursor == -1):
                                    cursor = len(avail_songs) - 1
                                play_song(cursor)
                            if(msg.note%12 == 2):
                                print("next song")
                                time.sleep(0.5)
                                cursor = cursor + 1
                                try:
                                    exist = avail_songs[cursor]
                                except:
                                    cursor = 0
                                play_song(cursor)
                            if(msg.note%12 == 1):
                                mixer.stop()
                                return cor_seq[cursor]
        except AttributeError as error:
            print("Error excepted")
            print(error)
            return False
        
    
'''
def select_or_next_song():
    cursor = 0
    while True:
        if(keyboard.is_pressed('q')): # isThisTilePushed(1)
            cursor = cursor - 1
            if(cursor == -1):
                cursor = len(avail_songs) - 1
            play_song(cursor)
        if(keyboard.is_pressed('d')): # isThisTilePushed(3)
            print("next song")
            time.sleep(0.5)
            cursor = cursor + 1
            try:
                exist = avail_songs[cursor]
            except:
                cursor = 0
            play_song(cursor)
        if(keyboard.is_pressed('s')): # isThisTilePushed(2)
            return cor_seq[cursor]

'''
def play_song(i):
    if(mixer.get_busy):
        mixer.stop()
        time.sleep(0.5)
    sound = mixer.Sound(avail_songs[i])
    sound.play()


