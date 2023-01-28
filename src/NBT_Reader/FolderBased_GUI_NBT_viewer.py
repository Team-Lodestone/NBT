import tkinter as tk
from tkinter import ttk
import nbtlib
from tkinter import filedialog
import os

def print_tags_gui(parent, tag, treeview):
    """
    A function to recursively add all the tags in an NBT file to a treeview.
    """
    if isinstance(tag, nbtlib.tag.Compound):
        for key, value in tag.items():
            child = treeview.insert(parent, 'end', text=key)
            print_tags_gui(child, value, treeview)
    elif isinstance(tag, nbtlib.tag.List):
        for value in tag:
            child = treeview.insert(parent, 'end', text=str(value))
            print_tags_gui(child, value, treeview)
    else:
        treeview.insert(parent, 'end', text=str(tag))

def open_folder():
    folder_path = filedialog.askdirectory()
    for root, dirs, files in os.walk(folder_path):
        for file in files:
            if file.endswith(".nbt") or file.endswith(".dat"):
                nbt_file = nbtlib.load(os.path.join(root, file), byteorder='little')
                child = treeview.insert('', 'end', text=file)
                print_tags_gui(child, nbt_file, treeview)
        for dir in dirs:
            child = treeview.insert('', 'end', text=dir)
            open_folder(child, os.path.join(root, dir))

root = tk.Tk()
treeview = ttk.Treeview(root)
treeview.pack(expand=True, fill='both')

open_folder_button = tk.Button(root, text="Open Folder", command=open_folder)
open_folder_button.pack()

root.mainloop()
