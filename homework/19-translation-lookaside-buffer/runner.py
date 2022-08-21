import platform
import matplotlib.pyplot as plt
import numpy as np
import subprocess

POWER = 14
TRIALS = 10000

data = []

power_array = np.arange(POWER)
pages = 2**power_array

for page in pages:
    result = subprocess.run(
        ["./tlb.out", str(page), str(TRIALS)],
        capture_output=True,
        check=True,
        text=True,
    )
    print(result)

    data.append(float(result.stdout.strip()))

print(data)

plt.plot(power_array, data, marker="o")
plt.xticks(power_array, labels=pages, fontsize="x-small")
plt.xlabel("Number of Pages")
plt.ylabel("Time per Access(ns)")
plt.title(
    f"TLB Size Measurements: {platform.system()} {platform.release()} {platform.machine()}"
)
plt.savefig("tlb.png")
plt.show()
