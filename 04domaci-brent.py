from time import time
import matplotlib.pyplot as plt
import numpy as np

def funkcija(n,beta,teta,d,delta):
   sum = 0.0
   fi = delta + beta*d*np.cos(teta)
   for k in range(n):
       sum+= np.exp(-1j*k*fi)
   return abs(sum)

def brent(p1,p2,n,beta,teta,d):

   x1 = p1 + (p2 - p1) * np.random.rand()
   x2 = p1 + (p2 - p1) * np.random.rand()
   x3 = p1 + (p2 - p1) * np.random.rand()

   #print(x1,x2,x3)


   start_time = time()

   f1 = - funkcija(n, beta, teta, d, x1)
   f2 = - funkcija(n, beta, teta, d, x2)
   f3 = - funkcija(n, beta, teta, d, x3)
   xmax = 999999999
   last = 0

   while abs(xmax-last) > 1e-7:

       last = xmax
       lista = [f1, f2, f3]
       niz = np.array(lista)
       matrica = np.array([[x1 ** 2, x1, 1], [x2 ** 2, x2, 1], [x3 ** 2, x3, 1]])
       transponovana = np.linalg.inv(matrica)
       proizvod = np.dot(transponovana, niz)

       a = proizvod[0]
       b = proizvod[1]

       if (a != 0):
           xmax = -b / (2.0 * a)
           fmax = -funkcija(n, beta, teta, d, xmax)

       tacke = np.array([x1, x2, x3, xmax])

       funkcije = np.array([f1, f2, f3, fmax])

       sortiran_niz = np.argsort(funkcije)

       x1 = tacke[sortiran_niz[0]]
       x2 = tacke[sortiran_niz[1]]
       x3 = tacke[sortiran_niz[2]]

       f1 = funkcije[sortiran_niz[0]]
       f2 = funkcije[sortiran_niz[1]]
       f3 = funkcije[sortiran_niz[2]]

       end_time = time()

       if end_time - start_time > 3:
           return [x1, abs(f1)]


   return [x1, abs(f1)]

n = 6
beta = 20*np.pi
teta = np.pi/3
d = 1/20
delta = np.arange(0,2*np.pi,0.01)
grafik = funkcija(n,beta,teta,d,delta)
plt.figure()
plt.plot(delta,abs(grafik))
plt.xlabel('delta')
plt.ylabel('|Fs(delta)|')
plt.grid()
plt.savefig('grafik.png', bbox_inches='tight')
plt.show()



s = brent(4.1, 5.6, n, beta, teta, d)
print('delta = ', s[0])
print('|Fs(delta)| = ', s[1])
