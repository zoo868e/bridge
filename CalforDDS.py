#!/usr/bin/env python
# coding: utf-8

# In[2]:


import csv
import Gameinfo.Game as Games

import Gameinfo.Calculate as Gamefunc
import numpy as np


# In[5]:




s = []
w = []
n = []
e = []
c = []
r = []
b = []
y = []
board = []
resdds = []
def clr():
    s.clear()
    w.clear()
    n.clear()
    e.clear()
    c.clear()
    r.clear()
    b.clear()
    y.clear()
    resdds.clear()


# In[6]:


file = open("./DDSresult.txt")
rowdata = file.read()
file.close()


# In[7]:


clr()
Gamefunc.loadddsresult(rowdata, s, w, n, e, resdds)
# for i in resdds:
#     print(i)
board.clear()


# In[8]:


for i in range(len(s)):
    board.append(Games.GameS(s[i], w[i], n[i], e[i], dds=resdds[i]))
clr()


# In[9]:


def gen_w(f, dis2):
    weight = []
    default = [0, 0, 0, 0, 0, 0]
    ace = [0, -1, -0.5, 0]
    king = [0, -1, -0.5, 0]
    queen = [0, -1, -0.5, 0]
    jack = [0, -1, -0.5, 0]
    for x in range(1, 11):
        ace.append(f*x)
        king.append((1 - dis2)*f*x)
        queen.append((1 - 2 * dis2)*f*x)
        jack.append((1 - 3 * dis2)*f*x)
        default.append((1 - 4 * dis2)*f*x)
    weight.append(default)
    weight.append(ace)
    for x in range(9):
        weight.append(default)
    weight.append(jack)
    weight.append(queen)
    weight.append(king)
    return weight


# In[10]:


## 驗證是否出現不是最大值
for i in board:
    for j in range(16):
        if i.suitbig[j] > i.biggest[j % 4][0]:
            print("error!!")
            print(i.suitbig[j])
            print("the biggest is", i.biggest[j % 4], "the index is", j, "the larger is found:", i.suitbig[j])


# In[11]:


H = [0,4,0,0,0,0,0,0,0,0,0,1,2,3]
S = [3,2,1,0,0,0,0,0,0,0,0,0,0,0]
L = [0,0,0,0,0,1,2,3,4,5,6,7,8,9]
weight = gen_w(0.5, 0.1)

# In[12]:


NT_neural = [[0, 3.975, 0.342, 0.340, 0.347, 0.341, 0.356, 0.380, 0.358, 0.496, 0.660, 1.047, 1.676, 2.643],[0, 3.971, 0.327, 0.334, 0.314, 0.332, 0.349, 0.331, 0.361, 0.469, 0.663, 1.032, 1.688, 2.643, 3.971], [0, 3.966, 0.329, 0.328, 0.351, 0.341, 0.339, 0.354, 0.375, 0.461, 0.671, 1.056, 1.675, 2.677], [0, 3.989, 0.342, 0.353, 0.345, 0.344, 0.329, 0.356, 0.400, 0.473, 0.684, 1.030, 1.656, 2.655]]
Suit_neural = [[0, 3.982, 1.660, 1.664, 1.669, 1.660, 1.684, 1.680, 1.709, 1.782, 1.921, 2.174, 2.569, 3.207], [0, 3.984, 1.670, 1.667, 1.655, 1.673, 1.685, 1.684, 1.719, 1.791, 1.916, 2.167, 2.569, 3.210, 3.984], [0, 3.973, 1.668, 1.663, 1.669, 1.676, 1.680, 1.687, 1.718, 1.780, 1.918, 2.177, 2.572, 3.220], [0, 3.995, 1.667, 1.660, 1.685, 1.663, 1.688, 1.697, 1.723, 1.783, 1.938, 2.172, 2.565, 3.216]]
neural = [NT_neural, Suit_neural]


# In[14]:


funclist = [Gamefunc.t_HCP,]
funcname = ['HCP']
H = [NT_neural, Suit_neural]

gmax = [0, 0]
fw = [[0, 0], [0, 0]]

for j in range(len(funclist)):
    myscore = []
    score = []
    for i in range(len(board)):
#         print(board[i].dds)
#         print(board[i].suitbig)
        we = Gamefunc.run(funclist[j], board[i].w, board[i].e)##, contract = board[i].biggest[1][1])
        sn = Gamefunc.run(funclist[j], board[i].s, board[i].n)##, contract = board[i].biggest[0][1])
        print(sn, we)

