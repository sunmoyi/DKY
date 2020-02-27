import CBC


def findB(iv, c1, c2):
    for i in range(16):
        c1_change = c1[:i] + (c1[i] ^ 1).to_bytes(length=1, byteorder='big', signed=False) + c1[i + 1:]
        C = c1_change + c2
        # print(CBC.check(iv, C))
        _, ans = CBC.check(iv, C)
        if not ans:
            return 16 - i
    return 0


def makeB(iv, c1):
    print(c1)
    for i in range(256):
        c1_change = c1[:-1] + i.to_bytes(length=1, byteorder='big', signed=False)
        # print(c1_change)
        if CBC.check(iv, c1_change)[1]:
            print(CBC.check(iv, c1_change))
            return
    return c1


def calculatec2(iv, c1, c2, b):
    # print(c1)
    # print(CBC.check(iv, c1 + c2))
    m2 = bytes()
    for i in range(15 - b, -1, -1):
        c1_end = bytes()
        for k in range(i + 1, 16):
            c1_end = c1_end + (c1[k] ^ (16 - i) ^ (15 - i)).to_bytes(length=1, byteorder='big', signed=False)
        # print(c1_end)
        for j in range(256):
            c1_change = c1[:i] + j.to_bytes(length=1, byteorder='big', signed=False) + c1_end
            # print(len(c1_change))
            if CBC.check(iv, c1_change + c2)[1]:
                # print(CBC.check(iv, c1_change + c2))
                m2 = (j ^ (16 - i) ^ c1[i]).to_bytes(length=1, byteorder='big', signed=False) + m2
                c1 = c1_change
                pass
    return m2


def calculatec1(iv, c1):
    # print(CBC.check(iv, iv + c1))
    iv_end = bytes()
    ans = bytes()
    for i in range(256):
        iv_change = iv[:-1] + i.to_bytes(length=1, byteorder='big', signed=False)
        if CBC.check(iv, iv_change + c1)[1]:
            # print(CBC.check(iv, iv_change + c1))
            iv_end = (0x01 ^ i ^ iv[-1]).to_bytes(length=1, byteorder='big', signed=False)
            # print(iv_end)
            ans = calculatec2(iv_change, iv_change, c1, 1)
            # print(ans)
            break
        # print(c1_change)
    # print(ans + iv_end)
    return ans + iv_end


def paddingOracle(iv, C):
    c1 = C[:16]
    c2 = C[-16:]
    m2 = bytes()
    b = findB(iv, c1, c2)
    # print("b = {0}".format(b))
    if b != 16:
        m2 = calculatec2(iv, c1, c2, b)
    m1 = calculatec1(iv, c1)

    return m1 + m2


if __name__ == '__main__':
    iv = b'1234567887654321' #任意长度为16的字符串
    M = 'test for padding-oracle' # 长度必须属于[16,32), 可变长度版本有时间更新
    if len(M) < 16 or len(M) >= 32:
        print("M error")
    else:
        C = CBC.encrypt(iv, M)
        print(paddingOracle(iv, C))
