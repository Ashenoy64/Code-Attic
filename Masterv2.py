import base64
import os 
import cv2,imutils,socket
from tkinter import filedialog
import time

sock=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

host_name=socket.gethostname()
host_ip=socket.gethostbyname(host_name)

port=8080
sock.bind((host_ip,port))

socket.timeout(1)
print(host_ip)

print("Select movie to broad cast")
time.sleep(1)

vid=cv2.VideoCapture(0)
fps,st,frames_to_count,cnt=(0,0,20,0)
client_list=[]
while True:
    msg,addr=sock.recvfrom(65536)
    print(addr[0],"has connected")
    sock.sendto("ok".encode(),addr)
    while (vid.isOpened()):
        _,frame=vid.read()
        frame=imutils.resize(frame,width=400)
        encoded,buffer=cv2.imencode(".jpg",frame,[cv2.IMWRITE_JPEG_QUALITY,80])
        message=base64.b64encode(buffer)
        sock.sendto(message,addr)
        cv2.imshow("broadcast",frame)
        key=cv2.waitKey(1)& 0xFF
        if key==ord("q"):
            sock.close()
            break