import numpy as np
from matplotlib import pyplot as plt
import tqdm
import numba


def congruent_generator(minval, maxval, initial, multiplier, increment, module):
    x = initial
    while(True):
        yield(x % (maxval-minval) + minval)
        x = (multiplier * x + increment) % module


def graphical_distribution_test(gen, count, filename):
    fig, ax = plt.subplots(1, 1)
    seq = np.array([x for i, x in zip(range(count+1), gen)])
    seq1 = seq[:-1]
    seq2 = seq[1:]
    ax.scatter(seq1, seq2, c=[(1, 0, 0, 0.1)], s=1, marker='.')
    plt.savefig(filename)


params = ((2, 4, 7, 7), (6 ,17, 125, 125), (1664525, 1013904223, 2**15-1, 1000), (48271, 0, 2**31-1, 10000), (253801, 14519, 2**32-1, 10000))


for i, (mult, incr, mod, maxval) in tqdm.tqdm(enumerate(params), total=len(params)):
    initials = (mod // 4 + 1, mod // 2 + 1, 3 * mod // 4 + 1, mod - 1)
    for j, initial in tqdm.tqdm(enumerate(initials), total=len(initials), leave=False):
        gen = congruent_generator(0, maxval, initial, mult, incr, mod)

        graphical_distribution_test(gen, 100000, "set{}_init{}_distr.png".format(i+1, initial))

        fig, ax = plt.subplots(1, 1)

        x = [val for i, val in zip(range(maxval*2), gen)]
        ax.set_xlim(0, maxval)
        ax.hist(x, bins=16)

        etalon_mean = (maxval-1) / 2
        mean = np.mean(x)
        etalon_stdev = (maxval-1) / np.sqrt(12)
        stdev = np.std(x)

        dmean = mean - etalon_mean
        dmean_perc = (dmean / etalon_mean) * 100

        dstdev = stdev - etalon_stdev
        dstdev_perc = (dstdev / etalon_stdev) * 100

        ax.set_title("Δm:{:.3f}({:.2f}%), Δsd:{:.3f}({:.2f}%)".format(dmean, dmean_perc, dstdev, dstdev_perc))
        plt.savefig('set{}_init{}.png'.format(i+1, initial))
        plt.close('all')



fig, ax = plt.subplots(1, 1)

default_rnd = np.random.random(20000)
ax.set_xlim(0, 1)
ax.hist(default_rnd, bins=16)

etalon_mean = 0.5
etalon_stdev = 1.0 / np.sqrt(12)
mean = np.mean(default_rnd)
stdev = np.std(default_rnd)

dmean = mean - etalon_mean
dmean_perc = (dmean / etalon_mean) * 100

dstdev = stdev - etalon_stdev
dstdev_perc = (dstdev / etalon_stdev) * 100
ax.set_title("Δm:{:.3f}({:.2f}%), Δsd:{:.3f}({:.2f}%)".format(dmean, dmean_perc, dstdev, dstdev_perc))
plt.savefig('default.png')


