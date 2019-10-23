# <template>

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

# </template>

class Solution:
  limit = 212345
  MOD = 1000000000 + 7

  def __init__(self):
    pass

  def build(self):
    self.sum = [0 for i in range(self.limit)]
    self.sum[0] = 1
    current = 1
    for i in range(1, self.limit):
      current = (current * 10) % self.MOD
      self.sum[i] = (self.sum[i - 1] + current) % self.MOD

  def main(self):
    self.build()
    self.s = input()
    print(self.solve())

  def solve(self):
    ans = 0
    for i in range(len(self.s)):
      value = (ord(self.s[i]) - ord('0')) * (i + 1) * self.sum[len(self.s) - i - 1] 
      ans += value
      ans %= self.MOD
    return ans

def main():
  Solution().main()

main()