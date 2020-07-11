import csv
with open('Partida1.csv','r') as filepepito:
    with open('pepito.txt', 'w') as file:
        #reader = csv.reader(file)
        #file.write(",Partida1,Juan,Pepe,nada,nada,\n")
        for row in filepepito:

            row = row[:-1] + ("nada,0,\n")
            #row = row.replace(';',',')
            file.write(row)
            
    file.close()
filepepito.close()

with open('pepito.txt', 'r') as file: 
    with open('Partida5.csv','w') as filepepito:
        for linea in file:
            filepepito.write(linea)
    file.close()
filepepito.close()


#with open ('Cartas2.csv','r') as file:
#    with open ('Cartas.csv','w') as file2:
#        for row in file:
#            row = row.replace(';',',')
#            file2.write(row)
            
#file.close()
