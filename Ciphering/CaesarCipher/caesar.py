import os

def encodeDecode (message, shiftVal): #encodeDecode sirve para decode, solo pasamos el shift como numero negativo
    def decode_letter(letter):
        if letter.isalpha():
            alphaVal = ord('a' if letter.islower() else 'A')
            return chr((ord(letter) - alphaVal - shiftVal) % 26 + alphaVal)
        else:
            return letter
    return "".join(decode_letter(c) for c in message)

def encode(shiftval):
    fileWriteOriginal = open("./OriginalText.txt", "w+")
    fileWriteEncode = open("./EncodedText.txt", "w+")
    text = ""
    stopword1 = ""
    stopword2 = "stop"
    while True:
        line = input("Ingrese el texto: ")
        if line.strip() == stopword1 or line.strip() == stopword2:
            break
        text += "%s\n" % line
    fileWriteOriginal.write(text)
    fileWriteEncode.write(encodeDecode(text, shiftval))
    fileWriteOriginal.close()
    fileWriteEncode.close()

def decode(shiftVal):
    fileRead = open("EncodedText.txt", "r")
    fileWrite = open("DecodedText.txt", "w+")
    decoded = encodeDecode(fileRead.read(), shiftVal=shiftVal)
    fileWrite.write(decoded)
    fileRead.close()
    fileWrite.close()

def main():
    while True:
        os.system("cls")
        print("\tMenu")
        print("Cifrado Caesar")
        print("1)Encriptar\n2)Desencriptar\n3)Salir")
        choice = input("Ingrese su opcion: ")
        if choice == "3":
            return
        if choice == "1":
            print("\tEncriptar")
            print('''La encriptacion de su texto se guardara en un archivo txt, la opcion de desencriptar abrira el contenido de este y lo mostrara en pantalla (desencriptado)''')
            print("La entrada de texto no se detiene hasta encontrar un 'stop' o una linea vacia, si quiere detener la entrada ingrese 'stop'")
            shift = input("Shift: ")
            encode(int(shift))
            print("Su texto ahora esta encriptado en un archivo de texto")
            input()

        if choice == '2':
            print("\tDesencriptar")
            shift = input("Shift: ")
            decode(-1 * int(shift))
            print("Su texto ahora esta desencriptado en un archivo de texto")
            file = open("DecodedText.txt", "r", encoding="utf-8")
            print("El texto desencriptado es: ", file.read())
            input()


if __name__ == "__main__":
    main()
