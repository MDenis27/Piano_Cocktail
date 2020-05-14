#!/usr/bin/env python

from AgeRecog import gad
from MIDIControl import midi_test as p
from cocktail_melo import cocktail_melo as melo
from textToSpeech import speak
import test_interface as ti
import time
import argparse
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)
GPIO.setup(10, GPIO.IN, pull_up_down=GPIO.PUD_UP)

parser = argparse.ArgumentParser()

parser.add_argument("--camera", "-c", help="enable camera and age detection", action="store_true")
parser.add_argument("--arduino", "-a", help="enable arduino communication", action="store_true")
parser.add_argument("--piano", "-p", help="enable piano", action="store_true")
parser.add_argument("--interface", "-i", help="enable user interface", action="store_true")
parser.add_argument("--button", "-b", help="enable the button pressure", action="store_true")

args = parser.parse_args()

age = '38-43'
seq = []

while True:
    speak("Place your glass.")
    if args.button:
        while True:
            if (GPIO.input(10) == False):
                break
            time.sleep(0.02)
    if args.camera:
        print("Camera args: OK")
        try:
            age = gad.detectAge()
        except:
            print("Camera is not attached")
    print(age)
    print(gad.isAgeOk(age))
    if gad.isAgeOk(age):
        if args.interface:
            selected_song = ti.selecting_song()
            print(selected_song)
#            if args.arduino:
# melo.SendMelo(selected_song)
        print("Let's play")
        if args.piano:
            print("Piano args: OK")
            try:
                seq = p.play_piano()
            except:
               print("Piano is not attached")
        if args.arduino:
            print("Arduino args: OK")
            try:
                melo.sendCocktail(seq)
                melo.waitResponse() # End the transmission
                print("Transmission ended")
            except:
               print("Arduino is not attached")
        time.sleep(5)
        print("gj")
    else:
        speak('Go home kiddo, this toy is for big boys')
        print("You are underaged")
        time.sleep(2)
