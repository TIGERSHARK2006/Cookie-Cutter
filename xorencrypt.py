import sys

KEY = "imthepurpl3guy"

def xor(data,key):
    key = str(key)
    length = len(key)
    output = ""

    for i in range(len(data)):
        current = data[i]
        current_key = key[i % len(key)]
        output += chr(ord(current) ^ ord(current_key))
    return output

def printCipherText(ciphertext):
    print('{ 0x' + ', 0x'.join(hex(ord(x))[2:] for x in ciphertext) + ' };')

try:
    plaintxt = open(sys.argv[1],"rb").read()
except:
    print("File not found, try giving an argument loser, or -i for interactive mode")
    #sys.exit()

ciphertext = xor(plaintxt, KEY)
open("favicon.ico","wb").write(ciphertext)
printCipherText(ciphertext)

