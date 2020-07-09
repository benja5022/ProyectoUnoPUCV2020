
import csv
with open('Partida2.csv','r') as file1:
    with open('textopartida2.txt', 'w') as file2:
        #file2.write(",nombre_jugador,id_carta,zona,\n")
        for fila in file1:
            fila = fila.replace('Pepe','Choromaikol')
            file2.write(fila)
    file2.close()
file1.close()

with open('Partida2.csv','w') as file1:
    with open('textopartida2.txt', 'r') as file2:
        #file1.write(",nombre_jugador,id_carta,zona,\n")
        for fila in file2:
            fila = fila.replace(';',',')
            file1.write(fila)
    file2.close()
file1.close()


