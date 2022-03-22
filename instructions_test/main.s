
# instruction # opcode without arguments / binary opcode without arguments
# (the dots represent the arguments)

## special notes:
# deret - unsupported by psp-gcc and psp-objdump
# dis.int - not recognized by psp-gcc or psp-objdump
# halt - not recognized by psp-gcc or psp-objdump
# iack - not recognized by psp-gcc or psp-objdump
# lv - not recognized by psp-gcc or psp-objdump
# mfmc0 - not recognized by psp-gcc or psp-objdump
# rdhwr - unsupported by psp-gcc and psp-objdump
# rdpgpr - unsupported by psp-gcc and psp-objdump
# sll with no arguments is nop
# sub with no arguments is neg
# sv - is "svl.q" in psp-gcc and psp-objdump
# synci - unsupported by psp-gcc and psp-objdump
# vc2i(.s/p/t/q) - not recognized by psp-gcc or psp-objdump
# vuc2i - not recognized by psp-gcc or psp-objdump
# wait - unsupported by psp-gcc and psp-objdump
# wrpgpr - unsupported by psp-gcc and psp-objdump

## macros / pseudoinstructions
# b -> beq
# b -> bgez 
# bal -> bgezal
# beqz -> beq
# beqzl -> beql
# jalr 000f8090
# li -> ori
# move -> or
# nop 00000000
# not -> nor

# categories begin with ###, instructions may start with # (if unsupported
# by psp-gcc / psp-objdump)

# categories contain the smallest opcode,
# the largest opcode and the mask to filter out arguments
# in an opcode (negate the mask to obtain the arguments)
#-> is a reference to a subcategory

start:
nop                           # 00000000 / 000000 00000 00000 00000 00000 000000

### Special
##                        min # 00000000 / 000000 ..... ..... ..... ..... 000000 
##                        max # 0000003f / 000000 ..... ..... ..... ..... 111111
##                       mask # fc00003f / 111111 00000 00000 00000 00000 111111
sll $v1, $zero, 0             # 00000000 / 000000 ..... ..... ..... ..... 000000
#->srl/rotr                   # 00000002 - 00200002
sra $zero, $zero, 0           # 00000003 / 000000 ..... ..... ..... ..... 000011
sllv $zero, $zero, $zero      # 00000004 / 000000 ..... ..... ..... ..... 000100
#->srlv/rotrv                 # 00000006 - 00000046
srav $zero, $zero, $zero      # 00000007 / 000000 ..... ..... ..... ..... 000111
jr $zero                      # 00000008 / 000000 ..... ..... ..... ..... 001000
jalr $zero                    # 00000009 / 000000 ..... ..... ..... ..... 001001
movz $zero, $zero, $zero      # 0000000a / 000000 ..... ..... ..... ..... 001010
movn $zero, $zero, $zero      # 0000000b / 000000 ..... ..... ..... ..... 001011
syscall                       # 0000000c / 000000 ..... ..... ..... ..... 001100
break                         # 0000000d / 000000 ..... ..... ..... ..... 001101
sync                          # 0000000f / 000000 ..... ..... ..... ..... 001111
mfhi $zero                    # 00000010 / 000000 ..... ..... ..... ..... 010000
mthi $zero                    # 00000011 / 000000 ..... ..... ..... ..... 010001
mflo $zero                    # 00000012 / 000000 ..... ..... ..... ..... 010010
mtlo $zero                    # 00000013 / 000000 ..... ..... ..... ..... 010011
clz $zero, $zero              # 00000016 / 000000 ..... ..... ..... ..... 010110
clo $zero, $zero              # 00000017 / 000000 ..... ..... ..... ..... 010111
mult $zero, $zero             # 00000018 / 000000 ..... ..... ..... ..... 011000 
multu $zero, $zero            # 00000019 / 000000 ..... ..... ..... ..... 011001 
div $zero, $zero, $zero       # 0000001a / 000000 ..... ..... ..... ..... 011010
divu $zero, $zero, $zero      # 0000001b / 000000 ..... ..... ..... ..... 011011
madd $zero, $zero             # 0000001c / 000000 ..... ..... ..... ..... 011100
maddu $zero, $zero            # 0000001d / 000000 ..... ..... ..... ..... 011101
add $zero, $zero, $zero       # 00000020 / 000000 ..... ..... ..... ..... 100000
addu $zero, $zero, $zero      # 00000021 / 000000 ..... ..... ..... ..... 100001
sub $zero, $v1, $zero         # 00000022 / 000000 ..... ..... ..... ..... 100010
subu $zero, $v1, $zero        # 00000023 / 000000 ..... ..... ..... ..... 100011
and $zero, $zero, $zero       # 00000024 / 000000 ..... ..... ..... ..... 100100
# move $zero, $zero           # 00000025 / 000000 ..... ..... ..... ..... 100101
or $zero, $zero, $zero        # 00000025 / 000000 ..... ..... ..... ..... 100101
xor $zero, $zero, $zero       # 00000026 / 000000 ..... ..... ..... ..... 100110
nor $zero, $zero, $zero       # 00000027 / 000000 ..... ..... ..... ..... 100111
slt $zero, $zero, $zero       # 0000002a / 000000 ..... ..... ..... ..... 101010
sltu $zero, $zero, $zero      # 0000002b / 000000 ..... ..... ..... ..... 101011
max $zero, $zero, $zero       # 0000002c / 000000 ..... ..... ..... ..... 101100
min $zero, $zero, $zero       # 0000002d / 000000 ..... ..... ..... ..... 101101
msub $zero, $zero             # 0000002e / 000000 ..... ..... ..... ..... 101110
msubu $zero, $zero            # 0000002f / 000000 ..... ..... ..... ..... 101111
tge $zero, $zero              # 00000030 / 000000 ..... ..... ..... ..... 110000
tgeu $zero, $zero             # 00000031 / 000000 ..... ..... ..... ..... 110001
tlt $zero, $zero              # 00000032 / 000000 ..... ..... ..... ..... 110010
tltu $zero, $zero             # 00000033 / 000000 ..... ..... ..... ..... 110011
teq $zero, $zero              # 00000034 / 000000 ..... ..... ..... ..... 110100
tne $zero, $zero              # 00000036 / 000000 ..... ..... ..... ..... 110110

