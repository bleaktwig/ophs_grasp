import math
import matplotlib.pyplot as plt

# === PARAMETERS DEFINITION ================================================== #
INSTANCES = 405
INIT_SEED = 1534452580
SEEDS     = [INIT_SEED + 0,  INIT_SEED + 1,  INIT_SEED + 2,  INIT_SEED + 3,
             INIT_SEED + 4,  INIT_SEED + 5,  INIT_SEED + 6,  INIT_SEED + 7,
             INIT_SEED + 8,  INIT_SEED + 9,  INIT_SEED + 10, INIT_SEED + 11,
             INIT_SEED + 12, INIT_SEED + 13, INIT_SEED + 14, INIT_SEED + 15,
             INIT_SEED + 16, INIT_SEED + 17, INIT_SEED + 18, INIT_SEED + 19
            ]
N_SEEDS   = len(SEEDS)

# === RESULTS GATHERING ====================================================== #
# NOTE: results_m is a [INSTANCES][N_ITERS] matrix to store every test result
results_m = [[0 for x in range(N_SEEDS)] for y in range(INSTANCES)]

for I in range(N_SEEDS):
    fin = open("tests/" + str(SEEDS[I]))
    out = fin.read()
    fin.close()

    counter = 0
    for line in out.splitlines():
        results_m[counter][I] = int(line)
        counter += 1

# === CALCULATING AVERAGES =================================================== #
averages     = [0.0 for x in range(INSTANCES)]
std_dev      = [[0.0 for x in range(N_SEEDS)] for y in range(INSTANCES)]
std_dev_avgs = [0.0 for x in range(INSTANCES)]
corr_std_dev = [0.0 for x in range(INSTANCES)]

# averages per instance
for I in range(INSTANCES):
    TEMP_SIZE = N_SEEDS
    for J in range(N_SEEDS):
        if results_m[I][J] == 0:
            TEMP_SIZE -= 1
        averages[I] += results_m[I][J]
    if TEMP_SIZE != 0:
        averages[I] /= TEMP_SIZE
    else:
        averages[I] /= N_SEEDS

# standard deviation per instance
for I in range(INSTANCES):
    for J in range(N_SEEDS):
        std_dev[I][J] = float(results_m[I][J]) - averages[I]
        std_dev[I][J] *= std_dev[I][J]
        std_dev_avgs[I] += std_dev[I][J]
    std_dev_avgs[I] = math.sqrt(std_dev_avgs[I]/(N_SEEDS-1))
    if averages[I] != 0:
        corr_std_dev[I] = std_dev_avgs[I]/averages[I]

# x axis for plotting
x_axis = [x for x in range(INSTANCES)]

# === PRINTING RESULTS ======================================================= #
plt.figure(figsize=(16, 8))

plt.plot(x_axis, corr_std_dev, c='r')

plt.xlabel("instance number")
plt.ylabel("scaled standard deviation")

plt.yticks([0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1])
plt.grid()

plt.savefig("stddev_graph.png", bbox_inches='tight')
plt.show()
# ============================================================================ #
