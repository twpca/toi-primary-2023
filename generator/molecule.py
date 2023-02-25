"""molecule.py"""
import binascii
import random

SEED_HEAD = 114514
INF = 1000000000
tests = set()


def out(fn, a, b, c):
  tests.add((a, b, c))
  with open(fn, 'w') as f:
    print(a, b, c, file=f)


def gen_abc(min_abc, max_abc, max_sum=INF):
  while True:
    a = random.randint(min_abc, max_abc)
    b = random.randint(min_abc, max_abc)
    c = random.randint(min_abc, max_abc)
    if a + b + c <= max_sum and a + b + c >= 3:
      break
  return a, b, c


def gen_ab(min_abc, max_abc, max_sum=INF):
  while True:
    a = random.randint(min_abc, max_abc)
    b = random.randint(min_abc, max_abc)
    if a + b <= max_sum and a + b >= 3:
      break
  return a, b


def gen_aab(min_abc, max_abc, max_sum=INF):
  while True:
    a = random.randint(min_abc, max_abc)
    b = random.randint(min_abc, max_abc)
    if a + a + b <= max_sum and a + a + b >= 3:
      break
  return a, a, b


def subtask_sp_cases(subtask, min_abc, max_abc, max_sum=INF, skip_min=False):
  random.seed(SEED_HEAD + binascii.crc32(('%d_sp' % subtask).encode()))

  enumerate_range = 4 if subtask == 1 else 3
  # min 3*3*3 or 4*4*4(subtask1)
  if not skip_min:
    for a in range(min_abc, min_abc + enumerate_range):
      for b in range(min_abc, min_abc + enumerate_range):
        for c in range(min_abc, min_abc + enumerate_range):
          if a + b + c >= 3 and a + b + c <= max_sum:
            fn = '%d_min_%d_%d_%d.in' % (subtask, a, b, c)
            out(fn, a, b, c)

  # max 3*3*3 or 4*4*4(subtask1)
  for a in range(max_abc - enumerate_range + 1, max_abc + 1):
    for b in range(max_abc - enumerate_range + 1, max_abc + 1):
      for c in range(max_abc - enumerate_range + 1, max_abc + 1):
        if a + b + c >= 3 and a + b + c <= max_sum:
          fn = '%d_max_%d_%d_%d.in' % (subtask, a, b, c)
          out(fn, a, b, c)

  # (a, a, 0)
  mn = max(2, min_abc)
  mx = min(max_sum // 2, max_abc)
  list_a = random.sample(range(mn, mx + 1), k=4)
  for a in list_a:
    fn = '%d_c0_%d_%d.in' % (subtask, a, a)
    out(fn, a, a, 0)

  # (a, 0, 0) or (0, a, 0)
  for _ in range(0, 4):
    a = random.randint(max(3, min_abc), max_abc)
    dice = random.randint(0, 1)
    if dice == 0:
      fn = '%d_c0_%d_%d_0.in' % (subtask, a, 0)
      out(fn, a, 0, 0)
    else:
      fn = '%d_c0_%d_%d_0.in' % (subtask, 0, a)
      out(fn, 0, a, 0)

  # (a, b, 0)
  for _ in range(0, 4):
    while True:
      a, b = gen_ab(min_abc, max_abc, max_sum=max_sum)
      if a != b:
        break
    fn = '%d_c0_%d_%d_0.in' % (subtask, a, b)
    out(fn, a, b, 0)

  # c%2 == 1
  for _ in range(0, 2):
    while True:
      a, b, c = gen_abc(min_abc, max_abc, max_sum=max_sum)
      if c % 2 == 1:
        break
    fn = '%d_codd_%d_%d_%d.in' % (subtask, a, b, c)
    out(fn, a, b, c)

  # c%4==2, a=b=0
  for _ in range(0, 2):
    c = random.randint(max(1, min_abc // 4), (max_abc - 2) // 4) * 4 + 2
    fn = '%d_cm42_%d_%d_%d.in' % (subtask, 0, 0, c)
    out(fn, 0, 0, c)

  # c%4==0, a=b=0
  for _ in range(0, 2):
    c = random.randint(max(1, min_abc // 4), (max_abc) // 4) * 4
    fn = '%d_cm40_%d_%d_%d.in' % (subtask, 0, 0, c)
    out(fn, 0, 0, c)

  # c%4==2, a=b
  for _ in range(0, 4):
    while True:
      a, b, c = gen_aab(min_abc, max_abc, max_sum=max_sum)
      if c % 4 == 2:
        break
    fn = '%d_cm42_%d_%d_%d.in' % (subtask, a, a, c)
    out(fn, a, a, c)

  # c==2, a==b
  for _ in range(0, 2):
    c = 2
    mn = max(1, min_abc)
    mx = min(max_abc, (max_sum - 2) // 2)
    a = random.randint(mn, mx)
    fn = '%d_c2_%d_%d_%d.in' % (subtask, a, a, c)
    out(fn, a, a, c)

  # c==2, a!=b
  for _ in range(0, 4):
    c = 2
    a, b = gen_ab(min_abc, max_abc, max_sum - 2)
    fn = '%d_c2_%d_%d_%d.in' % (subtask, a, b, c)
    out(fn, a, b, c)


def subtask_rand_cases(subtask, min_abc, max_abc, max_sum=INF, ntests=10):
  random.seed(SEED_HEAD + binascii.crc32(('%d_rand' % subtask).encode()))
  for _ in range(0, ntests):
    while True:
      a, b, c = gen_abc(min_abc, max_abc, max_sum)
      if c % 2 == 0:
        break
    fn = '%d_rand_%d_%d_%d.in' % (subtask, a, b, c)
    out(fn, a, b, c)


def subtask_rand_big_cases(subtask,
                           max_abc1,
                           min_abc2,
                           max_abc2,
                           max_sum=INF,
                           ntests=10):
  random.seed(SEED_HEAD + binascii.crc32(('%d_randbig' % subtask).encode()))
  for _ in range(0, ntests):
    while True:
      small = random.randint(1, max_abc1)
      c = random.randint(1, max_abc1)
      b = random.randint(min_abc2, max_abc2)
      if small + c + b >= 3 and small + c + b <= max_sum and c % 2 == 0:
        break
    dice = random.randint(0, 1)
    if dice == 0:
      fn = '%d_randbig_%d_%d_%d.in' % (subtask, small, b, c)
      out(fn, small, b, c)
    else:
      fn = '%d_randbig_%d_%d_%d.in' % (subtask, b, small, c)
      out(fn, b, small, c)


def subtask3():
  min_abc = 50000
  max_abc = 100000
  subtask = 3
  random.seed(SEED_HEAD + binascii.crc32(('%d_subtask3' % subtask).encode()))

  # b==0 && 2a>=c
  # copy valid tests from other subtasks
  for a, b, c in tests:
    if b == 0 and 2 * a >= c:
      fn = '3_copied_%d_%d_%d.in' % (a, b, c)
      out(fn, a, b, c)

  # (a, 0, 0)
  for _ in range(0, 2):
    a = random.randint(3, 100000)
    fn = '%d_c0_%d_%d_0.in' % (subtask, a, 0)
    out(fn, a, 0, 0)

  # c%2 == 1
  for _ in range(0, 2):
    while True:
      c = random.randint(min_abc, max_abc)
      a = random.randint((c + 1) // 2, max_abc)
      b = 0
      if c % 2 == 1:
        break
    fn = '%d_codd_%d_%d_%d.in' % (subtask, a, b, c)
    out(fn, a, b, c)

  # c==2, a!=b
  for _ in range(0, 4):
    c = 2
    b = 0
    a = random.randint(min_abc, max_abc)
    fn = '%d_c2_%d_%d_%d.in' % (subtask, a, a, c)
    out(fn, a, b, c)

  ntests = 10
  for _ in range(0, ntests):
    while True:
      a, c = gen_ab(min_abc, max_abc)
      b = 0
      if c % 2 == 0:
        break
    fn = '%d_rand_%d_%d_%d.in' % (subtask, a, b, c)
    out(fn, a, b, c)

  for t in range(0, ntests):
    while True:
      c = random.randint(1, 100)
      if t == ntests - 1:
        c = 0
      b = 0
      a = random.randint(min_abc, max_abc)
      if a + b + c >= 3 and c % 2 == 0:
        break

    fn = '%d_randbig_%d_%d_%d.in' % (subtask, a, b, c)
    out(fn, a, b, c)


def main():
  subtask_sp_cases(subtask=1, min_abc=0, max_abc=15, max_sum=15)
  subtask_sp_cases(subtask=2, min_abc=6, max_abc=20, skip_min=True)
  subtask_sp_cases(subtask=4, min_abc=50000, max_abc=100000, skip_min=True)

  subtask_rand_cases(subtask=1, min_abc=0, max_abc=15, max_sum=15, ntests=10)
  subtask_rand_cases(subtask=2, min_abc=6, max_abc=20, ntests=10)
  subtask_rand_cases(subtask=4, min_abc=50000, max_abc=100000, ntests=10)

  subtask_rand_big_cases(subtask=1,
                         max_abc1=3,
                         min_abc2=0,
                         max_abc2=15,
                         max_sum=15,
                         ntests=10)
  subtask_rand_big_cases(subtask=2,
                         max_abc1=5,
                         min_abc2=6,
                         max_abc2=20,
                         ntests=10)
  subtask_rand_big_cases(subtask=4,
                         max_abc1=50,
                         min_abc2=50000,
                         max_abc2=100000,
                         ntests=10)

  subtask3()


main()
