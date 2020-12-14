# -*- coding:utf-8 -*-
#
import tkinter
import tkinter.messagebox


class MyDialog:
    def __init__(self, root):
        self.top = tkinter.Toplevel(root)
        label = tkinter.Label(self.top, text='Your Password')
        label.pack()
        self.entry = tkinter.Entry(self.top, show='*')
        self.entry.pack()
        self.entry.focus()
        button = tkinter.Button(self.top, text='Ok',
                                command=self.Ok)
        button.pack()

    def Ok(self):
        self.input = self.entry.get()
        self.top.destroy()

    def get(self):
        return self.input
