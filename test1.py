from tkinter import *
from tkinter.ttk import Progressbar

root=Tk()
root.geometry("300x300")
p=Progressbar(root,orient=HORIZONTAL,length=200,mode="determinate",takefocus=True,maximum=100)
p.pack()
p.start()
p.step(10)
root.mainloop()