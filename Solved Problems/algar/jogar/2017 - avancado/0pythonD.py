def solve(h, r):
	return 3.141 * r * r * h

def main():
	v = input().split()
	r = int(v[0].strip())
	h1 = int(v[1].strip())
	h2 = int(v[2].strip())
	ans = solve(h2, r) - solve(h1, r)
	print("%.3f\n" % (ans), end = '')

main()