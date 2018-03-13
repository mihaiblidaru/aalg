import os

file = open("output.txt", "w")

table = []
for i in range(100,1001,100):
    tmp = []
    for j in range(1000, 10001,1000):
        stream = os.popen("(../ejercicio3 -tamanio " + str(i) + " -numP " + str(j) + ") | sort | head -n " + str(j)+ " | uniq -c | wc -l")
        tmp.append(int(stream.read()))
    table.append(tmp)

print(table)

file.write("N\\N_perms\t")
for j in range(1000, 10001,1000):
    file.write(str(j) + "\t")
file.write("\n")

for i in range(100,1001,100):
    file.write(str(i)+"\t")
    for x in table[int(i/100)-1]:
        file.write(str(x)+"\t")
    file.write("\n")

file.close()
