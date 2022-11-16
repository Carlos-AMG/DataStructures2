import random
import os


encryptionLevel = 128 // 8
maxKeyIndex = encryptionLevel - 1

def getKey():
    charPool = ""
    for i in range (0x00, 0xff):
        charPool += chr(i)
    key = ""
    for i in range(encryptionLevel):
        key += random.choice(charPool)
    return key

def encodeDecode(message, key):
    keyIndex = 0
    coded_msg = ""
    for char in message:
        if (char != " " or char != "\n"):
            coded_char = ord(char) ^ ord(key[keyIndex])
            coded_msg += chr(coded_char)
        else:
            coded_msg += char

        if keyIndex >= maxKeyIndex:
            keyIndex = 0
        else:
            keyIndex += 1
    return coded_msg

def encodeInterface():
    fileWriteOriginal = open("./OriginalText.txt", "w+")
    fileWriteEncode = open("./EncodedText.txt", "w+",encoding="utf-8")
    fileWriteKey = open("./Key.txt", "w+", encoding="utf-8")
    key = getKey()
    text = ""
    stopword1 = ""
    stopword2 = "stop"
    while True:
        line = input("Ingrese el texto: ")
        if line.strip() == stopword1 or line.strip() == stopword2:
            break
        text += "%s\n" % line
    fileWriteKey.write(key)
    fileWriteOriginal.write(text)
    encoded = encodeDecode(text, key)
    fileWriteEncode.write(encoded)
    fileWriteOriginal.close()
    fileWriteEncode.close()
    fileWriteKey.close()


def decodeInterface():
    fileReadEncoded = open("EncodedText.txt", "r", encoding="utf-8")
    fileReadKey = open("Key.txt", "r", encoding="utf-8")
    fileWrite = open("DecodedText.txt", "w+", encoding="utf-8")
    key = fileReadKey.read()
    decoded = encodeDecode(fileReadEncoded.read(), key)
    fileWrite.write(decoded)
    fileReadEncoded.close()
    fileWrite.close()



def main():
    while True:
        os.system("cls")
        print("\tMenu")
        print("Cifrado XOR")
        print("1)Encriptar\n2)Desencriptar\n3)Salir")
        choice = input("Ingrese su opcion: ")
        if choice == "3":
            return
        if choice == "1":
            print("\tEncriptar")
            print('''La encriptacion de su texto se guardara en un archivo txt, la opcion de desencriptar abrira el contenido de este y lo mostrara en pantalla (desencriptado)''')
            print("La entrada de texto no se detiene hasta encontrar un 'stop' o una linea vacia, si quiere detener la entrada ingrese 'stop'")
            encodeInterface()
            print("Su texto ahora esta encriptado en un archivo de texto")
            input()
        if choice == '2':
            print("\tDesencriptar")
            decodeInterface()
            file = open("DecodedText.txt", "r", encoding="utf-8")
            print("Su texto ahora esta desencriptado en un archivo de texto")
            print("El texto desencriptado es: ", file.read())
            input()

if __name__ == "__main__":
    main()
