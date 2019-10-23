# ~ <template>

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

# ~ </template>

class Solution:

  def __init__(self):
    self.dp = [[False for j in range(1123)] for i in range(1123)]

  def main(self):
    q = int(input())
    while q > 0:
      q -= 1
      self.a = input()
      self.b = input()
      for i in range(len(self.a) + 5):
        for j in range(len(self.b) + 5):
          self.dp[i][j] = False
      self.dp[0][0] = True
      for i in range(len(self.a)):
        for j in range(len(self.b) + 1):
          if self.a[i].islower() == True:
            self.dp[i + 1][j] |= self.dp[i][j]
          if j < len(self.b) and self.a[i].upper() == self.b[j]:
            self.dp[i + 1][j + 1] |= self.dp[i][j]
      print('YES' if self.dp[len(self.a)][len(self.b)] == True else 'NO')

def main():
  Solution().main()

main()