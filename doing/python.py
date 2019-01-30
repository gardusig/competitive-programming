import sys

sys.stdin = open('aztec.in', 'r')
sys.stdout = open('aztec.out', 'w')

def solve(n):
  sum = 1
  i = 1
  while True:
    i += 1
    current = 0
    current += ((i + 1) * i) // 2
    current += (i * (i - 1)) // 2
    if sum + sum + current > n:
      return i - 1
    sum += current

def main():
  n = int(input())
  print(solve(n))
  return 0

main()