# -*- coding:utf-8 -*-

'''
This file is for creating a all-in-one window, using four buttons to wake up
four command line inputs
'''

import stddraw
import tkinter
from universe import Universe
from tkinter import *
import tkinter.font as font
import tkinter.messagebox
from functools import partial
from MessageBox import MyDialog

root = tkinter.Tk(className='N Body Problem')
root.geometry('499x737')

# define my font
myFontHelvetica = font.Font(family='Helvetica', size=18, weight='bold')
# myFontScript = font.Font(font='Segoe Script')


class Login_Success(tkinter.Frame):
    def __init__(self, master=None):
        super().__init__(master)
        self.master = master
        self.pack()
        # self.create_background()
        self.ShowAuthor()
        # self.Create_Message_Box()
        # self.create_buttons()

    def create_background(self, events):
        self.canvas.pack_forget()
        self.backgroundname = tkinter.PhotoImage(file="ThreeBodyWelcome.png")
        self.background_label = Label(self.master, image=self.backgroundname)
        self.background_label.place(relx=0, rely=0)

        # Create a Button to Login
        # self.ThreeBodyLogin = tkinter.PhotoImage('ThreeBodyLogin.jpg')
        self.login = tkinter.Button(
            self.master, text='Login', command=self.Create_Message_Box)
        self.login['bg'] = '#87CEFA'  # DeepSkyBlue
        self.login.place(relx=0.46, rely=0.6)

    def ShowAuthor(self):
        self.canvas = tkinter.Canvas(self)
        self.canvas["width"] = 500
        self.canvas["height"] = 480
        self.canvas["bg"] = 'Azure'

        # import logo
        self.logo = tkinter.PhotoImage(file='phoenix6.png')
        self.canvas.create_image(250, 300, image=self.logo)

        # caption
        self.canvas.create_text(
            250, 80, font=myFontHelvetica, text="N Body Problem")
        self.canvas.create_text(
            250, 120, font=myFontHelvetica, text='by OrigamiAyc')
        self.canvas.pack()

        # respond to Left-Click, changing to Author Page from Welcome Page
        self.canvas.bind('<ButtonRelease-1>', self.create_background)

    def Create_Message_Box(self):
        password = MyDialog(self.master)
        self.login.wait_window(password.top)
        if password.get() == 'lapland':
            tkinter.messagebox.showinfo(
                'NBody', 'Welcome to the world of NBody')
            self.create_buttons()
        else:
            tkinter.messagebox.showinfo('NBody', 'Incorrect Password')

    def create_buttons(self):
        self.background_label.place_forget()
        self.login.place_forget()

        self.TwoBodyTiny = tkinter.Button(self)
        self.TwoBodyTiny["text"] = "TwoBodyTiny"
        self.TwoBodyTiny["command"] = self.TwoBodyTiny
        self.TwoBodyTiny['font'] = myFontHelvetica
        self.TwoBodyTiny['bg'] = '#98FB98'
        self.TwoBodyTiny['fg'] = '#800000'
        self.TwoBodyTiny['height'] = 1
        self.TwoBodyTiny['width'] = 15
        self.TwoBodyTiny['command'] = self.execTwoTiny
        self.TwoBodyTiny.pack(side=tkinter.TOP)

        self.TwoBody = tkinter.Button(self)
        self.TwoBody["text"] = "TwoBody"
        self.TwoBody["command"] = self.TwoBody
        self.TwoBody['font'] = myFontHelvetica
        self.TwoBody['bg'] = '#87CEFA'
        self.TwoBody['fg'] = '#8B008B'
        self.TwoBody['width'] = 15
        self.TwoBody['height'] = 1
        self.TwoBody['command'] = self.execTwoBody
        self.TwoBody.pack(side=tkinter.TOP)

        self.ThreeBody = tkinter.Button(self)
        self.ThreeBody["text"] = "ThreeBody"
        self.ThreeBody["command"] = self.ThreeBody
        self.ThreeBody['font'] = myFontHelvetica
        self.ThreeBody['bg'] = '#DEB887'
        self.ThreeBody['fg'] = '#191970'
        self.ThreeBody['height'] = 1
        self.ThreeBody['width'] = 15
        self.ThreeBody['command'] = lambda: self.execNBody(
            '3body.txt', 20000, stddraw.MAGENTA)
        self.ThreeBody.pack(side=tkinter.TOP)

        self.FourBody = tkinter.Button(self)
        self.FourBody["text"] = "FourBody"
        self.FourBody["command"] = self.FourBody
        self.FourBody['font'] = myFontHelvetica
        self.FourBody['bg'] = '#FFDEAD'
        self.FourBody['fg'] = '#228B22'
        self.FourBody['height'] = 1
        self.FourBody['width'] = 15
        self.FourExec = partial(
            self.execNBody, '4body.txt', 20000, stddraw.ORANGE)
        self.FourBody['command'] = self.FourExec
        self.FourBody.pack(side=tkinter.TOP)

    def execTwoTiny(self):
        filename = '2bodytiny.txt'
        dt = float(20000)
        PenColorTiny = stddraw.DARK_RED
        universe = Universe(filename)
        while True:
            universe.increaseTime(dt)
            stddraw.clear()
            universe.draw(PenColorTiny)
            stddraw.show(10)

    def execTwoBody(self):
        filename = '2body.txt'
        dt = float(20000)
        PenColor = stddraw.DARK_GREEN
        universe = Universe(filename)
        while True:
            universe.increaseTime(dt)
            stddraw.clear()
            universe.draw(PenColor)
            stddraw.show(10)

    def execNBody(self, fileName, calcFrequent, PenColor):
        self.filename = fileName
        self.dt = calcFrequent
        self.PenColor = PenColor
        self.universe = Universe(self.filename)
        while True:
            self.universe.increaseTime(self.dt)
            stddraw.clear()
            self.universe.draw(self.PenColor)
            stddraw.show(10)


game = Login_Success(master=root)
game.mainloop()
