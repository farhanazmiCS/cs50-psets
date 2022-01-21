from cs50 import get_string

letters = 0
words = 1
sentences = 0

text = get_string("Text: ")

for text_count in range(0, len(text)):
    if text[text_count].isalpha() == True:
        letters += 1
    if text[text_count].isspace() == True:
        words += 1
    if text[text_count] == "." or text[text_count] == "!" or text[text_count] == "?":
        sentences += 1

L = letters / words * 100
S = sentences / words * 100
index = 0.0588 * L - 0.296 * S - 15.8
grade = round(index)

if grade >= 1 and grade <= 16:
    print(f"Grade {grade}")
elif grade < 1:
    print("Before Grade 1")
elif grade > 16:
    print("Grade 16+")
