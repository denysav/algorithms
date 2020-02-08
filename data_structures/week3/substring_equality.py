#!/usr/bin/env python3

import random
import sys

class Solver:
    def __init__(self, s):
        self.s = s
        self.P1 = 1000000007
        self.P2 = 1000000009
        self.X = random.randint(1, 10**9)
        self.X_MOD_P1 = [1]
        self.X_MOD_P2 = [1]
        self.hm1 = [0]
        self.hm2 = [0]
        for c in s:
            self.hm1.append((self.X * self.hm1[-1] + ord(c)) % self.P1)
            self.hm2.append((self.X * self.hm2[-1] + ord(c)) % self.P2)
        for i in range(0, len(s)):
            self.X_MOD_P1.append((self.X_MOD_P1[-1] * self.X) % self.P1)
            self.X_MOD_P2.append((self.X_MOD_P2[-1] * self.X) % self.P2)

    def ask(self, a, b, l):
        xm1 = self.X_MOD_P1[l]
        xm2 = self.X_MOD_P2[l]

        a_m1 = (self.hm1[a + l] - xm1 * self.hm1[a]) % self.P1
        a_m2 = (self.hm2[a + l] - xm2 * self.hm2[a]) % self.P2
        b_m1 = (self.hm1[b + l] - xm1 * self.hm1[b]) % self.P1
        b_m2 = (self.hm2[b + l] - xm2 * self.hm2[b]) % self.P2

        return a_m1 == b_m1 and a_m2 == b_m2

s = sys.stdin.readline()
q = int(sys.stdin.readline())
solver = Solver(s)
for i in range(q):
    a, b, l = map(int, sys.stdin.readline().split())
    print("Yes" if solver.ask(a, b, l) else "No")
