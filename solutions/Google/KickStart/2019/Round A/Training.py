def main():
  t = int(input())
  for test in range(1, t + 1):
    n, p = list(map(int, input().split(' ')))
    v = list(map(int, input().split(' ')))
    v.sort()
    current = 0
    for i in range(p - 1):
      current += (v[p - 1] - v[i])
    ans = current
    for i in range(p, n):
      current -= (v[i - 1] - v[i - p])
      current += (v[i] - v[i - 1]) * (p - 1)
      ans = min(ans, current)
    print('Case #' + str(test) + ': ' + str(ans))

main()