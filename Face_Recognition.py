from face_recognition import load_image_file,face_encodings,face_locations,compare_faces
from os import listdir
from cv2 import VideoCapture,rectangle,putText,FILLED,FONT_HERSHEY_SIMPLEX,imshow


KNOWN_FACES_PATH = "known_f"
#UNKNOWN_FACES_PATH = "unknown_f"
TOLERANCE = 0.6
MODEL = "hog"  # hog
video=VideoCapture(0)
known_f = []
known_n = []

for nm in listdir(KNOWN_FACES_PATH):
    for file in listdir(f"{KNOWN_FACES_PATH}/{nm}"):
        img = load_image_file(f"{KNOWN_FACES_PATH}/{nm}/{file}")
        img_encod = face_encodings(img)[0]
        known_f.append(img_encod)
        known_n.append(file)

while True:
    #img = face_recognition.load_image_file(f"{UNKNOWN_FACES_PATH}/{file}")
    ret,img=video.read()
    locations = face_locations(img, model=MODEL)
    img_encod =face_encodings(img, locations)
    #img = cv.cvtColor(img, cv.COLOR_RGB2BGR)

    for face_encod, face_loc in zip(img_encod, locations):
        results = compare_faces(known_f, face_encod, TOLERANCE)
        match=None
        if True in results:
            match=known_n[results.index(True)]

            top_left=(face_loc[3],face_loc[0])
            bottom_right=(face_loc[2],face_loc[1])
            color=[0,255,0]
            rectangle(img,top_left,bottom_right,color,3)


            top_left=(face_loc[3],face_loc[2])
            bottom_right=(face_loc[1],face_loc[2]+22)
            rectangle(img,top_left,bottom_right,color,FILLED)
            putText(img,match,(face_loc[3]+10,face_loc[2]+15),FONT_HERSHEY_SIMPLEX,0.5,(200,200,200),2)
    imshow("Face recogntionn",img)
    if  0xFF==ord("q"):
        break
