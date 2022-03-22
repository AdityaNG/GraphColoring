def dec_to_base(num,base):  #Maximum base - 36
    if num==0:
        return "0"

    base_num = ""
    while num>0:
        dig = int(num%base)
        if dig<10:
            base_num += str(dig)
        else:
            base_num += chr(ord('A')+dig-10)  #Using uppercase letters
        num //= base
    base_num = base_num[::-1]  #To reverse the string
    return base_num

class Mapper:
    def __init__(self, v) -> None:
        self.v = v
        self.l = 0
        for i in range(1, self.v+1):
            self.l += i**self.v
    
    def __len__(self):
        # 1**v + 2**v + ... + v**v
        return self.l

    def __getitem__(self, key):
        if key > self.l:
            raise IndexError
        
        key+=1
        t = 1
        c = 1
        while key>t:
            key -= t
            c+=1
            t = c**self.v
        
        key -= 1

        return key, c, dec_to_base(key, c).zfill(self.v)

    def __setitem__(self, key, value):
        print("set")


def get_length(v):
    l = 0
    for i in range(1, v+1):
        l += i**v
    return l

def get_item(v, key):
    l = get_length(v)
    if key > l:
        raise IndexError
        
    key+=1
    t = 1
    c = 1
    while key>t:
        key -= t
        c+=1
        t = c**v
        
    key -= 1

    return key, c, dec_to_base(key, c).zfill(v)

v = 7

m = Mapper(2)
l = get_length(v)
for i in range(l):
    j, c, col = get_item(v, i)
    print('index : ', i, '\t->', [c,j] ,'->\t', col)

exit()

v = 3

m = Mapper(2)
print(len(m))
for i in range(len(m)):
    j, c, col = m[i]
    print('index : ', i, '\t->', [c,j] ,'->\t', col)
