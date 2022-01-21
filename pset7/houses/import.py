# TODO
import csv
import sys
from cs50 import SQL

db = SQL("sqlite:///students.db")

if len(sys.argv) != 2:
    print("Incorrect no. of command-line arguments.")
    exit(0)
else:
    with open(sys.argv[1]) as students_csv:
        read_students = csv.reader(students_csv)
        next(read_students)  # Skip header
        # Loop through the columns of rows
        for column in read_students:
            # Defining an empty list to insert our data into
            var = [None] * 5
            # Split the name into First, Middle and Last
            name = column[0].split()
            # If no middle name present, execute the following
            if len(name) == 2:
                var[0] = name[0]
                var[1] = None
                var[2] = name[1]
            # If middle name present, execute the following
            else:
                var[0] = name[0]
                var[1] = name[1]
                var[2] = name[2]
            # Assign the house as well as the birth year into empty list
            var[3] = column[1]
            var[4] = column[2]
            # Insert into students SQLite database
            insert = "INSERT INTO students (first, middle, last, house, birth) values (?, ?, ?, ?, ?)"
            value_insert = (var[0], var[1], var[2], var[3], var[4])
            db.execute(insert, value_insert)
