from collections import OrderedDict

def main():
	v = {}
	n = int(input())
	for i in range(n):
		s = input().split()
		x = int(s[0].strip())
		y = int(s[1].strip())
		a = int(s[2].strip())
		if not x in v:
			v[x] = []
		v[x].append((-a, y))
	v = OrderedDict(sorted(v.items()))
	ans, before = 0, 0
	for i in v:
		v[i].sort()
		for j in v[i]:
			ans += abs(before - j[1])
			before = j[1]
	print(ans)

main()