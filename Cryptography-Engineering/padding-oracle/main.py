import CBC
import time

def findB(iv, c1, c2):
    for i in range(16):
        c1_change = c1[:i] + (c1[i] ^ 1).to_bytes(length=1, byteorder='big', signed=False) + c1[i + 1:]
        C = c1_change + c2
        _, ans = CBC.check(iv, C)
        if not ans:
            return 16 - i
    return 0


def calculatec2(iv, c1, c2, b):
    m2 = bytes()
    for i in range(15 - b, -1, -1):
        c1_end = bytes()
        for k in range(i + 1, 16):
            c1_end = c1_end + (c1[k] ^ (16 - i) ^ (15 - i)).to_bytes(length=1, byteorder='big', signed=False)
        for j in range(256):
            c1_change = c1[:i] + j.to_bytes(length=1, byteorder='big', signed=False) + c1_end
            if CBC.check(iv, c1_change + c2)[1]:
                m2 = (j ^ (16 - i) ^ c1[i]).to_bytes(length=1, byteorder='big', signed=False) + m2
                c1 = c1_change
                pass
    return m2


def calculatec1(iv, front, c1):
    iv_end = bytes()
    ans = bytes()
    for i in range(256):
        iv_change = front[:-1] + i.to_bytes(length=1, byteorder='big', signed=False)
        if CBC.check(iv, iv_change + c1)[1]:
            iv_end = (0x01 ^ i ^ front[-1]).to_bytes(length=1, byteorder='big', signed=False)
            ans = calculatec2(iv_change, iv_change, c1, 1)
            break
    return ans + iv_end


def paddingOracle(iv, C):
    C = iv + C
    eposion = len(C) / 16
    ans = bytes()
    for i in range(int(eposion) - 1):
        c1 = C[-32:-16]
        c2 = C[-16:]
        C = C[:-16]
        if i == 0:
            b = findB(iv, c1, c2)
            if b != 16:
                ans = calculatec2(iv, c1, c2, b)
            else:
                ans = bytes()
        else:
            ans = calculatec1(iv, c1, c2) + ans

    return ans


if __name__ == '__main__':
    iv = b'1234567887654321'
    M = 'test for padding-oracle. 20199102 Sun Qilong.' * 5
    C = CBC.encrypt(iv, M)
    print("len:", int(len(C) / 16), "blocks")

    time_start = time.time()
    print(paddingOracle(iv, C))
    time_end = time.time()
    print('spend time:', time_end - time_start, 's')