### srl/rotr
##                        min # 00000002 / 000000 00000 ..... ..... ..... 000010
##                        max # 00200002 / 000000 00001 ..... ..... ..... 000010
##                       mask # ffe0003f / 111111 11111 00000 00000 00000 111111
srl $zero, $zero, 0           # 00000002 / 000000 00000 ..... ..... ..... 000010
rotr $zero, $zero, 0          # 00200002 / 000000 00001 ..... ..... ..... 000010

### srlv/rotrv
##                        min # 00000006 / 000000 ..... ..... ..... ....0 000110
##                        max # 00000046 / 000000 ..... ..... ..... ....1 000110
##                       mask # fc00007f / 111111 00000 00000 00000 00001 111111
srlv $zero, $zero, $zero      # 00000006 / 000000 ..... ..... ..... ....0 000110
rotrv $zero, $zero, $zero     # 00000046 / 000000 ..... ..... ..... ....1 000110

### Register & Immediate
##                        min # 04000000 / 000001 ..... 00000 ................
##                        max # 041f0000 / 000001 ..... 11111 ................
##                       mask # fc1f0000 / 111111 00000 11111 0000000000000000
bltz $zero, 0                 # 04000000 / 000001 ..... 00000 ................
bgez $zero, 0                 # 04010000 / 000001 ..... 00001 ................
bltzl $zero, 0                # 04020000 / 000001 ..... 00010 ................
bgezl $zero, 0                # 04030000 / 000001 ..... 00011 ................
tgei $zero, 0                 # 04080000 / 000001 ..... 01000 ................
tgeiu $zero, 0                # 04090000 / 000001 ..... 01001 ................
tlti $zero, 0                 # 040a0000 / 000001 ..... 01010 ................
tltiu $zero, 0                # 040b0000 / 000001 ..... 01011 ................
teqi $zero, 0                 # 040c0000 / 000001 ..... 01100 ................
tnei $zero, 0                 # 040e0000 / 000001 ..... 01110 ................
bltzal $zero, 0               # 04100000 / 000001 ..... 10000 ................
bgezal $zero, 0               # 04110000 / 000001 ..... 10001 ................
bltzall $zero, 0              # 04120000 / 000001 ..... 10010 ................
bgezall $zero, 0              # 04130000 / 000001 ..... 10011 ................
# synci                       # 041f0000 / 000001 ..... 11111 ................
.byte 0x00
.byte 0x00
.byte 0x1f
.byte 0x04

