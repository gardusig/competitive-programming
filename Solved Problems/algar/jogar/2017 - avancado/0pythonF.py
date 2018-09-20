def main():
	v = input().split()
	n = int(v[0].strip())
	k = int(v[1].strip())
	s = input().strip()
	k %= n
	for i in range(n - k, n):
		print(s[i], end = '')
	for i in range(0, n - k):
		print(s[i], end = '')
	print()

main()