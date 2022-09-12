from typing import List
import heapq


MOD = 1000 * 1000 * 1000 + 7


class Width:
    def __init__(self, start_index: int):
        self.L = start_index
        self.R = start_index

    def join(self, R: int) -> None:
        self.R = max(self.R, R)

    def has_collision(self, L: int, R: int) -> None:
        return L <= self.R and R >= self.L

    def get(self) -> int:
        return (self.R - self.L) * 2


class Height:
    def __init__(self):
        INF = 11234567891234
        self.remove_queue = []
        heapq.heappush(self.remove_queue, (INF, 0))
        self.highest = 0
        self.highest_queue = []
        heapq.heappush(self.highest_queue, -self.highest)
        self.frequency = {0: 1}
        self.total = 0

    def join(self, L: int, R: int, H: int) -> None:
        self.__remove_finished(L)
        heapq.heappush(self.remove_queue, (R, H))
        if H not in self.frequency:
            self.frequency[H] = 0
            heapq.heappush(self.highest_queue, -H)
        self.frequency[H] += 1
        if H > self.highest:
            self.total += H - self.highest
            self.highest = H

    def get(self) -> int:
        return self.total + self.highest

    def __remove_finished(self, start_index: int) -> None:
        while True:
            idx, H = heapq.heappop(self.remove_queue)
            if idx >= start_index:
                heapq.heappush(self.remove_queue, (idx, H))
                break
            self.frequency[H] -= 1
        previous = self.highest
        flag = False
        while self.frequency[self.highest] < 1:
            flag = True
            self.highest = -heapq.heappop(self.highest_queue)
        if flag:
            heapq.heappush(self.highest_queue, -self.highest)
            self.total += previous - self.highest


class Polygon:
    def __init__(self):
        self.perimeter_total = 0

    def solve(self, N: int, W: int, L: List[int], H: List[int]) -> int:
        self.width = Width(L[0])
        self.height = Height()
        ans = 1
        for i in range(N):
            if not self.width.has_collision(L[i], L[i] + W):
                self.perimeter_total += self.get_current_perimeter()
                self.width = Width(L[i])
                self.height = Height()
            self.width.join(L[i] + W)
            self.height.join(L[i], L[i] + W, H[i])
            total = (self.perimeter_total + self.get_current_perimeter()) % MOD
            ans = (ans * total) % MOD
        return ans

    def get_current_perimeter(self) -> None:
        width = self.width.get()
        height = self.height.get()
        return width + height


def run_test(test_id: int) -> None:
    N, K, W = list(map(int, input().split()))
    L = list(map(int, input().split()))
    AL, BL, CL, DL = list(map(int, input().split()))
    for i in range(K, N):
        nxt_l = ((((AL * L[i - 2]) + (BL * L[i - 1]) + CL)) % DL) + 1
        L.append(nxt_l)
    H = list(map(int, input().split()))
    AH, BH, CH, DH = list(map(int, input().split()))
    for i in range(K, N):
        nxt_h = ((((AH * H[i - 2]) + (BH * H[i - 1]) + CH)) % DH) + 1
        H.append(nxt_h)
    polygon = Polygon()
    ans = polygon.solve(N, W, L, H)
    print(f'Case #{test_id}: {ans}')


T = int(input())
for test_id in range(1, T + 1):
    run_test(test_id)
