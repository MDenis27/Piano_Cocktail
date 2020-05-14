from MIDIControl import choose_song as cs
from textToSpeech import speak as s
import time

def selecting_song(): # main
    s("To select a song, a melody will be played.")
    s("You can navigate between all available songs with the first and third tile.")
    s("If you are okay with the song, press the second tile.")
    s("Once selected, you will be able to play.")
    s("Some L E Ds will show you where to press.")

    time.sleep(0.5)

    cs.play_song(0)
    return cs.select_or_next_song()


