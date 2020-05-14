import mido
import numpy
import pygame as pg
import time

def note_lettre(note):
	"""
	Transform a number of the midi into the lettre of the note.
	input :
	- note : int that gives the number 
	  of pressed tile of the midi input
	Return the correct lettre note.
	"""
	n = note%12
	if(n == 0):
		return 'C'
	elif(n == 1):
		return 'C#'
	elif(n == 2):
		return 'D'
	elif(n == 3):
		return 'D#'
	elif(n == 4):
		return 'E'
	elif(n == 5):
		return 'F'
	elif(n == 6):
		return 'F#'
	elif(n == 7):
		return 'G'
	elif(n == 8):
		return 'G#'
	elif(n == 9):
		return 'A'
	elif(n == 10):
		return 'A#'
	else:
		return 'B'

def play_piano():
	"""
	After 7 seconds without playing, the played sequence will be return.
	Also allows to play the sounds.
	"""
	port = mido.open_input('Q49 MIDI 1') # open USB port

	# Mixer from pygame allows to play different sounds
	mixer = pg.mixer
	mixer.init(buffer=16) # setting buffer to 16 allows to run the sound quicker
	mixer.set_num_channels(100) # number of channels allows to play multiple sounds at the same time

	note_list = []
	start = time.time()
	print('Ready!')
	while time.time()-start < 7: #time.time()-start < 7
		try: #This filters out all non-note data
			for msg in port.iter_pending():
				if(msg.type == 'note_on'):
					octave = msg.note//12
					print('note : ' + str(note_lettre(msg.note)) + 'et octave : ' + str(octave))
					file = note_lettre(msg.note) + str(octave)
					print(file)
					sound = mixer.Sound('MIDIControl/notes/pianoB2/'+file+'.wav')
					sound.play()
					print(msg.note)
					note_list.append(msg.note)
					print(note_list)
					start = time.time()
		except AttributeError as error:
			print("Error excepted")
			print(error)
			pass
	return note_list

