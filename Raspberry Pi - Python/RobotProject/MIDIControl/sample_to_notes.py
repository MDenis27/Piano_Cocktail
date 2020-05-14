import wave
import numpy as np
import pygame as pg

wr = wave.open('samples/sound.wav', 'r')
# Set the parameters for the output file.
par = list(wr.getparams())
par[3] = 0  # The number of samples will be set by writeframes.
par = tuple(par)
ww = wave.open('notes/pitch1.wav', 'w')
ww.setparams(par)
fr = 1
sz = wr.getframerate()//fr  # Read and process 1/fr second at a time.
# A larger number for fr means less reverb.
c = int(wr.getnframes()/sz)  # count of the whole file
shift = -50//fr  # shifting 100 Hz
for num in range(c):
    da = np.fromstring(wr.readframes(sz), dtype=np.int16)
    left, right = da[0::2], da[1::2]  # left and right channel
    lf, rf = np.fft.rfft(left), np.fft.rfft(right)
    print(rf)
    lf, rf = np.roll(lf, shift), np.roll(rf, shift)
    lf[0:shift], rf[0:shift] = 0, 0
    nl, nr = np.fft.irfft(lf), np.fft.irfft(rf)
    ns = np.column_stack((nl, nr)).ravel().astype(np.int16)
    ww.writeframes(ns.tostring())

ww.close()
wr.close()

