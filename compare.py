import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
eplanet = {}
eplanet_num = {}
eorder = []
#with open('vv.txt') as f:
with open('data.txt') as f:
    for i,line in enumerate(f):
        line = line.rstrip()
        data = line.split()
        if i == 0:
            for p,val in enumerate(data):
                eplanet_num[val] = p
                eplanet[p] = [] #"Earthx".list
        else:
            for p,val in enumerate(data):
                eplanet[p].append(float(val))
vplanet = {}
vplanet_num = {}
vorder = []
#with open('vv.txt') as f:
with open('vv.txt') as f:
    for i,line in enumerate(f):
        line = line.rstrip()
        data = line.split()
        if i == 0:
            for p,val in enumerate(data):
                vplanet_num[val] = p
                vplanet[p] = [] #"Earthx".list
        else:
            for p,val in enumerate(data):
                vplanet[p].append(float(val))    


fig = plt.figure()
plt.plot(0,0,'ro')
plt.plot(eplanet[eplanet_num["Earthx"]],eplanet[eplanet_num["Earthy"]])
plt.plot(vplanet[vplanet_num["Earthx"]],vplanet[vplanet_num["Earthy"]])
#plt.axis([-1.5,1.5,-1.5,1.5])
plt.axis([-1.5,1.5,-1.5,1.5])
plt.xlabel('x')
plt.ylabel('y')
plt.show()
