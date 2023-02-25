"""storm.py"""
import binascii
import random

SEED_HEAD = 114514


def out(fn, n, k, w):
  w = [str(x) for x in w]
  with open(fn, 'w') as f:
    print(n, k, file=f)
    print(' '.join(w), file=f)


def gen_random(fn, n, mxk, mnw, mxw, sorted=None):
  w = []
  for _ in range(0, n):
    w.append(random.randint(mnw, mxw))
  if sorted == 'smaller':
    w.sort()
  elif sorted == 'greater':
    w.sort(reverse=True)
  k = random.randint(1, mxk)
  out(fn, n, k, w)


def gen_minmax(fn, n, mxk, mnw, mxw, variation):
  if variation == 'max':
    w = [mxw] * n
    k = 1
  elif variation == 'min':
    w = [mnw] * n
    k = mxk
  out(fn, n, k, w)


def gen_subtask(subtask, mxn, mxk, mxw=1000000000):
  for i in range(1, 7):
    fn = '%d_random_%02d.in' % (subtask, i)
    random.seed(SEED_HEAD + binascii.crc32(fn.encode()))
    n = random.randint(1, mxn)
    mxk = min(n * (n + 1) // 2, mxk)
    gen_random(fn, n, mxk, -mxw, mxw)

  for variation in ['smaller', 'greater']:
    fn = '%d_sorted_%s_01.in' % (subtask, variation)
    random.seed(SEED_HEAD + binascii.crc32(fn.encode()))
    n = mxn
    mxk = min(n * (n + 1) // 2, mxk)
    gen_random(fn, n, mxk, -mxw, mxw, sorted=variation)

  for variation in ['min', 'max']:
    fn = '%d_%s_01.in' % (subtask, variation)
    random.seed(SEED_HEAD + binascii.crc32(fn.encode()))
    n = mxn
    mxk = min(n * (n + 1) // 2, mxk)
    gen_minmax(fn, n, mxk, -mxw, mxw, variation)


def main():
  # case 1
  MXN = 20
  MXK = MXN * (MXN + 1) // 2
  gen_subtask(1, MXN, MXK)

  # case 2
  MXN = 10000
  MXK = 200000
  gen_subtask(2, MXN, MXK)

  # case 3
  MXN = 10000
  MXK = MXN * (MXN + 1) // 2
  gen_subtask(3, MXN, MXK)

  # case 4
  MXN = 200000
  MXK = 200000
  gen_subtask(4, MXN, MXK)

  # case 5
  MXN = 200000
  MXK = MXN * (MXN + 1) // 2
  gen_subtask(5, MXN, MXK, mxw=100)

  # case 6
  MXN = 200000
  MXK = MXN * (MXN + 1) // 2
  gen_subtask(6, MXN, MXK)


main()
