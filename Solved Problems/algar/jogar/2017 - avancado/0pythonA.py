import math

def main():
	n = int(input())
	ans = 0
	for i in range(1, n + 1):
		ans += math.log10(i)
	print(max(1, math.ceil(ans)))
	
main()