import numpy as np
import samplerate
import pygame as pg
import time

mixer = pg.mixer
mixer.init(buffer=16)

# Synthesize data
fs = 1000.
t = np.arange(fs * 2) / fs
input_data = np.sin(2 * np.pi * 5 * t)

# Simple API
ratio = 1.5
converter = 'sinc_best'  # or 'sinc_fastest', ...
output_data_simple = samplerate.resample(input_data, ratio, converter)

print("first")
sound = mixer.Sound(input_data)
sound.play()

time.sleep(2)

print("sec")
sound = mixer.Sound(output_data_simple)
sound.play()

time.sleep(2)

print("third")
ratio = 0.5
converter = 'sinc_best'  # or 'sinc_fastest', ...
output_data_simple = samplerate.resample(input_data, ratio, converter)

sound = mixer.Sound(output_data_simple)
sound.play()

time.sleep(2)
