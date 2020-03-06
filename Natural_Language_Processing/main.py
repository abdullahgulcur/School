import turkishnlp
import nltk
import os
from os.path import join
from nltk.tokenize import sent_tokenize

#from turkishnlp import detector
#obj = detector.TurkishNLP()

#obj.create_word_set()



class Alphabet():
    def __init__(self, character, index):
        self.character = character
        self.index = index

def turkishAlphabetInLowerCase():

    a = Alphabet('a', 0)
    b = Alphabet('b', 1)
    c = Alphabet('c', 2)
    ç = Alphabet('ç', 3)
    d = Alphabet('d', 4)
    e = Alphabet('e', 5)
    f = Alphabet('f', 6)
    g = Alphabet('g', 7)
    ğ = Alphabet('ğ', 8)
    h = Alphabet('h', 9)
    ı = Alphabet('ı', 10)
    i = Alphabet('i', 11)
    j = Alphabet('j', 12)
    k = Alphabet('k', 13)
    l = Alphabet('l', 14)
    m = Alphabet('m', 15)
    n = Alphabet('n', 16)
    o = Alphabet('o', 17)
    ö = Alphabet('ö', 18)
    p = Alphabet('p', 19)
    r = Alphabet('r', 20)
    s = Alphabet('s', 21)
    ş = Alphabet('ş', 22)
    t = Alphabet('t', 23)
    u = Alphabet('u', 24)
    ü = Alphabet('ü', 25)
    v = Alphabet('v', 26)
    y = Alphabet('y', 27)
    z = Alphabet('z', 28)

    alphabet = [a,b,c,ç,d,e,f,g,ğ,h,ı,i,j,k,l,m,n,o,ö,p,r,s,ş,t,u,ü,v,y,z]

    return alphabet

def turkishAlphabetInUpperCase():

    a = Alphabet('A', 0)
    b = Alphabet('B', 1)
    c = Alphabet('C', 2)
    ç = Alphabet('Ç', 3)
    d = Alphabet('D', 4)
    e = Alphabet('E', 5)
    f = Alphabet('F', 6)
    g = Alphabet('G', 7)
    ğ = Alphabet('Ğ', 8)
    h = Alphabet('H', 9)
    ı = Alphabet('I', 10)
    i = Alphabet('İ', 11)
    j = Alphabet('J', 12)
    k = Alphabet('K', 13)
    l = Alphabet('L', 14)
    m = Alphabet('M', 15)
    n = Alphabet('N', 16)
    o = Alphabet('O', 17)
    ö = Alphabet('Ö', 18)
    p = Alphabet('P', 19)
    r = Alphabet('R', 20)
    s = Alphabet('S', 21)
    ş = Alphabet('Ş', 22)
    t = Alphabet('T', 23)
    u = Alphabet('U', 24)
    ü = Alphabet('Ü', 25)
    v = Alphabet('V', 26)
    y = Alphabet('Y', 27)
    z = Alphabet('Z', 28)

    alphabet = [a,b,c,ç,d,e,f,g,ğ,h,ı,i,j,k,l,m,n,o,ö,p,r,s,ş,t,u,ü,v,y,z]

    return alphabet

def getIndexOfLetter(letter):

    alphabetLower = turkishAlphabetInLowerCase()
    alphabetUpper = turkishAlphabetInUpperCase()

    for char in alphabetLower:
        if(char.character == letter):
            return char.index

    for char in alphabetUpper:
        if (char.character == letter):
            return char.index

    return 0

def sumOfLetters(word):

    sum = 0
    for char0 in list(word):
        #print(char0)
        sum += getIndexOfLetter(char0)

    return sum

