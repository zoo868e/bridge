import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np
#圖的大小
fig = plt.figure(figsize=(8,5))
ax = fig.add_subplot(1, 1, 1)
#要畫的資料
peftmakespan = [0.943,0.942,0.941,0.941,0.941,0.941,]
pefttimes = [3.074,4.17,4.458,4.746,5.148,5.57]
#畫線
plt.plot(pefttimes,peftmakespan,color='gray',marker='o',markerfacecolor='gray',label='PEFT ranking')
#調整間距
major_ticks_x=np.linspace(3,6,4)
major_ticks_y=np.linspace(0.939,0.943,5)
ax.set_xticks(major_ticks_x)
ax.set_yticks(major_ticks_y)
ax.grid(which="major",alpha=0.6)
plt.xlabel("Time Ratio",fontdict={'size': 10})
plt.ylabel("Makespan Ratio",fontdict={'size': 10})
plt.title("(0.1 , 10 , 3)",fontdict={'size': 20})
plt.legend()
plt.show() #顯示繪製的圖形
ax.set_rasterized(True)
fig.savefig('ccr0.1n=10.eps',dpi=600,format='eps')

