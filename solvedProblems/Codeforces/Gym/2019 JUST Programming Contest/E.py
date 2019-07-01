t = int(input())
while t > 0:
	t-=1
	
	n, m = input().split()
	n= int(n)
	m = int(m)
	
	s = input()
	p = input()
	nova = input()
	
	custo = {}
	for i in range(n):
		l = s[i]
		if l not in custo:
			custo[l] = int(p[i])
		else:
			custo[l] = min(custo[l], int(p[i]))
			
	soma = 0
	for i in range(m):
		l = nova[i]
		if l not in custo:
			print("-1")
			break
		else: soma+=custo[l]
	else:	
		print(soma)