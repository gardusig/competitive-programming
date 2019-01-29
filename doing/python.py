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

def node:
  def __init__(self):
    self.nxt = []
  node *nxt

def main():
  l, d, n = list(map(int, input().split(' ')))
  for i in range(d):
    s = input()

  return 0

main()