def generateSumOfLetter(sum):

    index = 1
    while 1:

        if not os.path.isfile("1150haber/ekonomi/{}.txt".format(index)):
            break

        f = open("1150haber/ekonomi/{}.txt".format(index), "r", encoding='utf8')
        for line in f:
            for word in line.split():
                if(sumOfLetters(word) == sum):
                    print(word)

        f.close()
        index += 1

    while 1:

        if not os.path.isfile("1150haber/magazin/{}.txt".format(index)):
            break

        f = open("1150haber/magazin/{}.txt".format(index), "r", encoding='utf8')
        for line in f:
            for word in line.split():
                if(sumOfLetters(word) == sum):
                    print(word)

        f.close()
        index += 1

    while 1:

        if not os.path.isfile("1150haber/saglik/{}.txt".format(index)):
            break

        f = open("1150haber/saglik/{}.txt".format(index), "r", encoding='utf8')
        for line in f:
            for word in line.split():
                if(sumOfLetters(word) == sum):
                    print(word)

        f.close()
        index += 1

    while 1:

        if not os.path.isfile("1150haber/siyasi/{}.txt".format(index)):
            break

        f = open("1150haber/siyasi/{}.txt".format(index), "r", encoding='utf8')
        for line in f:
            for word in line.split():
                if(sumOfLetters(word) == sum):
                    print(word)

        f.close()
        index += 1

    while 1:

        if not os.path.isfile("1150haber/spor/{}.txt".format(index)):
            break

        f = open("1150haber/spor/{}.txt".format(index), "r", encoding='utf8')
        for line in f:
            for word in line.split():
                if(sumOfLetters(word) == sum):
                    print(word)

        f.close()
        index += 1

def checkIfSentence(sentence):
    if sentence[-1] == '.' or sentence[-1] == '!' or sentence[-1] == '?':
        return True

def generateSumOfLetterForSentences(sum):

    index = 1
    str = ""

    while 1:

        if not os.path.isfile("1150haber/ekonomi/{}.txt".format(index)):
            break

        f = open("1150haber/ekonomi/{}.txt".format(index), "r", encoding='utf8')
        str = f.read().replace('\n', '')
        for s in sent_tokenize(str):
            if sumOfLetters(s) == sum and checkIfSentence(s):
                print(s)

        f.close()
        index += 1

    while 1:

        if not os.path.isfile("1150haber/magazin/{}.txt".format(index)):
            break

        f = open("1150haber/magazin/{}.txt".format(index), "r", encoding='utf8')
        str = f.read().replace('\n', '')
        for s in sent_tokenize(str):
            if sumOfLetters(s) == sum and checkIfSentence(s):
                print(s)

        f.close()
        index += 1

    while 1:

        if not os.path.isfile("1150haber/saglik/{}.txt".format(index)):
            break

        f = open("1150haber/saglik/{}.txt".format(index), "r", encoding='utf8')
        str = f.read().replace('\n', '')
        for s in sent_tokenize(str):
            if sumOfLetters(s) == sum and checkIfSentence(s):
                print(s)

        f.close()
        index += 1

    while 1:

        if not os.path.isfile("1150haber/siyasi/{}.txt".format(index)):
            break

        f = open("1150haber/siyasi/{}.txt".format(index), "r", encoding='utf8')
        str = f.read().replace('\n', '')
        for s in sent_tokenize(str):
            if sumOfLetters(s) == sum and checkIfSentence(s):
                print(s)

        f.close()
        index += 1

    while 1:

        if not os.path.isfile("1150haber/spor/{}.txt".format(index)):
            break

        f = open("1150haber/spor/{}.txt".format(index), "r", encoding='utf8')
        str = f.read().replace('\n', '')
        for s in sent_tokenize(str):
            if sumOfLetters(s) == sum and checkIfSentence(s):
                print(s)

        f.close()
        index += 1

def start():

    #moduleInput = input("Enter the module number you want to execute. 1, 2 or 3:")

    #if moduleInput == '1':
        #numberInput = input("Enter the sum of letter value:")
       # print("Words are generating...")
        #generateSumOfLetter(int(numberInput))
   # elif moduleInput == '2' or moduleInput == '3':
       ## numberInput = input("Enter the sum of letter value:")
       # print("Sentences are generating...")
       # generateSumOfLetterForSentences(int(numberInput))

    #str = ""
    #with open("1150haber/spor/601.txt", "r", encoding='utf8') as file:
       # str = file.read().replace('\n', '')

    #for s in sent_tokenize(str):
        #print(s)

    generateSumOfLetterForSentences(187)

start()