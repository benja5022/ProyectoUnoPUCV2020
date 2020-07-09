import csv
with open('Partida1.csv','w') as filepepito:
    with open('pepito.txt', 'r') as file:
        #reader = csv.reader(file)
        filepepito.write(",nombre_jugador,id_carta,zona,\n")
        for row in file:
            
            row = row.replace(';',',')
            filepepito.write(row)
            
    file.close()
filepepito.close()

#with open ('Cartas2.csv','r') as file:
#    with open ('Cartas.csv','w') as file2:
#        for row in file:
#            row = row.replace(';',',')
#            file2.write(row)
            
#file.close()
