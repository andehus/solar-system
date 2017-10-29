import matplotlib.pyplot as plt
import sys
from mpl_toolkits.mplot3d import Axes3D
filename = sys.argv
print("Plotting data from: ",sys.argv[1])
planet = {}
planet_num = {}
order = []
#with open('vv.txt') as f:
with open(sys.argv[1]) as f:
    for i,line in enumerate(f):
        line = line.rstrip()
        data = line.split()
        if i == 0:
            for p,val in enumerate(data):
                planet_num[val] = p
                planet[p] = [] #"Earthx".list
        else:
            for p,val in enumerate(data):
                planet[p].append(float(val))    

fig = plt.figure()
plt.plot(0,0,'ro',label='COM')
plt.plot(planet[planet_num["Sunx"]],planet[planet_num["Suny"]],label='Sun')
plt.plot(planet[planet_num["Mercuryx"]],planet[planet_num["Mercuryy"]],label='Mercury')

#plt.axis([-1.5,1.5,-1.5,1.5])
#plt.axis([-1.5,1.5,-1.5,1.5])
plt.xlabel('x [AU]')
plt.ylabel('y [AU]')
#plt.legend([label],['Velocity Verlet'])
plt.legend(loc=1)
plt.savefig('last_plot.png')
plt.show()
