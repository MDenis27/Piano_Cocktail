import festival
import os

def speak(sentence):
    """
    Simple text to speech function
    Argument: the text to speak
    Speaks the given text
    """
    os.system('echo "{0}" | festival --tts'.format(sentence))
