from Crypto.Cipher import AES
from binascii import a2b_hex, b2a_hex
import time

runTime = 0


def add_to_16_by_number(text):
    add = 16 - (len(text.encode('utf-8')) % 16)
    text = text.encode('utf-8')
    text = text + add.to_bytes(length=1, byteorder='big', signed=False) * add
    return text


# 加密函数
def encrypt(iv, text):
    key = '9999999999999999'.encode('utf-8')
    mode = AES.MODE_CBC
    text = add_to_16_by_number(text)
    cryptos = AES.new(key, mode, iv)
    cipher_text = cryptos.encrypt(text)
    return cipher_text


# 解密后，去掉补足的空格用strip() 去掉
def decrypt(iv, text):
    key = '9999999999999999'.encode('utf-8')
    mode = AES.MODE_CBC
    cryptos = AES.new(key, mode, iv)
    plain_text = cryptos.decrypt(text)
    # print(plain_text)
    return plain_text
    # return bytes.decode(plain_text).rstrip('\0')


def check(iv, string):
    text = decrypt(iv, string)
    number = text[-1]
    if number > 16 or number == 0:
        return text, False

    flag = True
    for i in range(number * -1, -1):
        if text[i] != number:
            # print("text[{0}]".format(i) + str(text[i]))
            flag = False
    return text, flag


if __name__ == '__main__':
    iv = b'1234567887654321'
    e = encrypt(iv, "abcdefghijklmnopqrstuvw")
    d = check(iv, e)
    print("加密:", e)
    print("解密:", d)

    # string = 'abcdefghi'
    # print(add_to_16_by_number(string))
    # print(add_to_16(string))
