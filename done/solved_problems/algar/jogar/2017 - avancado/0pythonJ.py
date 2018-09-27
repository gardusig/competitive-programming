default_value = (-1123456789012345678, 0)

class node:
	def __init__(self, lo, hi):
		self.lo = lo
		self.hi = hi
		self.value = default_value
		self.left = None
		self.right = None

	def merge(self, a, b):
		if a[0] == b[0]:
			return (a[0], a[1] + b[1])
		if a[0] > b[0]:
			return a
		return b

	def update(self, idx, new_value):
		if idx < self.lo or idx > self.hi:
			return
		if idx == self.lo and idx == self.hi:
			self.value = (new_value, 1)
			return
		mid = (self.lo + self.hi) >> 1
		if idx <= mid:
			if self.left == None:
				self.left = node(self.lo, mid)
			self.left.update(idx, new_value)
		else:
			if self.right == None:
				self.right = node(mid + 1, self.hi)
			self.right.update(idx, new_value)
		a = self.left.value if self.left != None else default_value
		b = self.right.value if self.right != None else default_value
		self.value = self.merge(a, b)

	def query(self, qlo, qhi):
		if self.lo > qhi or self.hi < qlo:
			return default_value
		if self.lo >= qlo and self.hi <= qhi:
			return self.value
		a = self.left.query(qlo, qhi) if self.left != None else default_value
		b = self.right.query(qlo, qhi) if self.right != None else default_value
		return self.merge(a, b)

def main():
	root = node(0, 1123456789)
	s = input().split()
	n = int(s[0].strip())
	q = int(s[1].strip())
	s = input().split()
	for i in range(n):
		root.update(i, int(s[i]))
	for i in range(q):
		s = input().split()
		x = int(s[0].strip()) - 1
		y = int(s[1].strip()) - 1
		print(root.query(x, y)[1])

main()