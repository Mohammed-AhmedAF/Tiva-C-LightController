#!/usr/bin/env python3

from tkinter import *
from tkinter import ttk
import platform
import serial

#Global variables
ser = serial.Serial()
baudrate = 0

root = Tk()
root.title("Light Controller GUI")
root.resizable(width=False,height=False)

try:
    photo = PhotoImage(file="images/led.png")
    root.iconphoto(False,photo)
except:
    print("No photo")

statusLabel = Label(root,text="",relief=SUNKEN,anchor=W)
osLabel = Label(root,text=platform.system(),relief=SUNKEN,anchor=W)

connectionFrame = LabelFrame(root,text="Connection")
controlFrame = LabelFrame(root,text="Control")

def sendLED(ledNumber):
    if (ledNumber==0):
        ser.write(b'a')
    elif (ledNumber == 1):
        ser.write(b'b')

led0Label = Label(controlFrame,text="LED 1")
led0Btn = Button(controlFrame,text="Toggle",command= lambda: sendLED(0))

led1Label = Label(controlFrame,text="LED 2")
led1Btn = Button(controlFrame,text="Toggle",command= lambda: sendLED(1))

baudrateCmbox = ttk.Combobox(connectionFrame,values=[9600,19200,38400,57600,115200],state="readonly")
baudrateCmbox.current(0)
portCmbox = ttk.Combobox(connectionFrame,values=["COM3","COM4"],state="readonly")
portCmbox.current(1)

def connectByUART():
    global ser
    global baudrate
    if (platform.system().startswith("Win")):
        port = portCmbox.get()
    else:
        port = "dev/ttypUSB0"
    if not ser.is_open:
        try:
            baudrate = baudrateCmbox.get()
            ser = serial.Serial(port,baudrate)
            statusLabel['text'] = "Connection established!"
        except:
            statusLabel['text'] = "Connection could not be established."
    else:
        if baudrate != baudrateCmbox.get():
            ser.close()
            connectByUART()
        else:
            statusLabel['text'] = "Connection already opened!"

connectBtn = Button(connectionFrame,text="Connect",command=connectByUART)

connectionFrame.grid(row=0,column=3,sticky=W+S+N+E,padx=5)
controlFrame.grid(row=0,column=0,sticky=W+S+N+E,padx=5,columnspan=3)

connectByUART()

#Elements placement
led0Label.grid(row=0,column=0,sticky=W,padx=5)
led0Btn.grid(row=0,column=1,columnspan=2,sticky=W,padx=5)

led1Label.grid(row=1,column=0,sticky=W,padx=5)
led1Btn.grid(row=1,column=1,columnspan=2,sticky=W,padx=5)

connectBtn.grid(row=2,column=0,sticky=W+E,padx=5,pady=5)
baudrateCmbox.grid(row=1,column=0,sticky=W+E,padx=5,pady=5)
portCmbox.grid(row=0,column=0,sticky=W+E,padx=5,pady=5)

statusLabel.grid(row=2,column=0,sticky=W+E,columnspan=3,padx=5)
osLabel.grid(row=2,column=3,sticky=W+E,padx=5,pady=5)

root.mainloop()

