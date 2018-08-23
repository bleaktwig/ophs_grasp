fin = open("processed_data/SET4", 'r', 1)
file = fin.read()
fin.close()

counter = 0
for line in file.splitlines():
    if counter % 4 == 3:
        print(line)
    counter += 1
