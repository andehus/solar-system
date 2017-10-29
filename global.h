#define dim 3
#define _integration_points 100000
#define _final_time 100
//For testing beta remember to use beta+1
#define _beta 3 
//#define stepsize 10
#define r0 1.0
//exercise a-f
#define calculate_COM 1
#define m_sun 1.0
#define m_earth 0.000003
#define m_jupiter 0.1
#define x_sun 0.0
#define y_sun 0.0
#define z_sun 0.0
#define vx_sun 0.0
#define vy_sun 0.0
#define vz_sun 0.0
#define x_earth 1.0
#define y_earth 0.0
#define z_earth 0.0
#define vx_earth 0.0
#define vy_earth 2*M_PI
#define vz_earth 0.0
#define x_jupiter 5.2
#define y_jupiter 0.0
#define z_jupiter 0.0
#define vx_jupiter 0.0
#define vy_jupiter (2*5.2/11.86)*M_PI
#define vz_jupiter 0.0
/*exercise f REAL DATA */
/* masses */
#define _m_sun  1.0
#define _m_earth  3e-06
#define _m_jupiter  0.0009499999999999999
#define _m_mars  3.2999999999999996e-07
#define _m_venus  2.4500000000000003e-06
#define _m_saturn  0.000275
#define _m_mercury  1.6499999999999998e-07
#define _m_uranus  4.400000000000001e-05
#define _m_neptune  5.15e-05
#define _m_pluto  6.550000000000001e-09

/* sun */
#define _x_sun 2.254914359005566E-03
#define _y_sun 5.696733747366659E-03
#define _z_sun -1.310075429333557E-04
#define _vx_sun -5.167703680121991E-06
#define _vy_sun 5.527723140782790E-06
#define _vz_sun 1.205466911670736E-07
#define _distance_sun 6.128178940855195E-03
//LT= 3.539340981123532E-05 RG= 6.128178940855195E-03 RR= 3.234475591572609E-06
/* mercury */
#define _x_mercury -3.846713465482475E-01
#define _y_mercury -1.579325457908142E-01
#define _z_mercury 2.199490374286210E-02
#define _vx_mercury 5.137900396188225E-03
#define _vy_mercury -2.468707812358977E-02
#define _vz_mercury -2.489408503024493E-03
#define _distance_mercury 4.164114667799956E-01
//LT= 2.404992059808431E-03 RG= 4.164114667799956E-01 RR= 4.485312919946206E-03
/* venus */
#define _x_venus -5.777888437093712E-01
#define _y_venus 4.279546016625797E-01
#define _z_venus 3.913336137322485E-02
#define _vx_venus -1.198878438738676E-02
#define _vy_venus -1.644840060871289E-02
#define _vz_venus 4.659512729800137E-04
#define _distance_venus 7.200809044625172E-01
//LT= 4.158840463841000E-03 RG= 7.200809044625172E-01 RR=-1.304695370881765E-04
/* earth */
#define _x_earth 9.537246338950663E-01
#define _y_earth 3.079876250045664E-01
#define _z_earth -1.456115960710078E-04
#define _vx_earth -5.487608572692462E-03
#define _vy_earth 1.633769725891812E-02
#define _vz_earth -9.114068232004963E-07
#define _distance_earth 1.002221071249736E+00
//LT= 5.788346169155273E-03 RG= 1.002221071249736E+00 RR=-2.014114183107567E-04
/* mars */
#define _x_mars -1.535984267806829E+00
#define _y_mars 6.435831220326336E-01
#define _z_mars 5.098735620662728E-02
#define _vx_mars -4.840830926178535E-03
#define _vy_mars -1.172542956522649E-02
#define _vz_mars -1.270319881572687E-04
#define _distance_mars 1.666147237313766E+00
//LT= 9.622863911978760E-03 RG= 1.666147237313766E+00 RR=-7.041721382210321E-05
/* jupiter */
#define _x_jupiter -4.608361389621023E+00
#define _y_jupiter -2.884972013779792E+00
#define _z_jupiter 1.150413745126802E-01
#define _vx_jupiter 3.915785028427493E-03
#define _vy_jupiter -6.038636342031143E-03
#define _vz_jupiter -6.255316756545723E-05
#define _distance_jupiter 5.438133203176638E+00 
//LT= 3.140803800374286E-02 RG= 5.438133203176638E+00 RR=-1.160787839687350E-04
/* saturn */
#define _x_saturn -3.843449989753845E-01
#define _y_saturn -1.004789019756586E+01
#define _z_saturn 1.899996541096748E-01
#define _vx_saturn 5.268221291411744E-03
#define _vy_saturn -2.305529925966965E-04
#define _vz_saturn -2.059712986670514E-04
#define _distance_saturn 1.005703327871292E+01
//LT= 5.808458006107838E-02 RG= 1.005703327871292E+01 RR= 2.511895555854659E-05
/* uranus */
#define _x_uranus 1.787024415826866E+01 
#define _y_uranus 8.789756094405210E+00 
#define _z_uranus -1.988666240097684E-01
#define _vx_uranus -1.764803086811542E-03 
#define _vy_uranus 3.345969399815219E-03 
#define _vz_uranus 3.541636603343686E-05
//LT= 1.150249230041944E-01 RG= 1.991594804194402E+01 RR=-1.071628755770107E-04 */
/* neptune */
#define _x_neptune 2.860841144186702E+01
#define _y_neptune -8.839449989873037E+00
#define _z_neptune -4.772780134973292E-01
#define _vx_neptune 9.061008901152526E-04
#define _vy_neptune 3.017687597250824E-03
#define _vz_neptune -8.342715831855396E-05
#define _distance_neptune 2.994670058041089E+01
//LT= 1.729577181682180E-01 RG= 2.994670058041089E+01 RR=-2.380140604778157E-05
/* pluto */
#define _x_pluto 1.052876161102794E+01
#define _y_pluto -3.171458190193588E+01
#define _z_pluto 3.481020221139978E-01
#define _vx_pluto 3.036489560762828E-03
#define _vy_pluto 3.282787577594146E-04
#define _vz_pluto -9.075944595230298E-04
//LT= 1.930086891947284E-01 RG= 3.341841859355787E+01 RR= 6.356768691471149E-04
