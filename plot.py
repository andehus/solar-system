import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
planet = {}
planet_num = {}
order = []
#with open('vv.txt') as f:
with open('vv.txt') as f:
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

#for l in x:
#    print(l);
#plt.plot(x,y,z)
#plt.axis([0,3000,0,3000,0,3000])
#plt.xlabel('x')
#plt.ylabel('y')
print(planet_num)
print(planet_num.keys())
#print(planet["Suny"])
#ax = fig.add_subplot(111, projection='3d')
##ax.plot(x,y,z)
##plt.show()
#print(planet[4])
fig = plt.figure()
plt.plot(0,0,'ro')
plt.plot(planet[planet_num["Earthx"]],planet[planet_num["Earthy"]])
#plt.axis([-1.5,1.5,-1.5,1.5])
plt.axis([-1.5,1.5,-1.5,1.5])
plt.xlabel('x')
plt.ylabel('y')
plt.show()
