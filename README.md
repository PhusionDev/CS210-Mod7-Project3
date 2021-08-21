# CS210-Mod7-Project3
Project 3 Submission CS-210

- Summarize the project and what problem it was solving:
This application simulates a grocery administration utility that allows a user to print reports for the daily items purchased
based on an input file with a single grocery item on each line.
It also allows the user to search for a specific item and additionally print out a text-based graphical representation of items purchased.

- What did you do particularly well?
The C++ code communicates with Python scripts that read and write to files, working seamlessly between the two languages.

- Where could you enhance your code? How would these improvements make your code more efficient, secure, and so on?
For this project I didn't seem to need a lot of input validation based on the inputs, but if continuing to work on functionality it would
be a good idea to include more validation in the C++ user input code that parses and uses try/catch blocks, and also including additional
validations within the Pyton code method parameters.

- Which pieces of the code did you find most challenging to write, and how did you overcome this? What tools or resources are you adding to your support network?
The most challenging part was reading the input file line by line and stripping the newline characters from them before storing them in a list.
I used google and stackoverflow to find a post explaining how to use list comprehensions in python which could be used to solve such a problem.

- What skills from this project will be particularly transferable to other projects or course work?
Combining two programming languages together into a single application was a very helpful experience that I believe will be useful in later projects.
This will allow me to choose the right language for the task, and combine them into a project across multiple tasks if necessary.

- How did you make this program maintainable, readable, and adaptable?
I've including in line comments for most all lines in the code that explain what is happening, or a comment in the line above if the line was
already too long. Each function/method contains JavaDoc documentation describing what the function does, it's parameters, and also information on
anything that is returned from the function.
