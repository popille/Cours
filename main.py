
from deep_translator import GoogleTranslator
import csv

wordsave = []
trad = []
tradAL = []
tradEsp = []
i = 0
keys = ['Anglais', 'francais']

with open('name of the animals.txt', newline='') as csvfile:
    with open("listeAnimaux.csv", "w", newline="") as csv_file:
        spamreader = csv.reader(csvfile, delimiter=',', quotechar='|')
        for row in spamreader:
            word = (','.join(row))

            wordsave.append(','.join(row))
            translated = GoogleTranslator(source='auto', target='fr').translate(word)
            allemand = GoogleTranslator(source='auto', target='de').translate(word)
            espagnol = GoogleTranslator(source='auto', target='spanish').translate(word)
            trad.append(translated)
            tradAL.append(allemand)
            tradEsp.append(espagnol)
            print(espagnol)
            writter = csv.writer(csv_file)
            writter.writerow([wordsave[i], trad[i], tradAL[i], tradEsp[i]])
            i = i + 1