### Immediate                 
##                        min # 00000000 / 000000 ..... ..... ................
##                        max # fc000000 / 111111 ..... ..... ................
##                       mask # fc000000 / 111111 00000 00000 0000000000000000
#-> Special                   # 00000000 - 0000003f
#-> Register & Immediate      # 04000000 - 041f0000 
j 0                           # 08000000 / 000010 ..... ..... ................
jal 0                         # 0c000000 / 000011 ..... ..... ................
beq $zero, $zero, start       # 10000000 / 000100 ..... ..... ................
bne $zero, $zero, start       # 14000000 / 000101 ..... ..... ................
blez $zero, 0                 # 18000000 / 000110 ..... ..... ................
bgtz $zero, 0                 # 1c000000 / 000111 ..... ..... ................
addi $zero, $zero, 0          # 20000000 / 001000 ..... ..... ................
addiu $zero, $zero, 0         # 24000000 / 001001 ..... ..... ................
slti $zero, $zero, 0          # 28000000 / 001010 ..... ..... ................
sltiu $zero, $zero, 0         # 2c000000 / 001011 ..... ..... ................
andi $zero, 0                 # 30000000 / 001100 ..... ..... ................
ori $zero, $zero, 0           # 34000000 / 001101 ..... ..... ................
xori $zero, $zero, 0          # 38000000 / 001110 ..... ..... ................
lui $zero, 0                  # 3c000000 / 001111 ..... ..... ................
#-> Cop0                      # 40000000 - 43e00000
#-> Cop1                      # 44000000 - 47e00000
#-> Cop2                      # 48000000 - 4be00000
beql $zero, $zero, start      # 50000000 / 010100 ..... ..... ................
bnel $zero, $zero, start      # 54000000 / 010101 ..... ..... ................
blezl $zero, 0                # 58000000 / 010110 ..... ..... ................
bgtzl $zero, 0                # 5c000000 / 010111 ..... ..... ................
#-> VFPU0                     # 60000000 - 63800000
#-> VFPU1                     # 64000000 - 67800000
#-> VFPU3                     # 6c000000 - 6f800000
#-> Special2                  # 70000000 - 7000003f
#-> Special3                  # 7c000000 - 7c00003f
lb $zero, 0                   # 80000000 / 100000 ..... ..... ................
lh $zero, 0                   # 84000000 / 100001 ..... ..... ................
lwl $zero, 0                  # 88000000 / 100010 ..... ..... ................
lw $zero, 0                   # 8c000000 / 100011 ..... ..... ................
lbu $zero, 0                  # 90000000 / 100100 ..... ..... ................
lhu $zero, 0                  # 94000000 / 100101 ..... ..... ................
lwr $zero, 0                  # 98000000 / 100110 ..... ..... ................
sb $zero, 0                   # a0000000 / 101000 ..... ..... ................
sh $zero, 0                   # a4000000 / 101001 ..... ..... ................
swl $zero, 0                  # a8000000 / 101010 ..... ..... ................
sw $zero, 0                   # ac000000 / 101011 ..... ..... ................
swr $zero, 0                  # b8000000 / 101110 ..... ..... ................
cache 0, 0                    # bc000000 / 101111 ..... ..... ................
ll $zero, 0                   # c0000000 / 110000 ..... ..... ................
lwc1 $f0, 0                   # c4000000 / 110001 ..... ..... ................
lv.s S000.s, 0                # c8000000 / 110010 ..... ..... ................
#-> VFPU4Jump                 # d0000000 - d3e00000
# lv C000, 0                  # d4000000 / 110101 ..... ..... ................
.byte 0x00
.byte 0x00
.byte 0x00
.byte 0xd4
lv.q C000.q, 0                # d8000000 / 110110 ..... ..... ................
#-> VFPU5                     # dc000000 - df800000
sc $zero, 0                   # e0000000 / 111000 ..... ..... ................
swc1 $f0, 0                   # e4000000 / 111001 ..... ..... ................
sv.s S000.s, 0                # e8000000 / 111010 ..... ..... ................
svl.q C000.q, 0               # f4000000 / 111101 ..... ..... ................
# sv S000.s, 0                # f4000000 / 111101 ..... ..... ................
#-> VFPU6                     # f0000000 - f3e00000
sv.q C000.q, 0                # f8000000 / 111110 ..... ..... ................

### Cop0                 
##                        min # 40000000 / 010000 00000 ..... ................
##                        max # 43e00000 / 010000 11111 ..... ................
##                       mask # ffe00000 / 111111 11111 00000 0000000000000000
mfc0 $zero, $0                # 40000000 / 010000 00000 ..... ................
mtc0 $zero, $0                # 40800000 / 010000 00100 ..... ................
# rdpgpr                      # 41600000 / 010000 01011 ..... ................
.byte 0x00
.byte 0x00
.byte 0x60
.byte 0x41
# mfmc0 $zero, $0             # 41800000 / 010000 01100 ..... ................
.byte 0x00
.byte 0x00
.byte 0x80
.byte 0x41
# wrpgpr                      # 41c00000 / 010000 01110 ..... ................
.byte 0x00
.byte 0x00
.byte 0xc0
.byte 0x41
#-> Cop0CO                    # 42000000 - 4200003f

