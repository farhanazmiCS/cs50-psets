import csv  # access to importing csv files
import sys  # access to command line arguments
import re  # access to regular expression functions

# if argument count is not equals 3, print error message.
if len(sys.argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
else:
    # open database(csv) file, and read it
    with open(sys.argv[1]) as csv_file:
        read_row = csv.reader(csv_file)
        next(read_row)

        # open STR sequence file, and read it
        txt_file = open(sys.argv[2], "r")
        string_sequence = txt_file.read()

        # use regular expression "re.findall" to find the max number of consecutive STRs within the sequence. Returns integers.
        # Source: https://stackoverflow.com/questions/59746080/count-max-consecutive-re-groups-in-a-string
        if "AGATC" in string_sequence:
            AGATC_find_max = max([len(string_sequence) // 5 for string_sequence in re.findall(r'((?:AGATC)+)', string_sequence)])
        else:
            AGATC_find_max = 0
        if "AATG" in string_sequence:
            AATG_find_max = max([len(string_sequence) // 4 for string_sequence in re.findall(r'((?:AATG)+)', string_sequence)])
        else:
            AATG_find_max = 0
        if "TATC" in string_sequence:
            TATC_find_max = max([len(string_sequence) // 4 for string_sequence in re.findall(r'((?:TATC)+)', string_sequence)])
        else:
            TATC_find_max = 0
        if "TTTTTTCT" in string_sequence:
            TTTTTTCT_find_max = max(
                [len(string_sequence) // 8 for string_sequence in re.findall(r'((?:TTTTTTCT)+)', string_sequence)])
        else:
            TTTTTTCT_find_max = 0
        if "TCTAG" in string_sequence:
            TCTAG_find_max = max([len(string_sequence) // 5 for string_sequence in re.findall(r'((?:TCTAG)+)', string_sequence)])
        else:
            TCTAG_find_max = 0
        if "GATA" in string_sequence:
            GATA_find_max = max([len(string_sequence) // 4 for string_sequence in re.findall(r'((?:GATA)+)', string_sequence)])
        else:
            GATA_find_max = 0
        if "GAAA" in string_sequence:
            GAAA_find_max = max([len(string_sequence) // 4 for string_sequence in re.findall(r'((?:GAAA)+)', string_sequence)])
        else:
            GAAA_find_max = 0
        if "TCTG" in string_sequence:
            TCTG_find_max = max([len(string_sequence) // 4 for string_sequence in re.findall(r'((?:TCTG)+)', string_sequence)])
        else:
            TCTG_find_max = 0

        # storing max sequence values in a data structure (list)
        list_max_sequence = [AGATC_find_max, AATG_find_max, TATC_find_max,
                             TTTTTTCT_find_max, TCTAG_find_max, GATA_find_max, GAAA_find_max, TCTG_find_max]

        for column in read_row:
            if list_max_sequence[0] == int(column[1]) and list_max_sequence[1] == int(column[2]) and list_max_sequence[2] == int(column[3]):
                print(column[0])
                break
            elif list_max_sequence[0] == int(column[1]) and list_max_sequence[3] == int(column[2]) and list_max_sequence[1] == int(column[3]) and list_max_sequence[4] == int(column[4]) and list_max_sequence[5] == int(column[5]) and list_max_sequence[2] == int(column[6]) and list_max_sequence[6] == int(column[7]) and list_max_sequence[7] == int(column[8]):
                print(column[0])
                break

        else:
            print("No match")