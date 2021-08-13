import os
import re
import string

# paths/filenames for items purchased and the frequency data file
filepath = os.path.join(os.path.dirname(__file__), 'items_purchased.txt')
freqpath = os.path.join(os.path.dirname(__file__), 'frequency.dat')

# this method opens the items_purchased.txt file, reads the lines
# into a dictionary of items and their frequencies and then returns
# the dictionary.
def GetItemsFromFile():
    lines = [] # list of lines from the input file
    items = {} # dictionary for items purchased processed from lines in file

    # loop through lines in input file
    with open(filepath) as f:
        # list comprehension to read each line and strip the newline character
        # and store the lines into a lines list
        lines = [ line.strip() for line in f ]

    # loop through each line and either add item to dictionary
    # or increment the value in dictionary
    for line in lines:
        if not line in items:
            items[line] = 0 # item not yet in dictionary, add it with value of 0
        items[line] += 1 # increment item's purchase count by 1

    return items    # return dictionary of items


# this method prints a list of all items purchased and the purchase count for each
def PrintItemsPurchasedFrequency():
    items = GetItemsFromFile()  # get dictionary of items purchased from file

    # loop through items in dictionary and print the item name and it's purchase frequency
    for item, count in items.items():
        print(f"{item}: {count}")

# this method takes an item name and returns the number of times it was purchased
def PrintItemPurchaseFrequency(item_name):
    print(f"\nLocating today's purchase frequency for: {item_name}...")

    items = GetItemsFromFile()  # get dictionary of items purchased from file
    
    # check if the specified item is in the dictionary or not
    if item_name in items.keys():
        # item is in dictionary, return the number of times it was purchased
        return items[item_name]
    else:
        # item is NOT in dictionary, return 0
        return 0

# this method writes a frequency.dat file containing the purchase frequencies for each item
def GeneratePurchaseFrequencyReport():
    items = GetItemsFromFile()  # get dictionary of items purchased from file

    with open(freqpath, "w") as file:   # open frequency.dat for writing
        # loop through each item name and purchase count
        for item, count in items.items():
            file.write(f"{item} {count}\n") # write the item name and purchase count to file line