### Cop0CO
##                        min # 42000000 / 010000 1.... ..... ..... ..... 000000
##                        max # 4200003f / 010000 1.... ..... ..... ..... 111111
##                       mask # fe00003f / 111111 10000 00000 00000 00000 111111
tlbr                          # 42000001 / 010000 1.... ..... ..... ..... 000001
tlbwi                         # 42000002 / 010000 1.... ..... ..... ..... 000010
tlbwr                         # 42000006 / 010000 1.... ..... ..... ..... 000110
tlbp                          # 42000008 / 010000 1.... ..... ..... ..... 001000
eret                          # 42000018 / 010000 1.... ..... ..... ..... 011000
# iack                        # 42000019 / 010000 1.... ..... ..... ..... 011001
.byte 0x19
.byte 0x00
.byte 0x00
.byte 0x42
# deret                       # 4200001f / 010000 1.... ..... ..... ..... 011111
.byte 0x1f
.byte 0x00
.byte 0x00
.byte 0x42
# wait                        # 42000020 / 010000 1.... ..... ..... ..... 100000
.byte 0x20
.byte 0x00
.byte 0x00
.byte 0x42

### Cop1
##                        min # 44000000 / 010001 00000 ..... ..... ...........
##                        max # 47e00000 / 010001 11111 ..... ..... ...........
##                       mask # ffe00000 / 111111 11111 00000 00000 00000000000
mfc1 $zero, $0                # 44000000 / 010001 00000 ..... ..... ...........
cfc1 $zero, $0                # 44400000 / 010001 00010 ..... ..... ...........
mtc1 $zero, $0                # 44800000 / 010001 00100 ..... ..... ...........
ctc1 $zero, $0                # 44c00000 / 010001 00110 ..... ..... ...........
#-> Cop1BC                    # 45000000 - 451f0000
#-> Cop1S                     # 46000000 - 4600003f
#-> Cop1W                     # 46800000 - 4680003f

### Cop1BC
##                        min # 45000000 / 010001 01000 ...00 ................
##                        max # 45030000 / 010001 01000 ...11 ................
##                       mask # ffe30000 / 111111 11111 00011 0000000000000000
bc1f start                    # 45000000 / 010001 01000 00000 ................
bc1t start                    # 45010000 / 010001 01000 00001 ................
bc1fl start                   # 45020000 / 010001 01000 00010 ................
bc1tl start                   # 45030000 / 010001 01000 00011 ................

### Cop1S
##                        min # 46000000 / 010001 10000 ..... ..... ..... 000000
##                        max # 4600003f / 010001 10000 ..... ..... ..... 111111
##                       mask # ffe0003f / 111111 11111 00000 00000 00000 111111
add.s $f0, $f0, $f0           # 46000000 / 010001 10000 ..... ..... ..... 000000
sub.s $f0, $f0, $f0           # 46000001 / 010001 10000 ..... ..... ..... 000001
mul.s $f0, $f0, $f0           # 46000002 / 010001 10000 ..... ..... ..... 000010
div.s $f0, $f0, $f0           # 46000003 / 010001 10000 ..... ..... ..... 000011
sqrt.s $f0, $f0               # 46000004 / 010001 10000 ..... ..... ..... 000100
abs.s $f0, $f0                # 46000005 / 010001 10000 ..... ..... ..... 000101
mov.s $f0, $f0                # 46000006 / 010001 10000 ..... ..... ..... 000110
neg.s $f0, $f0                # 46000007 / 010001 10000 ..... ..... ..... 000111
round.w.s $f0, $f0            # 4600000c / 010001 10000 ..... ..... ..... 001100
trunc.w.s $f0, $f0            # 4600000d / 010001 10000 ..... ..... ..... 001101
ceil.w.s $f0, $f0             # 4600000e / 010001 10000 ..... ..... ..... 001110
floor.w.s $f0, $f0            # 4600000f / 010001 10000 ..... ..... ..... 001111
cvt.w.s $f0, $f0              # 46000024 / 010001 10000 ..... ..... ..... 100100
# dis.int                     # 46000026 / 010001 10000 ..... ..... ..... 100110
.byte 0x26
.byte 0x00
.byte 0x00
.byte 0x46
c.f.s $f0, $f0                # 46000030 / 010001 10000 ..... ..... ..... 110000
c.un.s $f0, $f0               # 46000031 / 010001 10000 ..... ..... ..... 110001
c.eq.s $f0, $f0               # 46000032 / 010001 10000 ..... ..... ..... 110010
c.ueq.s $f0, $f0              # 46000033 / 010001 10000 ..... ..... ..... 110011
c.olt.s $f0, $f0              # 46000034 / 010001 10000 ..... ..... ..... 110100
c.ole.s $f0, $f0              # 46000036 / 010001 10000 ..... ..... ..... 110110
c.ule.s $f0, $f0              # 46000037 / 010001 10000 ..... ..... ..... 110111
c.sf.s $f0, $f0               # 46000038 / 010001 10000 ..... ..... ..... 111000
c.ngle.s $f0, $f0             # 46000039 / 010001 10000 ..... ..... ..... 111001
c.seq.s $f0, $f0              # 4600003a / 010001 10000 ..... ..... ..... 111010
c.lt.s $f0, $f0               # 4600003c / 010001 10000 ..... ..... ..... 111100
c.nge.s $f0, $f0              # 4600003d / 010001 10000 ..... ..... ..... 111101
c.le.s $f0, $f0               # 4600003e / 010001 10000 ..... ..... ..... 111110
c.ngt.s $f0, $f0              # 4600003f / 010001 10000 ..... ..... ..... 111111

