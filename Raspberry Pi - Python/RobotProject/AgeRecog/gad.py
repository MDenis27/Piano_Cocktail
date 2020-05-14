import cv2
import math
import numpy as np
import time

def isAgeOk(range):
    """
    Return True if the person is adult and False if not
    """
    forbiddenAges=['0-2', '4-6', '8-12', '15-20']
    for age in forbiddenAges:
        if range == age:
            return False
    return True

def takePic():
    """
    Take a picture and saves it as an image in 'img_analyse.jpg'
    """
    cap = cv2.VideoCapture(0) # video capture source camera 
    ret,frame = cap.read() # return a single frame in variable `frame`
    cv2.imwrite('img_analyse.jpg',frame)
    cap.release()

def highlightFace(net, frame, conf_threshold=0.7):
    """
    Detect if there a face or not.
    As arguments: 
    - net: the net of the trained neural newtork
    - frame: the picture to analyse 
    Return a new image with highlighted faces
    and the faces'boxes
    """
    frameOpencvDnn=frame.copy()
    frameHeight=frameOpencvDnn.shape[0]
    frameWidth=frameOpencvDnn.shape[1]
    # Compute the image to be comparable to the net
    blob=cv2.dnn.blobFromImage(frameOpencvDnn, 1.0, (300, 300), [104, 117, 123], True, False)
    # Compare the net with the computed image
    net.setInput(blob)
    # Compute to extract the faces
    detections=net.forward()
    faceBoxes=[]
    for i in range(detections.shape[2]):
        confidence=detections[0,0,i,2]
        if confidence>conf_threshold:
            # Compute to find the corners of the rectangle for the face
            x1=int(detections[0,0,i,3]*frameWidth)
            y1=int(detections[0,0,i,4]*frameHeight)
            x2=int(detections[0,0,i,5]*frameWidth)
            y2=int(detections[0,0,i,6]*frameHeight)
            faceBoxes.append([x1,y1,x2,y2])
            cv2.rectangle(frameOpencvDnn, (x1,y1), (x2,y2), (0,255,0), int(round(frameHeight/150)), 8)
    return frameOpencvDnn,faceBoxes

def detectAge():
    """
    Detect the age of the person.
    Take the taken picture (img_analyse.jpg),
    analyse it and return the age's range 
    """

    """
    - opencv_face_detector.pbtxt: protobuf file (in text format),
    holds the graph definition and the trained weights of the model
    - opencv_face_detector_uint8.pb: protobuf file (in binary format)
    - age_deploy.prototxt: describe the network configuration for ages
    - age_net.caffemodel: defines the internal states of the parameters
    of the layers of the neural networks for ages
    - gender_deploy.prototxt: describe the neural network configuration for genders
    - gender_net.caffemodel: defines the internal states of the parameters
    of the layers of the neural networks for genders
    """
    faceProto="AgeRecog/opencv_face_detector.pbtxt"
    faceModel="AgeRecog/opencv_face_detector_uint8.pb"
    ageProto="AgeRecog/age_deploy.prototxt"
    ageModel="AgeRecog/age_net.caffemodel"
    genderProto="AgeRecog/gender_deploy.prototxt"
    genderModel="AgeRecog/gender_net.caffemodel"

    MODEL_MEAN_VALUES=(78.4263377603, 87.7689143744, 114.895847746) # Mean values
    ageList=['(0-2)', '(4-6)', '(8-12)', '(15-20)', '(25-32)', '(38-43)', '(48-53)', '(60-100)']
    genderList=['Male','Female']

    # Load the neural network
    faceNet=cv2.dnn.readNet(faceModel,faceProto)
    ageNet=cv2.dnn.readNet(ageModel,ageProto)
    genderNet=cv2.dnn.readNet(genderModel,genderProto)

    takePic()
    video=cv2.VideoCapture('img_analyse.jpg')
    padding=20

    while cv2.waitKey(1)<0:
        hasFrame,frame=video.read()
        if not hasFrame:
            cv2.waitKey()
            break

        resultImg,faceBoxes=highlightFace(faceNet,frame)
        if not faceBoxes:
            print("No face detected")

        for faceBox in faceBoxes:
            face=frame[max(0,faceBox[1]-padding):
                       min(faceBox[3]+padding,frame.shape[0]-1),max(0,faceBox[0]-padding)
                       :min(faceBox[2]+padding, frame.shape[1]-1)]

            # Compute the face to be comparable to the net
            blob=cv2.dnn.blobFromImage(face, 1.0, (227,227), MODEL_MEAN_VALUES, swapRB=False)
            # Compare the net with the computed face
            genderNet.setInput(blob)
            # Compute to tell the age of the face
            genderPreds=genderNet.forward()
            gender=genderList[genderPreds[0].argmax()]
            print('Gender: {}'.format(gender))

            # Same as the age
            ageNet.setInput(blob)
            agePreds=ageNet.forward()
            age=ageList[agePreds[0].argmax()]
            print('Age: {} years'.format(age[1:-1]))
            
            return age[1:-1]
