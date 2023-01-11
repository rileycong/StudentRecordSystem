import tkinter as tk
from tkinter import *
from PIL import ImageTk
import tkinter.messagebox as mb
import connect_db
import System

# DESIGN VARIABLES
lg_labelfont = ('Verdana', 13, 'bold')
lg_entryfont = ('Ariel', 12, 'bold')
lg_btfont = ('Ariel',12)

class LoginScreen():
    def __init__(self,login):
        
    # INITIATE WINDOW
        self.login = login
        self.login.title('Login - Student Record System')
        self.login.geometry('1000x600')
        self.login.resizable(0,0)
        self.login.iconbitmap('./Assets/icon.ico')

    # DECLARE ENTRY VARIABLES
        self.username_strvar = StringVar()
        self.pass_strvar = StringVar()

    # BACKGROUND IMAGE
        self.bgimage = PhotoImage(file='./Assets/background.png')
        Label(login, image=self.bgimage).place(x=0,y=0)

    # LOGIN FRAME
        '''
        The components of the login frame include:
        - Logo image
        - Username + Password Entries
        - Login button
        '''
        ## Create and place the frame
        login_frame = Frame(login, bg='ghost white')
        login_frame.place(x=350,y=200)

        ## Logo Image
        self.lgimage = PhotoImage(file='./Assets/logo.png')
        Label(login_frame,image=self.lgimage,bg='ghost white').grid(row=0,column=0,columnspan=2,pady=10)

        ## Username
        self.userimage = PhotoImage(file='./Assets/username.png')
        Label(login_frame, image=self.userimage,text=' Username',font=lg_labelfont,
                    bg='ghost white',compound=LEFT).grid(row=1,column=0,padx=10,pady=10)
        Entry(login_frame,textvariable=self.username_strvar,font=lg_entryfont,fg='royalblue4',bd=2).grid(row=1,column=1,padx=10,pady=10)

        ## Password
        self.passimage = PhotoImage(file='./Assets/password.png')
        Label(login_frame, image=self.passimage,text=' Password',font=lg_labelfont,
                    bg='ghost white',compound=LEFT).grid(row=2,column=0,padx=10,pady=10)
        Entry(login_frame,textvariable=self.pass_strvar,show="*",font=lg_entryfont,fg='royalblue4',bd=2).grid(row=2,column=1,padx=10,pady=10)

        ## Login Button
        Button(login_frame,text='Login',font=lg_btfont,bg='royalblue',activebackground='royalblue', 
                fg='snow',width=10,cursor='hand2',command=self.login_program).grid(row=3,column=0,columnspan=2,pady=15)
        
    def login_program(self):
        if self.username_strvar.get() == '' or self.pass_strvar.get() == '':
            mb.showerror('Error!','Please fill all the missing fields!!')
        else:
            lg_con = connect_db.getConnection()
            cur = lg_con.cursor()
            verify = 'select*from admin_accounts where username = %s and password = %s'
            cur.execute(verify,(self.username_strvar.get(),self.pass_strvar.get()))
            results = cur.fetchall()
            if results:
                for i in results:
                    mb.showinfo("Success",'Welcome to the Student Record System')
                    self.login.destroy()
            else:
                mb.showerror('Error','Please enter the correct credentials')

if __name__ == "__main__":
    login = Tk()
    log_obj = LoginScreen(login)        
    login.mainloop()