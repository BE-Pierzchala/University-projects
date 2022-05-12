#!/usr/bin/env python

import tkinter
import time
from matplotlib.backends.backend_tkagg import (
    FigureCanvasTkAgg, NavigationToolbar2Tk)
# Implement the default Matplotlib key bindings.
from matplotlib.backend_bases import key_press_handler
from matplotlib.figure import Figure

import numpy as np


F = open("yes.txt", "w")

root = tkinter.Tk()
root.wm_title("YES")

i = [0]

Time = [time.time()]
delT = []

def action():
    global i
    global time
    global delT
    Time.append( time.time() - Time[0])
    
    if(len(Time) > 3):
        delT.append(Time[-1] - Time[-2])
    
    i.append(i[-1] + 1)
    
    F.write(str(i[-1]) + ", " + str(Time[-1]) + "\n")
    
    fig1.clf()
    fig1.add_subplot(111).plot(Time[1:], i[1:])
    
    #fig2.clf()
    #fig2.add_subplot(111).hist(delT, bins = 'auto')
    
    canvas1.draw()
    #canvas2.draw()


fig1 = Figure(figsize=(5, 4), dpi=100)
fig1.add_subplot(111).plot(Time[1:], i[1:])

#fig2 = Figure(figsize=(5, 4), dpi=100)
#fig2.add_subplot(111).hist(delT, bins = 'auto')

canvas1 = FigureCanvasTkAgg(fig1, master=root)  # A tk.DrawingArea.
canvas1.draw()
canvas1.get_tk_widget().pack(side=tkinter.LEFT, fill=tkinter.BOTH, expand=1)

#canvas2 = FigureCanvasTkAgg(fig2, master=root)  # A tk.DrawingArea.
#canvas2.draw()
#canvas2.get_tk_widget().pack(side=tkinter.RIGHT, fill=tkinter.BOTH, expand=1)




def on_key_press(event):
    action()
    key_press_handler(event, canvas1)


canvas1.mpl_connect("key_press_event", on_key_press)
#canvas2.mpl_connect("key_press_event", on_key_press)

def _save():
    F.close()

def _quit():
    root.quit()     # stops mainloop
    root.destroy()
    F.close()
    # this is necessary on Windows to prevent
                    # Fatal Python Error: PyEval_RestoreThread: NULL tstate

frame = tkinter.Frame(root)
frame.pack( side = tkinter.BOTTOM)

button_quit = tkinter.Button(frame, text="Quit", command=_quit)
button_save = tkinter.Button(frame, text="Save", command=_save)

bottomframe = tkinter.Frame(root)
bottomframe.pack( side = tkinter.BOTTOM )

button_save.pack(side = tkinter.LEFT)
button_quit.pack(side = tkinter.RIGHT)

tkinter.mainloop()
# If you put root.destroy() here, it will cause an error if the window is
# closed with the window manager.