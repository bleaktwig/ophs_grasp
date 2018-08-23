fin = open("raws", 'r', 1)
file = fin.read()
fin.close()

result_list = [-1 for i in range(3)]
ct_list     = [-1 for i in range(3)]

counter = 0
for line in file.splitlines():
    if   counter == 0:
        print(line)
    elif counter == 1:
        result_list[0] = int(line)
    elif counter == 2:
        ct_list[0]     = int(line)
    elif counter == 3:
        result_list[1] = int(line)
    elif counter == 4:
        ct_list[1]     = int(line)
    elif counter == 5:
        result_list[2] = int(line)
    elif counter == 6:
        ct_list[2]     = int(line)
        # we have all the required data
        print("%.0f" % max(result_list))
        print("%.0f" % (sum(result_list) / float(len(result_list))))
        print("%.0f" % (sum(ct_list)     / float(len(ct_list))))

        counter = -1
    counter += 1
