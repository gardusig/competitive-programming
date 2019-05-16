t = int(input())

while t > 0:
	t-=1
	
	n, inv = input().split()
	n = int(n)
	inv = int(inv)
	
	ent = input().split()
	v = []
	for ve in ent:
		v.append(int(ve))
		
	
	v.sort()

	for i in range(n):
		if v[i] < 0 and inv > 0:
			v[i] = -v[i]
			inv-=1
			
	
		
	v.sort()
	
	inv = inv%2
	for i in range(inv):
		v[0] = -v[0]
	
	print(sum(v))
	
	
	