def convert(s, p):
	current = 0
	for i in range(p):
		if s[i] == '1':
			current |= (1 << i)
	return current

def main():
	tests = int(input())
	for test in range(1, tests + 1):
		s = input().split(' ')
		n = int(s[0])
		m = int(s[1])
		p = int(s[2])
		friends = []
		for i in range(n):
			friends.append(convert(input(), p))
		v = [True for i in range(1 << p)]
		while m > 0:
			m -= 1
			v[convert(input(), p)] = False
		ans = n * p
		for i in range(1 << p):
			current = 0
			if v[i] == True:
				for j in friends:
					for k in range(p):
						current += (i & (1 << k)) != (j & (1 << k))
				ans = min(ans, current)
		print('Case #' + str(test) + ': ' + str(ans))
		
main()