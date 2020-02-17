# Cryptographic-Engineering


DKY 密码工程原理作业

## paddingOracle

### 文件结构  

```
paddingOracle
|————CBC.py
|----main.py
```

### 测试运行方式

main.py

```python
if __name__ == '__main__':
    iv = b'1234567887654321' #随意输入长度为16个字符
    M = 'test for padding-oracle' # 明文长度为要求[16, 32)，长度可变版本有时间改
    if len(M) < 16 or len(M) >=32:
        print("M error")
    else:
        C = CBC.encrypt(iv, M)
        print(paddingOracle(iv, C))
```

### TODO

- 明文长度无限制
- 冗余代码整理