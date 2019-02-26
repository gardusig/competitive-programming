# import atexit
# import io
import sys

# _INPUT_LINES = sys.stdin.read().splitlines()
# input = iter(_INPUT_LINES).__next__
# _OUTPUT_BUFFER = io.StringIO()
# sys.stdout = _OUTPUT_BUFFER

# @atexit.register
# def write():
#   sys.__stdout__.write(_OUTPUT_BUFFER.getvalue())

def ask(n):
  print(n)
  sys.stdout.flush()
  ans = input()
  if ans == 'CORRECT':
    return 0
  if ans == 'TOO_SMALL':
    return 1
  if ans == 'TOO_BIG':
    return 2
  return -1

def main():
  t = int(input())
  while t > 0:
    t -= 1
    a, b = list(map(int, input().split(' ')))
    n = int(input())
    lo = a + 1
    hi = b
    while lo <= hi:
      mid = lo + ((hi - lo) // 2)
      current = ask(mid)
      if current == 0:
        break
      if current == 1:
        lo = mid + 1
      elif current == 2:
        hi = mid - 1
      else:
        return 0
  return 0

main()