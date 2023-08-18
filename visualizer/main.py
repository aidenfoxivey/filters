#!/opt/homebrew/bin/python3
# -*- coding: utf-8 -*-

import ctypes
from math import floor
import subprocess
import matplotlib.pyplot as plt
from scipy.stats import chisquare

# written by GPT 3
def plot_bar_chart(data):
    # Create a figure and axis
    fig, ax = plt.subplots()

    # Create a bar chart
    ax.bar(range(len(data)), data)

    # Set the x-axis ticks and labels
    ax.set_xticks(range(len(data)))
    ax.set_xticklabels(range(1, len(data)+1))

    # Set the y-axis label
    ax.set_ylabel('Count')

    # Set the title
    ax.set_title('sdbmhash')

    # Show the plot
    plt.show()

def convert_string_to_cstring(b: bytes) -> tuple[ctypes.c_char_p, ctypes.c_uint]:
	length = ctypes.c_uint(len(b))
	return (ctypes.c_char_p(b), length)

def rand_str(min: int, max: int) -> bytes:
	import random, string

	if min <= 0:
		raise Exception("minimum must be above 0")
	if max >= 256:
		raise Exception("maximum must be below 256")

	k = random.randrange(min, max)

	return ''.join(random.choices(string.ascii_lowercase, k=k)).encode('ascii')

def c_string_gen(min: int, max: int) -> tuple[ctypes.c_char_p, ctypes.c_uint]:
	return convert_string_to_cstring(rand_str(min, max))

def main():
	file_path = "hash.so"
	process = subprocess.Popen(['clang', '--shared', '../src/hash.c', '-o', file_path])

	try: 
		c = ctypes.CDLL(file_path)

		fns = [	c.RSHash, c.JSHash, c.PJWHash, 
				c.ELFHash, c.BKDRHash, c.SDBMHash, 
				c.DJBHash, c.DEKHash, c.APHash ]

		for fn in fns:
			TABLE_SIZE = 1000
			table = [0] * TABLE_SIZE

			# with a loading factor of 0.7
			HASH_RANGE = floor(TABLE_SIZE*0.7)

			for i in range(1, HASH_RANGE+1):
				ptr, length = c_string_gen(2,19)
				location = fn(ptr, length)
				location %= TABLE_SIZE
				table[location] += 1

			print(f"Max collisions for {fn.__name__} is {max(table)}.")
			# https://stats.stackexchange.com/questions/532395/about-the-explanation-of-testing-and-measurement-of-hash-functions-at-wikipedia
			# print(chisquare(table))

			# plot_bar_chart(table)

	except Exception as error:
		print(f"{error}")

if __name__ == "__main__":
	main()