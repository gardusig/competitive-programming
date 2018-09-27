def main():
	tests = int(input())
	for test in range(1, tests + 1):
		s = input().split(' ')
		n = int(s[0])
		k = int(s[1])
		v = []
		s = input().split(' ')
		for i in range(n):
			v.append(int(s[i]))
		v.sort()
		ans = 0
		current_day = 0
		can_eat = k
		for i in v:
			if can_eat == 0:
				current_day += 1
				can_eat = k
			if current_day < i:
				ans += 1
				can_eat -= 1
		print('Case #' + str(test) + ': ' + str(ans))
		
main()