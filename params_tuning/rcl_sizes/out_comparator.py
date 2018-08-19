INSTANCES = 405
HOTELS =    10
POIS =      10

# === RESULTS GATHERING ====================================================== #
# results_m is a [405][25] matrix to store every test result
results_m = [[0 for x in range(HOTELS*POIS)] for y in range(INSTANCES)]

for H in range(HOTELS):
    for P in range(POIS):
        fin = open("tests/" + str(H+1) + '-' + str(P+1))
        out = fin.read()
        fin.close()

        counter = 0
        for line in out.splitlines():
            results_m[counter][H*HOTELS + P] = int(line)
            counter += 1

# === BEST RESULTS COUNTING ================================================== #
i_best = [0 for x in range(HOTELS*POIS)]

for I in range(INSTANCES):
    i_max = max(results_m[I])
    for X in range(HOTELS*POIS):
        if i_max == results_m[I][X]:
            i_best[X] += 1

# === PRINTING RESULTS ======================================================= #
print("========================================")
print("best results by rcl sizes:")
for X in range(HOTELS*POIS):
    print("    " + str(int(X/HOTELS)+1) + '-' + str(X%HOTELS+1) + ": " + str(i_best[X]))
print("========================================")
# ============================================================================ #
