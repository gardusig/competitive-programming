def main():
	import math
	tests = int(input())
	for test in range(1, tests + 1):
		ans_num = 0
		ans_den = 1
		for i in input().split(' '):
			i = i.split('/')
			num = int(i[0])
			den = int(i[1])
			new_den = ans_den * (den // math.gcd(ans_den, den))
			new_num = (ans_num * (new_den // ans_den)) + (num * (new_den // den))
			ans_den = new_den
			ans_num = new_num
		gcd = math.gcd(ans_num, ans_den)
		ans_num //= gcd
		ans_den //= gcd
		print(str(ans_num) + '/' + str(ans_den))

main()