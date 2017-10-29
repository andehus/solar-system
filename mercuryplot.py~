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
plt.plot(planet[planet_num["Venusx"]],planet[planet_num["Venusy"]],label='Venus')
plt.plot(planet[planet_num["Earthx"]],planet[planet_num["Earthy"]],label='Earth')
plt.plot(planet[planet_num["Marsx"]],planet[planet_num["Marsy"]],label='Mars')
plt.plot(planet[planet_num["Jupiterx"]],planet[planet_num["Jupitery"]],label='Jupiter')
plt.plot(planet[planet_num["Saturnx"]],planet[planet_num["Saturny"]],label='Saturn')
plt.plot(planet[planet_num["Uranusx"]],planet[planet_num["Uranusy"]],label='Uranus')
plt.plot(planet[planet_num["Neptunex"]],planet[planet_num["Neptuney"]],label='Neptune')
plt.plot(planet[planet_num["Plutox"]],planet[planet_num["Plutoy"]],label='Pluto')


#plt.axis([-1.5,1.5,-1.5,1.5])
#plt.axis([-1.5,1.5,-1.5,1.5])
plt.xlabel('x [AU]')
plt.ylabel('y [AU]')
#plt.legend([label],['Velocity Verlet'])
plt.legend(loc=1)
plt.savefig('last_plot.png')
plt.show()
