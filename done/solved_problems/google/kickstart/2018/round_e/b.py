def main():
	global current
	tests = int(input())
	for test in range(1, tests + 1):
		s = input().split(' ')
		n = int(s[0])
		m = int(s[1])
		p = int(s[2])
		friends = []
		for i in range(n):
			friends.append(input().strip())
		current = 0
		valid = []
		nxt_node = []
		root = node(valid, nxt_node)
		value = [[0 for i in range(2)] for i in range(p)]
		for i in range(m):
			root.add(0, input(), value, valid, nxt_node)
		for i in friends:
			for j in range(len(i)):
				k = 1 if i[j] == '1' else 0
				value[j][k] += 1
		valid.append(True)
		dp = [[-1 for j in range(current + 5)] for i in range(p + 5)]
		print('Case #' + str(test) + ': ' + str(n * p - solve(0, 0, p, value, valid, nxt_node, dp)))

class node:
	def __init__(self, valid, nxt_node):
		global current
		self.idx = current
		self.nxt = [None for i in range(2)]
		valid.append(True)
		nxt_node.append([-1 for i in range(2)])
		current += 1
	def add(self, i, s, value, valid, nxt_node):
		if i == len(s):
			valid[self.idx] = False
			return
		j = 1 if s[i] == '1' else 0
		if self.nxt[j] == None:
			self.nxt[j] = node(valid, nxt_node)
			nxt_node[self.idx][j] = self.nxt[j].idx
		self.nxt[j].add(i + 1, s, value, valid, nxt_node)

def solve(i, j, p, value, valid, nxt_node, dp):
	if dp[i][j] != -1:
		return dp[i][j]
	if i == p:
		dp[i][j] = 0
		return dp[i][j]
	ans = -1123456789
	global current
	for k in range(2):
		nxt = current if (j == current or nxt_node[j][k] == -1) else nxt_node[j][k]
		if valid[nxt]:
			ans = max(ans, solve(i + 1, nxt, p, value, valid, nxt_node, dp) + value[i][k])
	dp[i][j] = ans
	return dp[i][j]

main()