file = open("csv-data/2018-12-04-15-23-50.csv", "r")


largest = ""
index = 0

i = 0
for line in file:
    if i == 0:
        i += 1
        continue

    company = line.split(",")[4]

    if len(company) > len(largest):
        largest = company
        index = i

    i += 1

print(index, len(largest), largest)

