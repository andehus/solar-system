import matplotlib.pyplot as plt
from math import *
import sys
filename = sys.argv
print("Plotting data from: ",sys.argv[1])
print("Plotting data from: ",sys.argv[2])
tanlist = []
t=[]
l=[]
t2 = []
l2 = []

#L = (2.0*10**30)*0.000003*1.5*10**8*1.5*10**8*2*pi #kg*km^2/yr
#L2 = (0.000003)*1*2*pi
#print("L ",L,"L2",L2)

with open(sys.argv[1]) as f:
    for i,line in enumerate(f):
        line = line.rstrip()
        data = line.split()
        t.append(float(data[0]))
        l.append(float(data[1]))

with open(sys.argv[2]) as f:
    for i,line in enumerate(f):
        line = line.rstrip()
        data = line.split()
        t2.append(float(data[0]))
        l2.append(float(data[1]))
        
fig = plt.figure()
plt.plot(t,l,label='Eulers Forward')
plt.plot(t2,l2,label='Velocity Verlet')

plt.xlabel('Time [yr]')
plt.ylabel('Angular Momentum [M_sun AU^2/yr^2]')
#plt.legend([label],['Velocity Verlet'])
plt.legend(loc=1)
plt.savefig('last_plot.png')
plt.show()
