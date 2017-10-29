ms = 1.0
me = 0.000001
mj = 0.001
rs = 0.0
re = 1.0
rj = 5.2
com = ms*rs+me*re+mj*rj/(ms+mj+me)
print(com)

vs = 0.0
ve = 2*3.14
vj = 2*5.2/11.86

vs = (me*(re-com)*ve+mj*(rj-com)*vj)/(ms*(rs-com))
print(vs)
