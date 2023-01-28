import nbtlib

nbt_file = nbtlib.load('SimpleNBT.nbt')

def print_tags(tag, indent=0):
    """
    A function to recursively print all the tags in an NBT file.
    """
    print(' ' * indent + str(tag))
    if isinstance(tag, nbtlib.tag.Compound):
        for key, value in tag.items():
            print_tags(value, indent + 2)
    elif isinstance(tag, nbtlib.tag.List):
        for value in tag:
            print_tags(value, indent + 2)

print_tags(nbt_file)
