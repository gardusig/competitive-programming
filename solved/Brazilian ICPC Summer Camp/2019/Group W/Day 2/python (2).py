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

def main():
  t = int(input())
  mn = 0
  size = 0
  while t > 0:
    t -= 1
    s = input().strip()
    size = max(size, len(s))
    mn = max(mn, int(s))
  kappa = '1'
  for i in range(1, size):
    kappa += '0'
  kappa = max(int(kappa), mn)
  keepo = ''
  for i in range(size):
    keepo += '9'
  print(kappa)
  print(keepo)
  return 0

main()
