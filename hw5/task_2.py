#!/usr/bin/env python

from argparse import ArgumentParser
from mpi4py import MPI
import numpy as np
import matplotlib.pyplot as plt

# MPI variables 
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
proc_cnt = comm.Get_size()

def setup_parser(parser):
  parser.add_argument("rule", type=int)
  parser.add_argument("steps", type=int)
  parser.add_argument("size", type=int)
  parser.add_argument("--savefig", action="store_true")
  parser.add_argument("--periodic", action="store_true")

def step(x, rule_b, periodic):
    #single step of an elementary cellular automaton
    y = np.vstack((np.roll(x, 1), x, np.roll(x, -1))).astype(np.int8)
    # LCR pattern for numbers between 0 and 7 
    u = np.array([[4], [2], [1]])
    z = np.sum(y * u, axis=0).astype(np.int8)
    res = rule_b[7 - z]
    if not periodic:
        if rank == 0:
            # fix first cell
            res[0] = x[0]
        elif rank == proc_cnt - 1:
            # fix last cell
            res[-1] = x[-1]
    return res

def send_ghost(arr, periodic):
    # send and receive ghost cells
    # leftmost
    if rank == 0:
        comm.send(arr[-1], dest=rank + 1)
        if periodic:
            comm.send(arr[0], dest=proc_cnt - 1)
            arr = np.insert(arr, 0, comm.recv(source=proc_cnt - 1))
        arr = np.append(arr, comm.recv(source=rank + 1))
    # rightmost
    elif rank == proc_cnt - 1:
        if periodic:
            comm.send(arr[-1], dest=0)
            arr = np.append(arr, comm.recv(source=0))
        comm.send(arr[0], dest=rank - 1)
        arr = np.insert(arr, 0, comm.recv(source=rank - 1))
    # middle
    else:
        comm.send(arr[0], dest=rank - 1)
        comm.send(arr[-1], dest=rank + 1)
        arr = np.append(arr, comm.recv(source=rank + 1))
        arr = np.insert(arr, 0, comm.recv(source=rank - 1))
    return arr


def slice_ghost(arr, periodic):
    # leave only significant cells for resulting array
    if periodic:
        # cut from both sides
        arr = arr[1:-1]
    else:
        if rank == 0:
            # cut last ghost cell
            arr = arr[:-1]
        elif rank == proc_cnt - 1:
            # cut first ghost cell
            arr = arr[1:]
        else:
            arr = arr[1:-1]        
    return arr

def run_cellulars(rule, seq_size, steps, periodic, savefig):
  RULE = rule
  SEQ_SIZE = seq_size
  STEPS = steps
  PERIODIC = periodic
  SAVEFIG = savefig

  rule_b = np.array(
    [int(_) for _ in np.binary_repr(RULE, 8)],
    dtype=np.int8
  )
  
  # define size for each array
  k, m = divmod(SEQ_SIZE, proc_cnt)
  start = rank * k + min(rank, m)
  end = (rank + 1) * k + min(rank + 1, m)
  proc_size = end - start

  arr = np.random.randint(2, size=proc_size)

  start_time = MPI.Wtime()
  history = np.zeros((STEPS, proc_size), dtype=np.int8)
  history[0, :] = arr

  for i in range(STEPS - 1):
      arr = send_ghost(arr, PERIODIC)
      arr = step(arr, rule_b, PERIODIC)
      arr = slice_ghost(arr, PERIODIC)
      history[i + 1, :] = arr

  gathered = comm.gather(history, root=0)

  if rank == 0:
      res = np.concatenate([a for a in gathered], axis=1)
      if SAVEFIG:
          print('SAVEFIG')
          plt.figure(figsize=(10, 10))
          plt.axis('off')
          plt.title(f"rule {RULE}")
          plt.imshow(res, cmap=plt.cm.binary);
          plt.savefig(f"rule_{RULE}_seqsize_{SEQ_SIZE}_steps_{STEPS}.png")
      time_spent = MPI.Wtime() - start_time
      print(rank, 'time elapsed:', time_spent)

      with open(f'num_nodes_{proc_cnt}_rule_{RULE}.txt', 'w') as f:
        s = f'rule={RULE}  '
        s += f'seqsize={SEQ_SIZE} '
        s += f'steps={STEPS} '
        s += f'time_spent={time_spent}'
        f.write(s)


  MPI.Finalize()

def main():
  parser = ArgumentParser(
        prog="mpi_game_of_life",
        description="MPI game of life",
    )
  setup_parser(parser)
  arguments = parser.parse_args()
    
  args = parser.parse_args()

  run_cellulars(args.rule, args.steps, args.size, args.periodic, args.savefig)

  # run_cellulars(110, 1000, 1000, True, True)

if __name__ == "__main__":
    main()
