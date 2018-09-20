def main():
	n = int(input())
	for i in range(1000):
		if (1 << i) == n:
			print(i)
			exit()
		elif (1 << i) > n:
			break
	print('-1')
	
main()