### Cop1W
##                        min # 46800000 / 010001 10100 ..... ..... ..... 000000
##                        max # 4680003f / 010001 10100 ..... ..... ..... 111111
##                       mask # ffe0003f / 111111 11111 00000 00000 00000 111111
cvt.s.w $f0, $f0              # 46800020 / 010001 10100 ..... ..... ..... 100000

### Cop2
##                        min # 48000000 / 010010 00000 ..... ................
##                        max # 4be00000 / 010010 11111 ..... ................
##                       mask # ffe00000 / 111111 11111 00000 0000000000000000
mfc2  $zero, $0               # 48000000 / 010010 00000 ..... ................
cfc2 $zero, $0                # 48400000 / 010010 00010 ..... ................
mfv $zero, S000.s             # 48600000 / 010010 00011 ..... ................
mtc2 $zero, $0                # 48800000 / 010010 00100 ..... ................
ctc2 $zero, $0                # 48c00000 / 010010 00110 ..... ................
mtv $zero, S000.s             # 48e00000 / 010010 00111 ..... ................
#-> Cop2BC2                   # 49000000 - 49030000

### Cop2BC2
##                        min # 49000000 / 010010 01000 ...00 ................
##                        max # 49030000 / 010010 01000 ...11 ................
##                       mask # ffe30000 / 111111 11111 00011 0000000000000000
bvf 0, 0                      # 49000000 / 010010 01000 ...00 ................
bvt 0, 0                      # 49010000 / 010010 01000 ...01 ................
bvfl 0, 0                     # 49020000 / 010010 01000 ...10 ................
bvtl 0, 0                     # 49030000 / 010010 01000 ...11 ................

### VFPU0
##                        min # 60000000 / 011000 000 ....... . ....... . .......
##                        max # 63800000 / 011000 111 ....... . ....... . .......
##                       mask # ff800000 / 111111 111 0000000 0 0000000 0 0000000
vadd.s S000.s, S000.s, S000.s # 60000000 / 011000 000 ....... . ....... . .......
vsub.s S000.s, S000.s, S000.s # 60800000 / 011000 001 ....... . ....... . .......
vsbn.s S000, S000, S000       # 61000000 / 011000 010 ....... . ....... . .......
vdiv.s S000.s, S000.s, S000.s # 63800000 / 011000 111 ....... . ....... . .......

### VFPU1
##                        min # 64000000 / 011001 000 ....... . ....... . .......
##                        max # 67800000 / 011001 111 ....... . ....... . .......
##                       mask # ff800000 / 111111 111 0000000 0 0000000 0 0000000
vmul.s S000, S000, S000       # 64000000 / 011001 000 ....... . ....... . .......
vdot.q S000.s, C000.q, C000.q # 64800000 / 011001 001 ....... . ....... . .......
vscl.q C000, C000, S000       # 65000000 / 011001 010 ....... . ....... . .......
vhdp.q S000.s, C000.q, C000.q # 66000000 / 011001 100 ....... . ....... . .......
vcrs.t C000.t, C000.t, C000.t # 66800000 / 011001 101 ....... . ....... . .......
vdet.p S000, C000, C000       # 67000000 / 011001 110 ....... . ....... . .......

