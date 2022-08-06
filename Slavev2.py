import socket
import cv2
import base64
import time
import numpy as np

fps,st,frames_to_count,cnt=(0,0,20,0)

sock=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
while True:
    sock.sendto("hello".encode(),("#########",8080))
    data,_=sock.recvfrom(65536)
    if data.decode()=="ok":
        break
    while True:
        packet,_=sock.recvfrom(65536)
        data=base64.b64decode(packet," /")
        npdata=np.fromstring(data,dtype=np.uint8)
        frame=cv2.imdecode(npdata,1)
        frame=cv2.putText(frame,"FPS:"+str(fps),(10,40),cv2.FONT_HERSHEY_SIMPLEX,0.7,(0,0,255),2)
        cv2.imshow("Receining video",frame)
        key=cv2.waitKey(1) & 0xFF
        if key==ord("q"):
            sock.close()
            break


    