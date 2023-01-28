import tkinter as tk
from tkinter import ttk
import nbtlib

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

root = tk.Tk()
treeview = ttk.Treeview(root)
treeview.pack(expand=True, fill='both')

nbt_file = nbtlib.load('SimpleNBT.nbt')
print_tags_gui('', nbt_file, treeview)

root.mainloop()