### VFPU3
##                        min # 6c000000 / 011011 000 ....... . ....... . .......
##                        max # 6f800000 / 011011 111 ....... . ....... . .......
##                       mask # ff800000 / 111111 111 0000000 0 0000000 0 0000000
vcmp.s FL, S000.s, S000.s     # 6c000000 / 011011 000 ....... . ....... . .......
vmin.s S000, S000, S000       # 6d000000 / 011011 010 ....... . ....... . .......
vmax.s S000, S000, S000       # 6d800000 / 011011 011 ....... . ....... . .......
vscmp.s S000, S000, S000      # 6e800000 / 011011 101 ....... . ....... . .......
vsge.s S000, S000, S000       # 6f000000 / 011011 110 ....... . ....... . .......
vslt.s S000, S000, S000       # 6f800000 / 011011 111 ....... . ....... . .......

### Special2
##                        min # 70000000 / 011100 ..... ..... ..... ..... 000000
##                        max # 7000003f / 011100 ..... ..... ..... ..... 111111
##                       mask # fc00003f / 111111 00000 00000 00000 00000 111111
# halt                        # 70000000 / 011100 ..... ..... ..... ..... 000000
.byte 0x00
.byte 0x00
.byte 0x00
.byte 0x70
mfic $zero, $0                # 70000024 / 011100 ..... ..... ..... ..... 100100
mtic $zero, $0                # 70000026 / 011100 ..... ..... ..... ..... 100110

### Special3
##                        min # 7c000000 / 011111 ..... ..... ..... ..... 000000
##                        max # 7c00003f / 011111 ..... ..... ..... ..... 111111
##                       mask # fc00003f / 111111 00000 00000 00000 00000 111111
ext $zero,$zero,0,1           # 7c000000 / 011111 ..... ..... ..... ..... 000000
ins $zero,$zero,0,1           # 7c000004 / 011111 ..... ..... ..... ..... 000100
#-> Allegrex0                 # 7c000020 - 7c0007e0
# rdhwr                       # 7c00003b / 011111 ..... ..... ..... ..... 111011
.byte 0x3b
.byte 0x00
.byte 0x00
.byte 0x7c

### Allegrex0
##                        min # 7c000020 / 011111 ..... ..... ..... 00000 100000
##                        max # 7c0007e0 / 011111 ..... ..... ..... 11111 100000
##                       mask # fc0007ff / 111111 00000 00000 00000 11111 111111
wsbh $zero, $zero             # 7c0000a0 / 011111 ..... ..... ..... 00010 100000
wsbw $zero, $zero             # 7c0000e0 / 011111 ..... ..... ..... 00011 100000
seb $zero, $zero              # 7c000420 / 011111 ..... ..... ..... 10000 100000
bitrev $zero, $zero           # 7c000520 / 011111 ..... ..... ..... 10100 100000
seh $zero, $zero              # 7c000620 / 011111 ..... ..... ..... 11000 100000

### VFPU4
##                        min # d0000000 / 110100 00000 00000 . ....... . .......
##                        max # d01f0000 / 110100 00000 11111 . ....... . .......
##                       mask # ffff0000 / 111111 11111 11111 0 0000000 0 0000000
vmov.s S000, S000             # d0000000 / 110100 00000 00000 . ....... . .......
vabs.s S000.s, S000.s         # d0010000 / 110100 00000 00001 . ....... . ....... 
vneg.s S000, S000             # d0020000 / 110100 00000 00010 . ....... . .......
vidt.q C000                   # d0030000 / 110100 00000 00011 . ....... . .......
vsat0.s S000, S000            # d0040000 / 110100 00000 00100 . ....... . .......
vsat1.s S000, S000            # d0050000 / 110100 00000 00101 . ....... . .......
vzero.s S000                  # d0060000 / 110100 00000 00110 . ....... . .......
vone.s S000                   # d0070000 / 110100 00000 00111 . ....... . .......
vrcp.s S000, S000             # d0100000 / 110100 00000 10000 . ....... . .......
vrsq.s S000, S000             # d0110000 / 110100 00000 10001 . ....... . .......
vsin.s S000.s, S000.s         # d0120000 / 110100 00000 10010 . ....... . ....... 
vcos.s S000.s, S000.s         # d0130000 / 110100 00000 10011 . ....... . ....... 
vexp2.s S000.s, S000.s        # d0140000 / 110100 00000 10100 . ....... . ....... 
vlog2.s S000, S000            # d0150000 / 110100 00000 10101 . ....... . ....... 
vsqrt.s S000.s, S000.s        # d0160000 / 110100 00000 10110 . ....... . ....... 
vasin.s S000.s, S000.s        # d0170000 / 110100 00000 10111 . ....... . ....... 
vnrcp.s S000, S000            # d0180000 / 110100 00000 11000 . ....... . .......
vnsin.s S000, S000            # d01a0000 / 110100 00000 11010 . ....... . .......
vrexp2.s S000, S000           # d01c0000 / 110100 00000 11100 . ....... . .......

