v = []

def main():
	v = []
	for i in range(2):
		s_input = input().split()
		v.append([])
		for j in range(3):
			v[i].append(int(s_input[j]))
		v[i].sort()
	for i in range(2):
		if v[i][0] > v[i ^ 1][2]:
			print('J' + str(i + 1))
			exit()
	print('E')

main()