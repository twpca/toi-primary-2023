"""game_sp.py"""
import binascii
import random

SEED_HEAD = 114514


def out(fn, n, e, w):
  pi = list(range(1, n + 1))
  random.shuffle(pi)
  pi = [0] + pi
  random.shuffle(e)

  with open(fn, 'w') as f:
    print(n, len(e), file=f)
    for x, y in e:
      x = pi[x]
      y = pi[y]
      if x > y:
        x, y = y, x
      print(x, y, file=f)

    w2 = [0] * (n + 1)
    for i in range(1, n + 1):
      w2[pi[i]] = w[i - 1]
    w2 = w2[1:]
    w2 = [str(x) for x in w2]
    print(' '.join(w2), file=f)


def subtask_sp1(n, cycle, t1, mn=int(1), mx=int(1e9)):
  e = []
  w = []
  for i in range(1, cycle):
    e.append((i, i + 1))
  e.append((cycle, 1))
  for i in range(1, cycle + 1):
    w.append(random.randint(mn, mx))

  ps = [1, 2]
  for i in range(cycle + 1, cycle + t1 + 1):
    fa = random.choice(ps)
    e.append((fa, i))
    ps.append(i)
    w.append(random.randint(mx // 2, mx))

  # random points
  for i in range(3, cycle + 1):
    ps.append(i)
  for i in range(cycle + t1 + 1, n + 1):
    fa = random.choice(ps)
    e.append((fa, i))
    ps.append(i)
    w.append(random.randint(mn, mx))

  return e, w


for i in range(1, 3):
  fn = '%d_sp1_%d.in' % (1, i)
  random.seed(SEED_HEAD + binascii.crc32(fn.encode()))
  n = 100
  cycle = 50
  t1 = 50
  e, w = subtask_sp1(n, cycle, t1)
  out(fn, n, e, w)

for i in range(1, 3):
  fn = '%d_sp1_%d.in' % (3, i)
  random.seed(SEED_HEAD + binascii.crc32(fn.encode()))
  n = 100000
  cycle = 30000
  t1 = 30000
  e, w = subtask_sp1(n, cycle, t1)
  out(fn, n, e, w)

for i in range(1, 3):
  fn = '%d_sp1_%d.in' % (4, i)
  random.seed(SEED_HEAD + binascii.crc32(fn.encode()))
  n = 100000
  cycle = 30000
  t1 = 30000
  e, w = subtask_sp1(n, cycle, t1)
  out(fn, n, e, w)