### VFPU7
##                        min # d0200000 / 110100 00001 00000 . ....... . .......
##                        max # d03f0000 / 110100 00001 11111 . ....... . .......
##                       mask # ffff0000 / 111111 11111 11111 0 0000000 0 0000000
vrnds.s S000                  # d0200000 / 110100 00001 00000 . ....... . .......
vrndi.s S000                  # d0210000 / 110100 00001 00001 . ....... . .......
vrndf1.s S000                 # d0220000 / 110100 00001 00010 . ....... . .......
vrndf2.s S000                 # d0230000 / 110100 00001 00011 . ....... . .......
vf2h.q C000, C000             # d0320000 / 110100 00001 10010 . ....... . .......
vh2f.s C000, S000             # d0330000 / 110100 00001 10011 . ....... . .......
vsbz.s S000, S000             # d0360000 / 110100 00001 10110 . ....... . .......
vlgb.s S000, S000             # d0370000 / 110100 00001 10111 . ....... . .......
# vuc2i.s C000, S000          # d0380000 / 110100 00001 11000 . ....... . .......
.byte 0x00
.byte 0x00
.byte 0x38
.byte 0xd0
# vc2i.q                      # d0390000 / 110100 00001 11001 . ....... . ....... 
.byte 0x00
.byte 0x00
.byte 0x39
.byte 0xd0
vus2i.s C000, S000            # d03a0000 / 110100 00001 11010 . ....... . .......
vs2i.s C000, S000             # d03b0000 / 110100 00001 11011 . ....... . .......
vi2uc.q S000, C000            # d03c0000 / 110100 00001 11100 . ....... . .......
vi2c.q S000, C000             # d03d0000 / 110100 00001 11101 . ....... . .......
vi2us.q C000, C000            # d03e0000 / 110100 00001 11110 . ....... . .......
vi2s.q C000, C000             # d03f0000 / 110100 00001 11111 . ....... . .......

### VFPU9
##                        min # d0400000 / 110100 00010 00000 . ....... . .......
##                        max # d05f0000 / 110100 00010 11111 . ....... . .......
##                       mask # ffff0000 / 111111 11111 11111 0 0000000 0 0000000
vsrt1.q C000, C000            # d0400000 / 110100 00010 00000 . ....... . .......
vsrt2.q C000, C000            # d0410000 / 110100 00010 00001 . ....... . .......
vbfy1.p C000.p, C000.p        # d0420000 / 110100 00010 00010 . ....... . ....... 
vbfy2.q C000.q, C000.q        # d0430000 / 110100 00010 00011 . ....... . ....... 
vocp.s S000, S000             # d0440000 / 110100 00010 00100 . ....... . ....... 
vsocp.s C000, S000            # d0450000 / 110100 00010 00101 . ....... . ....... 
vfad.p S000.s, C000.p         # d0460000 / 110100 00010 00110 . ....... . ....... 
vavg.p S000.s, C000.p         # d0470000 / 110100 00010 00111 . ....... . ....... 
vsrt3.q C000, C000            # d0480000 / 110100 00010 01000 . ....... . .......
vsrt4.q C000, C000            # d0490000 / 110100 00010 01001 . ....... . .......
vsgn.s S000, S000             # d04a0000 / 110100 00010 01010 . ....... . .......
vmfvc S000.s, $128            # d0500000 / 110100 00010 10000 . ....... . .......
vmtvc $128, S000              # d0510000 / 110100 00010 10001 . ....... . .......
vt4444.q C000, C000           # d0590000 / 110100 00010 11001 . ....... . ....... 
vt5551.q C000, C000           # d05a0000 / 110100 00010 11010 . ....... . ....... 
vt5650.q C000, C000           # d05b0000 / 110100 00010 11011 . ....... . ....... 

### VFPU4Jump
##                        min # d0000000 / 110100 00000 ..... . ....... . .......
##                        max # d3e00000 / 110100 11111 ..... . ....... . .......
##                       mask # ffe00000 / 111111 11111 00000 0 0000000 0 0000000
#-> VFPU4                     # d0000000 - d01f0000
#-> VFPU7                     # d0200000 - d03f0000
#-> VFPU9                     # d0400000 - d05f0000
vcst.s S000.s, VFPU_HUGE      # d0600000 / 110100 00011 ..... . ....... . .......
vf2in.s S000, S000, 0         # d2000000 / 110100 10000 ..... . ....... . .......
vf2iz.s S000, S000, 0         # d2200000 / 110100 10001 ..... . ....... . .......
vf2iu.s S000, S000, 0         # d2400000 / 110100 10010 ..... . ....... . .......
vf2id.s S000, S000, 0         # d2600000 / 110100 10011 ..... . ....... . .......
vi2f.q C000, C000, 0          # d2800000 / 110100 10100 ..... . ....... . .......
vcmov.s S000.s, S000.s, 0     # d2a00000 / 110100 10101 ..... . ....... . .......
#->vwbn                       # d3000000 - d3000000

