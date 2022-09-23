import matplotlib.pyplot as plt
import numpy as np


def make_bandwith_plot(x, y):
    plt.plot(x, y, marker='o')
    plt.xlabel("memory size")
    plt.ylabel("bandwith")
    plt.title("avg 10 loops bandwith per memory size")
    plt.savefig("bandwith.png")
    plt.clf()


def make_loop_plot(loops):
    plt.xlabel("loop")
    plt.ylabel("bandwith")
    plt.title("loops at various memory sizes")
    plt.xticks([0, 1, 2, 3, 4])

    for loop_group in loops:
        mem_size = loop_group[0]
        loop_bandwith = loop_group[1:]
        num_of_loops = np.arange(len(loop_bandwith))
        plt.plot(num_of_loops, loop_bandwith, label=f"{mem_size} GB")

    plt.legend()
    plt.savefig('loops.png')
    plt.clf()


def main():
    bandwith_x = np.array([8000, 10000, 12000, 14000])
    bandwith_y = np.array([6000, 5700, 5000, 112])

    make_bandwith_plot(bandwith_x, bandwith_y)

    loop_data = [
        [4000, 2741, 6043, 6245, 6247, 5829],
        [6000, 2223, 6060, 6032, 6071, 5995],
        [8000, 2407, 5161, 5305, 5602, 5202],
        [10000, 1506, 5639, 6078, 6058, 6081],
        [12000, 545, 5529, 5483, 4843, 5853],
        [14000, 336, 56, 69, 71, 69]
    ]

    make_loop_plot(loop_data)


if __name__ == '__main__':
    main()
