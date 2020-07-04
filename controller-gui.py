#!/usr/bin/env python3

from tkinter import *
from tkinter import ttk
import serial


root = Tk()
root.title("Light Controller GUI")



photo = PhotoImage(file="images/led.png")
root.iconphoto(False,photo)

statusLabel = Label(root,text="",relief=SUNKEN,anchor=W)

connectionFrame = LabelFrame(root,text="Connection")
controlFrame = LabelFrame(root,text="Control")


def sendDuration():
    statusLabel['text'] = durationSpin.get()


durationLabel = Label(controlFrame,text="Duration")
durationSpin = Spinbox(controlFrame,values=[1,4,5,5])
durationBtn = Button(controlFrame,text="Send",command=sendDuration)
baudrateCmbox = ttk.Combobox(connectionFrame,values=[9600,19200,38400,57600,115200],state="readonly")
baudrateCmbox.current(0)

def connectByUART():
    global ser
    try:
        ser = serial.Serial('dev/ttyUSB0',baudrateCmbox.get())
        statusLabel['text'] = "Connection established!"
    except:
        statusLabel['text'] = "Connection could not be established."

connectBtn = Button(connectionFrame,text="Connect",command=connectByUART)

connectionFrame.grid(row=0,column=1,sticky=W+S+N,padx=5)
controlFrame.grid(row=0,column=0,sticky=W+S+N,padx=5)

connectByUART()

#Elements placement
durationSpin.grid(row=0,column=1,sticky=W,padx=10)
durationLabel.grid(row=0,column=0,sticky=W,padx=5)
durationBtn.grid(row=0,column=2,sticky=W,padx=5)

connectBtn.grid(row=0,column=0,sticky=W+E,padx=5,pady=5)
baudrateCmbox.grid(row=1,column=0,sticky=W+E,padx=5,pady=5)

statusLabel.grid(row=2,column=0,sticky=W+E,columnspan=3,padx=5)

root.mainloop()

