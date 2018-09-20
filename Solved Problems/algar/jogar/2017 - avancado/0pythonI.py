def main():
	n = int(input())
	for i in range(1 << n):
		j = n-1
		while j >= 0:
			c = '1' if i & (1 << j) else '0'
			print('%c%c' % (c, ' ' if j > 0 else '\n'), end = '')
			j -= 1

main()