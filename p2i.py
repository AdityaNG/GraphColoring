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


v = 3 # Number of vertices 
for c in range(1, v+1):
    print('colors : ', c)
    for i in range(c**v):
        print(' ', 'index : ', i, '\t->', [c,i] ,'->\t', dec_to_base(i, c).zfill(v))
        