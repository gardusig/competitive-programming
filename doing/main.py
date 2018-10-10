from math import sqrt
from sys import stdout
MOD = 998244353
limit = 2000000000000000000

def f1(x):
	for i in range(2, 112345678):
		if x % i == 0:
			return (i, x / i)
	return (0, 0)

def f2(x):
	sq = int(sqrt(x))
	for i in range(max(2, sq - 15), sq + 15):
		if i * i == x:
			return (True, i)
	return (False, 0)

def build_3():
	global limit, have3
	have3 = {}
	for i in range(2, 5123456):
		current = i * i * i
		if current > limit:
			break
		have3[current] = i

def build_4():
	global limit, have4
	have4 = {}
	for i in range(2, 512345):
		current = i * i * i * i
		if current > limit:
			break
		have4[current] = i
		
def add(kappa, keepo):
	global ans
	if kappa not in ans:
		ans[kappa] = 0
	ans[kappa] += keepo

def main():
	n = int(input())
	v = []
	global ans
	ans = {}
	build_3()
	build_4()
	global have3, have4, MOD
	for i in range(n):
		x = int(input())
		if x in have4:
			add(have4[x], 4)
			continue
		if x in have3:
			add(have3[x], 3)
			continue
		eoq = f2(x)
		if eoq[0] == True:
			add(eoq[1], 2)
			continue
		eoq = f1(x)
		add(eoq[0], 1)
		add(eoq[1], 1)
	kappaloiro = 1
	for i in ans:
		kappaloiro = (kappaloiro * (ans[i] + 1)) % MOD
	print(kappaloiro)
	stdout.flush()

main()