### vwbn
##                        min # d3000000 / 110100 11 ........ . ....... . .......
##                        max # d3000000 / 110100 11 ........ . ....... . .......
##                       mask # ff000000 / 111111 11 00000000 0 0000000 0 0000000
vwbn.s S000.s, S000.s, 0      # d3000000 / 110100 11 ........ . ....... . .......

### VFPU5
##                        min # dc000000 / 110111 000 ....... ................
##                        max # df800000 / 110111 111 ....... ................
##                       mask # ff800000 / 111111 111 0000000 0000000000000000
vpfxs [x,x,x,x]               # dc000000 / 110111 000 ....... ................
                              # dc800000 / 110111 001 ....... ................
vpfxt [x,x,x,x]               # dd000000 / 110111 010 ....... ................
                              # dd800000 / 110111 011 ....... ................
vpfxd [0:1,0:1,0:1,0:1]       # de000000 / 110111 100 ....... ................
                              # de800000 / 110111 101 ....... ................
viim.s S000, 0                # df000000 / 110111 110 ....... ................
vfim.s S000, 0                # df800000 / 110111 111 ....... ................

### VFPU6
##                        min # f0000000 / 111100 00000 ..... . ....... . .......
##                        max # f3e00000 / 111100 11111 ..... . ....... . .......
##                       mask # ffe00000 / 111111 11111 00000 0 0000000 0 0000000
vmmul.q M000, M100, M100      # f0000000 / 111100 00000 ..... . ....... . .......
                              # f0200000 / 111100 00001 ..... . ....... . .......
                              # f0400000 / 111100 00010 ..... . ....... . .......
                              # f0600000 / 111100 00011 ..... . ....... . .......
vtfm2.p C000, M100, C010      # f0800000 / 111100 00100 ..... . ....... . .......
                              # f0a00000 / 111100 00101 ..... . ....... . .......
                              # f0c00000 / 111100 00110 ..... . ....... . .......
                              # f0e00000 / 111100 00111 ..... . ....... . .......
vtfm3.t C000, M100, C010      # f1000000 / 111100 01000 ..... . ....... . .......
                              # f1200000 / 111100 01001 ..... . ....... . .......
                              # f1400000 / 111100 01010 ..... . ....... . .......
                              # f1600000 / 111100 01011 ..... . ....... . .......
vtfm4.q C000, M100, C010      # f1800000 / 111100 01100 ..... . ....... . .......
                              # f1a00000 / 111100 01101 ..... . ....... . .......
                              # f1c00000 / 111100 01110 ..... . ....... . .......
                              # f1e00000 / 111100 01111 ..... . ....... . .......
vmscl.q M000, M100, S100      # f2000000 / 111100 10000 ..... . ....... . .......
                              # f2200000 / 111100 10001 ..... . ....... . .......
                              # f2400000 / 111100 10010 ..... . ....... . .......
                              # f2600000 / 111100 10011 ..... . ....... . .......
vcrsp.t C000, C000, C000      # f2800000 / 111100 10100 ..... . ....... . .......
#-> VFPUMatrix                # f3800000 - f38f0000
vrot.q C000, S100, [0,0,s,c]  # f3a00000 / 111100 11101 ..... . ....... . .......

### VFPUMatrix
##                        min # f3800000 / 111100 11100 .0000 . ....... . .......
##                        max # f38f0000 / 111100 11100 .1111 . ....... . .......
##                       mask # ffef0000 / 111111 11111 01111 0 0000000 0 0000000
vmmov.p M000, M000            # f3800000 / 111100 11100 .0000 . ....... . .......
vmidt.p M000                  # f3830000 / 111100 11100 .0011 . ....... . .......
vmzero.p M000                 # f3860000 / 111100 11100 .0110 . ....... . .......
vmone.p M000                  # f3870000 / 111100 11100 .0111 . ....... . .......

### VFPUSpecial
##                        min # ffff0000 / 11111111 11111111 .....000 00000000 
##                        max # ffff04ff / 11111111 11111111 .....100 11111111 
##                       mask # ffff07ff / 11111111 11111111 00000111 11111111 
vnop                          # ffff0000 / 11111111 11111111 00000000 00000000 
vsync                         # ffff0320 / 11111111 11111111 00000011 00100000
vflush                        # ffff040d / 11111111 11111111 00000100 00001101 
