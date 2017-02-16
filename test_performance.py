import os
import sys
import subprocess

KB = 1024
MB = 1024 * 1024
sizes = [
    1,
    1/2,
    1/4,
    1/16,
    1/256,
    1/65536
]

mem_size = 200*MB

filename = "records.dat"
block_size = 10240


f1 = open("performance_disk_sort.txt", "w")

for size in sizes:
    subprocess.run(["/usr/bin/time -v disk_sort", filename, str(mem_size*size), str(block_size)], stdout=f1)
f1.close()


f2 = open("performance_unit_sort"+str(iteration)+".txt", "w")
subprocess.run(["sort -t"," -n -k2 edges.csv > edges_sorted_uid2.csv"], stdout=f2)
f2.close()



