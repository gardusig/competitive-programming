import atexit
import io
import sys

_INPUT_LINES = sys.stdin.read().splitlines()
input = iter(_INPUT_LINES).__next__
_OUTPUT_BUFFER = io.StringIO()
sys.stdout = _OUTPUT_BUFFER

@atexit.register
def write():
  sys.__stdout__.write(_OUTPUT_BUFFER.getvalue())

class node:
  value = 0
  left = None
  right = None

  def __init__(self, lo, hi):
    self.lo = lo
    self.hi = hi

  def insert(self, idx):
    if self.lo == idx and self.hi == idx:
      self.value += 1
      return
    mid = self.lo + ((self.hi - self.lo) // 2)
    if idx <= mid:
      if self.left == None:
        self.left = node(self.lo, mid)
      self.left.insert(idx)
    else:
      if self.right == None:
        self.right = node(mid + 1, self.hi)
      self.right.insert(idx)
    self.value = 0
    if self.left != None:
      self.value += self.left.value
    if self.right != None:
      self.value += self.right.value

  def ask(self, n):
    if self.value < n:
      return -1
    if self.lo == self.hi:
      return self.lo
    if self.left != None:
      if self.left.value >= n:
        return self.left.ask(n)
      n -= self.left.value
    return self.right.ask(n)

def main():
  n, k = list(map(int, input().split(' ' )))
  v = []
  for i in range(n):
    v.append(list(map(int, input().split(' ' ))))
  v.sort()
  ans = 1123456789012345
  for i in range(n):
    kappaloiro = []
    for j in range(i + 1):
      kappaloiro.append((v[j][1], v[j][2]))
    kappaloiro.sort()
    segtree = node(0, 1000000000)
    for j in range(i + 1):
      segtree.insert(kappaloiro[j][1])
      value = segtree.ask(k)
      if value != -1:
        ans = min(ans, v[i][0] + kappaloiro[j][0] + value)
  print(ans)
  return 0

main()