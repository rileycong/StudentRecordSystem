# IMPORT LIBRARIES AND MODULES
import datetime
from tkinter import *
import tkinter.messagebox as mb
from tkinter import ttk
import connect_db

# DESIGN VARIABLES
labelfont = ('Ariel', 12)
entryfont = ('Ariel', 11)
btfont = ('Ariel',11,'bold')
entrywidth = 22
btwidth = 15
lf_bg = 'lavender' # bg color for the left_frame

##################### PROGRAM DECLARATION ########################
class StudentRecordSystem():
    def __init__(self, main):

    #=========== WINDOW INIT ==================
        self.main = main
        self.main.title('Student Management System')
        self.main.geometry('1000x600')
        self.main.resizable(0, 0)
        self.main.iconbitmap('student.ico')

    #=========== DECLARE VARIABLES ==================
        self.id_strvar = StringVar()
        self.name_strvar = StringVar()
        self.dob_strvar = StringVar()
        self.gender_strvar = StringVar()
        self.class_strvar = StringVar()
        self.contact_strvar = StringVar()
        self.searchby_strvar = StringVar()
        self.search_strvar = StringVar()

    #=========== WINDOW ZONING ==================
        title_frame = Frame(main, bg='teal')
        title_frame.place(x=0, y=0, height=35, width=1000)
        left_frame = Frame(main, bg=lf_bg)
        left_frame.place(x=0, y=36, height=600, width=400)
        search_frame = Frame(main, bg="grey")
        search_frame.place(x=400, y=36, height=40, width=600)
        table_frame = Frame(main, bg="grey")
        table_frame.place(x=400, y=76, height=560, width=600)

    #=========== TITLE FRAME ==================
        Label(title_frame, text="STUDENT MANAGEMENT SYSTEM", font=("Ubuntu", 14, 'bold'), bg='teal', fg='light cyan').place(x=350, y=3)

    #=========== LEFT FRAME ==================
        # LABELS
        Label(left_frame, text="ID", font=labelfont, bg=lf_bg).place(x=30, y=50)
        Label(left_frame, text="Name", font=labelfont, bg=lf_bg).place(x=30,y=100)
        Label(left_frame, text="Date of Birth", font=labelfont, bg=lf_bg).place(x=30,y=150)
        Label(left_frame, text="Gender", font=labelfont, bg=lf_bg).place(x=30, y=200)
        Label(left_frame, text="Class", font=labelfont, bg=lf_bg).place(x=30, y=250)
        Label(left_frame, text="Contact Number", font=labelfont, bg=lf_bg).place(x=30, y=300)

        # ENTRY
        Entry(left_frame, width=entrywidth, textvariable=self.id_strvar, font=entryfont).place(x=170, y=50)
        Entry(left_frame, width=entrywidth, textvariable=self.name_strvar, font=entryfont).place(x=170, y=100)
        Entry(left_frame, width=entrywidth, textvariable=self.dob_strvar, font=entryfont).place(x=170, y=150)
        OptionMenu(left_frame, self.gender_strvar, 'Male', "Female").place(x=170, y=200, width=150)
        Entry(left_frame, width=entrywidth, textvariable=self.class_strvar, font=entryfont).place(x=170,y=250)
        Entry(left_frame, width=entrywidth, textvariable=self.contact_strvar, font=entryfont).place(x=170, y=300)

        # BUTTONS
        Button(left_frame, text='Add Record', font=btfont, command=self.add_record, width=btwidth).place(x=120, y=380)
        Button(left_frame, text='Clear Fields', font=btfont, command=self.reset_fields, width=btwidth).place(x=40, y=430)
        Button(left_frame, text='Update Record', font=btfont, command=self.update_record, width=btwidth).place(x=200, y=430)
        Button(left_frame, text='Delete Record', font=btfont, command=self.delete_record, width=btwidth).place(x=40, y=480)
        Button(left_frame, text='Exit Program', font=btfont, command=self.exit_program, width=btwidth).place(x=200, y=480)

    #=========== SEARCH FRAME ==================
        Label(search_frame, text="Search By", font=('Ariel',11), bg='grey', fg='azure').place(x=5, y=8)
        search_option=['ID', 'Name', 'ContactNumber']
        OptionMenu(search_frame, self.searchby_strvar, *search_option).place(x=90, y=8, width=125, height=25)
        Entry(search_frame, width=30, textvariable=self.search_strvar, font=('Ariel',10)).place(x=235, y=9)
        Button(search_frame, text='Search', font=('Ariel',10,'bold'), command=self.search_record, width=9, height=1).place(x=490, y=7)

    #=========== TABLE FRAME ==================
        # LABEL
        self.table = ttk.Treeview(table_frame, selectmode=BROWSE,     # Create a table view
                    columns=("ID", "Name", "Date of Birth", "Gender", "Class", "Contact Number"))
        # SCROLLER
        X_scroller = Scrollbar(self.table, orient=HORIZONTAL)
        Y_scroller = Scrollbar(self.table, orient=VERTICAL, command=self.table.yview)
        X_scroller.pack(side=BOTTOM, fill=X)
        Y_scroller.pack(side=RIGHT, fill=Y)
        X_scroller.config(command=self.table.xview)
        Y_scroller.config(command=self.table.yview)

        # CONFIGURE TABLE
        # heading
        style = ttk.Style()
        style.theme_use("classic")
        style.configure("Treeview.Heading", background="black", foreground="white")
        self.table.heading('ID', text='ID', anchor=CENTER)
        self.table.heading('Name', text='Name', anchor=CENTER)
        self.table.heading('Date of Birth', text='DOB', anchor=CENTER)
        self.table.heading('Gender', text='Gender', anchor=CENTER)
        self.table.heading('Class', text='Class', anchor=CENTER)
        self.table.heading('Contact Number', text='Contact', anchor=CENTER)
        # column
        self.table.column('#0', width=0, stretch=NO, anchor=CENTER)
        self.table.column('#1', width=40, stretch=NO, anchor=CENTER)
        self.table.column('#2', width=150, stretch=NO)
        self.table.column('#3', width=100, stretch=NO, anchor=CENTER)
        self.table.column('#4', width=80, stretch=NO, anchor=CENTER)
        self.table.column('#5', width=100, stretch=NO, anchor=CENTER)
        self.table.column('#6', width=120, stretch=NO, anchor=CENTER)

        self.table.place(relwidth=1, relheight=0.94, relx=0)
        self.table.bind("<ButtonRelease>",self.get_cursor)  # this is the function that select each row
        self.display_records()

    #=========== FUNCTIONS ==================    
    # MAIN FUNCTIONS
    def add_record(self):
        self.get_input_data()
        if not ID or not Name or not DOB or not Gender\
        or not Class or not Contact:
            mb.showerror('Error!', "Please fill all the missing fields!!")
        else:
            try:
                con = connect_db.getConnection()
                cur = con.cursor()
                add = "insert into student_record values (%s,%s,%s,%s,%s,%s)"
                cur.execute(add,(ID, Name, DOB, Gender, Class, Contact))
                con.commit()
                mb.showinfo('Record added', f"Record of {Name} was successfully added")
                self.reset_fields()
                self.display_records()
                con.close()
            except:
                mb.showerror('Error!', 'Invalid or existed input')

    def display_records(self):
        con = connect_db.getConnection()
        cur = con.cursor()      
        cur.execute('select * from student_record')
        rows = cur.fetchall()
        if len(rows)!=0:
            self.table.delete(*self.table.get_children())
            for row in rows:
                self.table.insert('',END,values=row)
            con.commit()
        con.close()

    def update_record(self):
        mess = mb.askyesno('Update','Do you want to update the information of this student?')
        if mess>0:
            self.get_input_data()
            if not ID or not Name or not DOB or not Gender\
            or not Class or not Contact:
                mb.showerror('Error!', "Please fill all the missing fields!!")
            else:
                try:
                    con = connect_db.getConnection()
                    cur = con.cursor()
                    update = "update student_record set ID=%s,Name=%s,DOB=%s,Gender=%s,Class=%s,ContactNumber=%s where ID=%s"
                    cur.execute(update,(ID, Name, DOB, Gender, Class, Contact,ID))
                    con.commit()
                    mb.showinfo('Record updated', f"Record of {Name} was successfully updated")
                    self.reset_fields()
                    self.display_records()
                    con.close()
                except:
                    mb.showerror('Error!', 'Invalid or existed input')

    def delete_record(self):
        mess = mb.askyesno('Delete','Do you want to delete the information of this student?')
        if mess>0:
            con = connect_db.getConnection()
            cur = con.cursor()
            delete = "delete from student_record where ID=%s"
            cur.execute(delete,(self.id_strvar.get()))
            con.commit()
            mb.showinfo('Record deleted', f"Record of {self.name_strvar.get()} was successfully deleted")
            self.reset_fields()
            self.display_records()
            con.close()
    
    def search_record(self):
        con = connect_db.getConnection()
        cur = con.cursor()
        cur.execute("select * from student_record where "\
                + str(self.searchby_strvar.get())+" like '%"\
                + str(self.search_strvar.get())+"%'")
        rows = cur.fetchall()
        if len(rows)!=0:
            self.table.delete(*self.table.get_children())
            for row in rows:
                self.table.insert('',END,values=row)
            con.commit()
        con.close()
        
    def exit_program(self):
        mess = mb.askyesno('Exit','Do you want to exit the program?')
        if mess>0:
            self.main.destroy()

    # UTIL FUNCTIONS
    def get_input_data(self):
        global ID, Name, DOB, Gender, Class, Contact
        ID = self.id_strvar.get()
        Name = self.name_strvar.get()
        DOB = self.dob_strvar.get()
        Gender = self.gender_strvar.get()
        Class = self.class_strvar.get()
        Contact = self.contact_strvar.get()

    def reset_fields(self):
            for i in ['self.id_strvar', 'self.name_strvar', 'self.dob_strvar', \
            'self.gender_strvar', 'self.class_strvar', 'self.contact_strvar']:
                exec(f"{i}.set('')")

    def get_cursor(self,ev):   # This function select and focus on a single row
        cursor_row = self.table.focus()
        contents = self.table.item(cursor_row)
        row = contents['values']
        if len(row)!= 0:
            self.id_strvar.set(row[0])
            self.name_strvar.set(row[1])
            self.dob_strvar.set(row[2])
            self.gender_strvar.set(row[3])
            self.class_strvar.set(row[4])
            self.contact_strvar.set(('0'+str(row[5])))  # concat with 0 so that the 0 is kept while editing


##################### PROGRAM INITIALIZATION ########################
if __name__ == "__main__":
    print("Starting the Student Record System")
    main = Tk()
    obj = StudentRecordSystem(main)        
    main.mainloop() 