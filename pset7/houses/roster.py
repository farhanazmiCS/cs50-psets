# TODO
import sys
from cs50 import SQL

db = SQL("sqlite:///students.db")

if len(sys.argv) != 2:
    print("Incorrect no. of command-line arguments. Try again.")
    exit(0)
else:
    execute = db.execute("SELECT first, middle, last, birth FROM students WHERE house = %s ORDER by last, first", (sys.argv[1]))
    for row in execute:
        if row['middle'] == None:
            print(row['first'], row['last'], "born", row['birth'])
        else:
            print(row['first'], row['middle'], row['last'], "born", row['birth'])