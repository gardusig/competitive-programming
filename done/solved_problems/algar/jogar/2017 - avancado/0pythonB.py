x, y, r = [], [], []

def valid(i, j):
	return (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]) > (r[i] + r[j]) * (r[i] + r[j])

def main():
	n = int(input())
	for i in range(n):
		v = input().split()
		x.append(int(v[0].strip()))
		y.append(int(v[1].strip()))
		r.append(int(v[2].strip()))
	ans = 0
	for i in range(0, n):
		flag = True
		for j in range(n):
			if i != j:
				flag &= valid(i, j)
		if flag == True:
			ans += 1
	print(ans)

main()