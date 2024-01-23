import math
import numpy as np
import scipy.optimize


W_SIZE = 3
BOUNDS = [[5e6, 5e6]]*W_SIZE

x0 = [9.353956971444877e+06, 2.118990698587988e+07, 1.982601765067424e+07, 8.269561714563388e+06]
y0 = [1.241312016061606e+07, 3.927317122951025e+06, 3.567263619968160e+06, 2.272043407954935e+07]
z0 = [2.155077673436540e+07, 1.554291038208530e+07, 1.732690668817735e+07, 1.101881415061893e+07]
t = [6.953977405819632e-02, 6.796520885661889e-02, 6.769215215591819e-02, 7.501668358266193e-02]
ts = [6.953977e-02, 6.796521e-02, 6.769215e-02, 7.501668e-02]
c0 = 299792458


def opt_func(coordinates):
    x = coordinates[0]
    y = coordinates[1]
    z = coordinates[2]
    cost = 0
    for iter in range(4):
        temp = ((x - x0[iter])*(x - x0[iter]) + (y - y0[iter])*(y - y0[iter]) + (z - z0[iter])*(z - z0[iter]) ) / ( (t[iter]*c0)*(t[iter]*c0))
        temp1 = temp - 1
        cost += temp1*temp1

    return math.sqrt(cost)


FIRST_PRECISION = 1e-10
SECOND_PRECISION = 1e-15
min_fun = +float('inf')
min_coef = [0]*W_SIZE

tst = [4.234647881079292e+06, 1.581270102339405e+06, 4.489652902699516e+06]
print(format(opt_func(tst), '.15f'))

while True:
    START_W = np.random.rand(W_SIZE)
    # START_W = np.random.uniform(BOUNDS[0][0], BOUNDS[0][1], W_SIZE)
    end_w = scipy.optimize.minimize(opt_func, x0=START_W, method='nelder-mead', options={'xatol' : FIRST_PRECISION})

    if end_w.fun < min_fun:
        min_fun = end_w.fun
        min_coef = end_w.x
        # print(min_fun)

    if min_fun < FIRST_PRECISION:
        end_w = scipy.optimize.minimize(opt_func, x0=min_coef, method='nelder-mead')
        if end_w.fun < min_fun:
            min_coef = end_w.x
            min_fun = end_w.fun

        print("W: ", end = '')
        for w in min_coef:
            print(format(w, '.15f'), end = ' ')
        print()
        print("Optimizaciona funckija: ", min_fun)
        break


START_W = min_coef
while True:
    end_w = scipy.optimize.minimize(opt_func, x0=START_W, method='nelder-mead', options={'xatol': SECOND_PRECISION})
    if end_w.fun < min_fun:
        min_fun = end_w.fun
        min_coef = end_w.x

    if min_fun < SECOND_PRECISION:
        end_w = scipy.optimize.minimize(opt_func, x0=min_coef, method='nelder-mead')
        if end_w.fun < min_fun:
            min_coef = end_w.x
            min_fun = end_w.fun

        print("W: ", end = '')
        for w in min_coef:
            print(format(w, '.15f'), end = ' ')
        print()
        print("Optimizaciona funckija: ", min_fun)
        break

    START_W = end_w
