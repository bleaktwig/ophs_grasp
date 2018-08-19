INSTANCES = 405
ITERS     = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 50, 100]
N_ITERS   = len(ITERS)

# === RESULTS GATHERING ====================================================== #
# results_m is a [INSTANCES][N_ITERS] matrix to store every test result
results_m = [[0 for x in range(N_ITERS)] for y in range(INSTANCES)]

for I in range(N_ITERS):
    fin = open("tests/" + str(ITERS[I]))
    out = fin.read()
    fin.close()

    counter = 0
    for line in out.splitlines():
        results_m[counter][I] = int(line)
        counter += 1

# === CALCULATING AVERAGES =================================================== #
averages = [0.0 for x in range(N_ITERS)]

for I in range(INSTANCES):
    for J in range(N_ITERS):
        results_m[I][J] = results_m[I][J] - results_m[I][0]
        if (results_m[I][N_ITERS-1] != 0):
            results_m[I][J] = float(results_m[I][J] / results_m[I][N_ITERS-1])
        averages[J] += results_m[I][J]

for J in range(N_ITERS):
    averages[J] = averages[J]/INSTANCES

for J in range(N_ITERS-1, 1, -1):
    averages[J] -= averages[J-1]

# === PRINTING RESULTS ======================================================= #
print("========================================")
print("  all tests:")
for J in range(1, N_ITERS):
    if   (ITERS[J] < 10):
        print("    " + str(ITERS[J]) + ":   " + str(100 * averages[J]) + '%')
    elif (ITERS[J] < 100):
        print("    " + str(ITERS[J]) + ":  " + str(100 * averages[J]) + '%')
    else:
        print("    " + str(ITERS[J]) + ": " + str(100 * averages[J]) + '%')
print("========================================")
# ============================================================================ #
