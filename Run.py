import tkinter as tk
from tkinter import *
import System
import Login

##################### PROGRAM INITIALIZATION ########################
if __name__ == "__main__":
    print("Starting the Student Record System")
    login = Tk()
    log_obj = Login.LoginScreen(login)        
    login.mainloop()
    main = Tk()
    obj = System.StudentRecordSystem(main)        
    main.mainloop()