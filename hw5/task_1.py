#!/usr/bin/env python

from mpi4py import MPI
from string import ascii_lowercase
from random import choice, choices

def main():
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    size = comm.Get_size()
    to_visit = list(list(range(1, size)))
    name = str(rank) + '_' + ''.join(choices(ascii_lowercase, k=10))

    if rank == 0:
        visited = [rank]
        new_dest = choice(to_visit)
        msg = name
        comm.ssend((msg, visited), dest=new_dest)
    else:
        msg, visited = comm.recv()
        msg += ' ' + name
        visited.append(rank)
        to_visit = [r for r in to_visit if r not in visited]
        if to_visit:
            new_dest = choice(to_visit)
            comm.ssend((msg, visited), dest=new_dest)
        else:
            print(msg)

    MPI.Finalize()

if __name__ == "__main__":
    main()
