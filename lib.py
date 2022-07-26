import numpy as np
formulaPara = [26, 17, 9, 11, 15, 12, 19, 21, 21, 24, 23, 10]
HCPSize = [0, 11, 5]
HCP_name = ['', '$HT$', '$H$']
HCP_ub = [[4 for x in range(f)] for f in HCPSize]
HCP_lb = [[0 for x in range(f)] for f in HCPSize]
suitHCPSize = [0, 4]
suitHCP_name = ['', '$sH$']
suitHCP_ub = [[4 for x in range(f)] for f in suitHCPSize]
suitHCP_lb = [[0 for x in range(f)] for f in suitHCPSize]
distriSize = [0, 28, 6]
distri_name = ['', '$LS$', '$D$']
distri_ub = [[4 for x in range(f)] for f in distriSize]
distri_lb = [[0 for x in range(f)] for f in distriSize]
longSize = [0, 4, 6, 6, 2]
long_name = ['', '$L$', '$L_4$', '$L^*$', '$TL$']
long_ub = [[4 for x in range(f)] for f in longSize]
long_lb = [[0 for x in range(f)] for f in longSize]
shortSize = [0, 4, 6, 6, 3]
short_name = ['', '$S$', '$DS$', '$S^*$', '$NL$']
short_ub = [[4 for x in range(f)] for f in shortSize]
short_lb = [[0 for x in range(f)] for f in shortSize]
Original_HCP = [0, 0, 1, 2, 3]
Original_long = [1, 4]
Original_short = [3, 2, 1, 3, 2, 1]
Original_dis = [3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
called_HCP = ['', '$cH$']
called_HCP_size = [0, 12]
called_short = ['', '$cS$']
cH_ub = [[4 for x in range(f)] for f in called_HCP_size]
cH_lb = [[-4 for x in range(f)] for f in called_HCP_size]
called_short_size = [0, 3]
cS_ub = [[4 for x in range(f)] for f in called_short_size]
cS_lb = [[-4 for x in range(f)] for f in called_short_size]
called_dis = ['', '$cD$']
called_dis_size = [0, 3]
cD_ub = [[4 for x in range(f)] for f in called_dis_size]
cD_lb = [[-4 for x in range(f)] for f in called_dis_size]
called_long = ['', '$cL$']
called_long_size = [0, 2]
cL_ub = [[4 for x in range(f)] for f in called_long_size]
cL_lb = [[0 for x in range(f)] for f in called_long_size]
NT_HCP_name = ['', '$H$']
NT_HCP_size = [0, 5]
NT_HCP_ub = [[4 for x in range(f)] for f in NT_HCP_size]
NT_HCP_lb = [[0 for x in range(f)] for f in NT_HCP_size]
NT_long_name = ['', '$L_{nt}$']
NT_long_size = [0, 2]
NT_long_ub = [[4 for x in range(f)] for f in NT_long_size]
NT_long_lb = [[0 for x in range(f)] for f in NT_long_size]
NT_short_name = ['', '$S_{nt}$']
NT_short_size = [0, 2]
NT_short_ub = [[4 for x in range(f)] for f in NT_short_size]
NT_short_lb = [[0 for x in range(f)] for f in NT_short_size]

def cardtostring(card):
    if card == 1:
        return "A"
    elif card == 13:
        return "K"
    elif card == 12:
        return "Q"
    elif card == 11:
        return "J"
    elif card == 10:
        return "T"
    else:
        return str(card)

def handtostring(player):
    s = ""
    count = 1
    for i in player.hand.getcard():
        for j in i:
            s += cardtostring(j)
        if count < 4:
            s += "."
        count += 1
    return s

def stdoutreadint(process):
    ret = process.stdout.readline()
    try:
        return float(str(ret)[2:-3])
    except:
        return str(ret)
    return float(str(ret)[2:-3])

def listtostdin(l):
    s = str(l[0])
    for i in l[1:]:
        s += " " + str(i)
    s += "\n"
    return s
def shufflelist(l):
    import random
    random.shuffle(l)
def makeDATASET(l, filename, size = 1000):
    shufflelist(l)
    f = open(filename, "w")
    for i in range(min(size, len(l))):
        f.write(l[i] + '\n')
    f.close()
def read(filename):
    l = []
    file = open(filename)
    for line in file.readlines():
        line = line.strip()
        l.append(line)
    file.close()
    return l

def listtostdin2(l):
    s = str(l[0])
    for i in l[1:]:
        s += " " + str(i)
    s += "\n"
    return s

def objf(P, l):
    s = listtostdin2(l)
    P.stdin.write(s.encode())
    P.stdin.flush()
    return stdoutreadint(P)

def get_suit_formula_name(formulaid):
    ret = ""
    _H = int(formulaid) % 10
    if _H > 0:
        if len(ret) > 0:
            ret += " + "
        ret += str(HCP_name[_H])
    _sH = int(formulaid) // 10 % 10
    if _sH > 0:
        if len(ret) > 0:
            ret += " + "
        ret += str(suitHCP_name[_sH])
    _D = int(formulaid) // 100 % 10
    if _D > 0:
        if len(ret) > 0:
            ret += " + "
        ret += str(distri_name[_D])
    _L = int(formulaid) // 1000 % 10
    if _L > 0:
        if len(ret) > 0:
            ret += " + "
        ret += str(long_name[_L])
    _S = int(formulaid) // 10000 % 10
    if _S > 0:
        if len(ret) > 0:
            ret += " + "
        ret += str(short_name[_S])
    _cH = int(formulaid) // 100000 % 10
    if _cH > 0:
        if len(ret) > 0:
            ret += " + "
        ret += str(called_HCP[_cH])
    _cS = int(formulaid) // 1000000 % 10
    if _cS > 0:
        if len(ret) > 0:
            ret += " + "
        ret += str(called_short[_cS])
    _cD = int(formulaid) // 10000000 % 10
    if _cD > 0:
        if len(ret) > 0:
            ret += " + "
        ret += str(called_dis[_cD])
    _cL = int(formulaid) // 100000000 % 10
    if _cL > 0:
        if len(ret) > 0:
            ret += " + "
        ret += str(called_long[_cL])
    return ret

def get_suit_formula_para_size(formulaid):
    f = int(formulaid)
    return HCPSize[f % 10] + suitHCPSize[(f // 10) % 10] + distriSize[(f // 100) % 10] + longSize[(f // 1000) % 10] + shortSize[(f // 10000) % 10] + called_HCP_size[(f // 100000) % 10] + called_short_size[(f // 1000000) % 10] + called_dis_size[(f // 10000000) % 10] + called_long_size[(f // 100000000) % 10]

def get_suit_formula_ub(formulaid):
    f = int(formulaid)
    return HCP_ub[f % 10] + suitHCP_ub[f // 10 % 10] + distri_ub[f // 100 % 10] + long_ub[f // 1000 % 10] + short_ub[f // 10000 % 10] + cH_ub[f // 100000 % 10] + cS_ub[f // 1000000 % 10] + cD_ub[f // 10000000 % 10] + cL_ub[f // 100000000 % 10]

def get_suit_formula_lb(formulaid):
    f = int(formulaid)
    return HCP_lb[f % 10] + suitHCP_lb[f // 10 % 10] + distri_lb[f // 100 % 10] + long_lb[f // 1000 % 10] + short_lb[f // 10000 % 10] + cH_lb[f // 100000 % 10] + cS_lb[f // 1000000 % 10] + cD_lb[f // 10000000 % 10] + cL_lb[f // 100000000 % 10]
def get_NT_formula_name(formulaid):
    f = int(formulaid)
    ret = ""
    if f % 10:
        ret += NT_HCP_name[f % 10]
    if (f // 10) % 10:
        if len(ret) > 0:
            ret += " + "
        ret += NT_long_name[(f // 10) % 10]
    if (f // 100) % 10:
        if len(ret) > 0:
            ret += " + "
        ret += NT_short_name[(f // 100) % 10]
    return ret

def get_NT_formula_para_size(formulaid):
    f = int(formulaid)
    return NT_HCP_size[f % 10] + NT_long_size[(f // 10) % 10] + NT_short_size[(f // 100) % 10]

def get_NT_formula_ub(formulaid):
    f = int(formulaid)
    return NT_HCP_ub[f % 10] + NT_long_ub[f // 10 % 10] + NT_short_ub[f // 100 % 10]

def get_NT_formula_lb(formulaid):
    f = int(formulaid)
    return NT_HCP_lb[f % 10] + NT_long_lb[f // 10 % 10] + NT_short_lb[f // 100 % 10]

def get_suit_called_formula_para_size(formulaid):
    f = int(formulaid)
    return called_HCP_size[f // 100000 % 10] + called_short_size[f // 1000000 % 10] + called_dis_size[f // 10000000 % 10] + called_long_size[f // 100000000 % 10]
def get_suit_called_formula_lb(formulaid):
    f = int(formulaid)
    return cH_lb[f // 100000 % 10] + cS_lb[f // 1000000 % 10] + cD_lb[f // 10000000 % 10] + cL_lb[f // 100000000 % 10]
def get_suit_called_formula_ub(formulaid):
    f = int(formulaid)
    return cH_ub[f // 100000 % 10] + cS_ub[f // 1000000 % 10] + cD_ub[f // 10000000 % 10] + cL_ub[f // 100000000 % 10]
