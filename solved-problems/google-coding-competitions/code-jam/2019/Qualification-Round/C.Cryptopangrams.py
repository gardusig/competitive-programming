import atexit
import io
import sys
import copy
import math

_INPUT_LINES = sys.stdin.read().splitlines()
input = iter(_INPUT_LINES).__next__
_OUTPUT_BUFFER = io.StringIO()
sys.stdout = _OUTPUT_BUFFER

@atexit.register
def write():
  sys.__stdout__.write(_OUTPUT_BUFFER.getvalue())

def decrypt(v):
  temp = copy.deepcopy(v)
  temp.sort()
  convert = {}
  letter = ord('A')
  for i in temp:
    if i not in convert:
      convert[i] = str(chr(letter))
      letter += 1
  ans = ''
  for i in v:
    ans += convert[i]
  return ans

def solve(l, v):
  ans = [0 for i in range(l + 1)]
  for i in range(1, l):
    if v[i] != v[i - 1]:
      idx = i
      ans[i] = math.gcd(v[i], v[i - 1])
      break
  i = idx
  while i > 0:
    i -= 1
    ans[i] = v[i] // ans[i + 1]
  i = idx
  while i < l:
    i += 1
    ans[i] = v[i - 1] // ans[i - 1]
  return decrypt(ans)

def main():
  t = int(input())
  for test in range(1, t + 1):
    _, l = list(map(int, input().split(' ')))
    v = list(map(int, input().split(' ')))
    print('Case #' + str(test) + ': ' + solve(l, v))

main()