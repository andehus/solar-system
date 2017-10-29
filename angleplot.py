import matplotlib.pyplot as plt
from math import *
import sys
filename = sys.argv
print("Plotting data from: ",sys.argv[1])
tanlist = []
r=[]
x=[]
y=[]

with open(sys.argv[1]) as f:
    for i,line in enumerate(f):
        line = line.rstrip()
        data = line.split()
        x.append(float(data[0]))
        y.append(float(data[1]))
        r.append(float(data[2]))
for i in range(1,len(r)-1):
    if r[i]>r[i-1] and r[i]<r[i+1]:
        tanlist.append(atan(y[i]/x[i]))
        

fig = plt.figure()
plt.plot(range(len(tanlist)),tanlist)

#plt.axis([-1.5,1.5,-1.5,1.5])
#plt.axis([-1.5,1.5,-1.5,1.5])
plt.xlabel('x')
plt.ylabel('theta')
#plt.legend([label],['Velocity Verlet'])
plt.legend(loc=1)
plt.savefig('last_plot.png')
plt.show()
