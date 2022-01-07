#!/usr/bin/env python3

def get_binnum(s):
    s = s.replace(' ', '')
    s = s.replace('.', '0')

    assert(len(s) == 32)

    return int(s, 2)

lines = []

with open("main.s", 'r') as f:
    lines = f.readlines()

if not lines:
    quit(0)

i = 0
for line in lines:
    i += 1
    try:
        if not line:
            continue

        if '#' not in line or '/' not in line:
            continue

        line = line.strip('#')
        line = line.strip(' ')
        sp = line.split('#')
        name = sp[0].split(' ')[0]
        nsp = sp[1].split('/')

        hexnum = int(nsp[0].strip(), 16)

        binnum = get_binnum(nsp[1].strip())

        if (hexnum != binnum):
            print(f"[{i}] {name} incorrect: hex {hex(hexnum)} != bin {hex(binnum)}")

    except Exception: 
        pass
