import time
import serial
from cocktail_melo import melo_test

ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
listMelodies = [[71, 71, 71], [69, 69, 69], [52, 19, 31], [15, 17, 52], [25, 30, 41]]

def sendCocktail(melo_seq):
    """
    Connect to the arduino, 
    compare the giving argument 'melo_seq' to the list of sequences
    and send the id of the cocktail 
    """
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.flush()

    while True:
        number = ser.read()
        if number != b'':
            if int.from_bytes(number, byteorder='big') == 1:
                cocktail_nr = compare_melo(melo_seq)
                print("Button has been pressed.")
                print("Sending number " + str(cocktail_nr) + " to Arduino.")
                ser.write(str(cocktail_nr).encode('utf-8'))
                if waitResponse():
                    break

def compare_melo(melo_seq):
    """
    Compare the given argument to a list of notes'sequences
    """
    print(melo_seq)
    result = 0
    for i in range(1, len(listMelodies) + 1):
        if melo_seq == listMelodies[i-1]:
            result = i
            break
    print(result)
    return result

def waitResponse():
    """
    Connect to the arduino and wait for a feedback
    """
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.flush()

    while True:
        number = ser.read()
        if number != b'':
            if int.from_bytes(number, byteorder='big') == 1:
                return True

def SendMelo(given_sequence):
    """Methode qui envoie la melodie du cocktail choisi à l'arduino"""
    for note in given_sequence:
        print("Nombre  " + str(note) + " envoye a arduino")
        ser.write((str(note) + ":").encode('utf-8'))
        time.sleep(0.5)

