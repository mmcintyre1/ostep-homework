import random

max_address = 16 * 1024
iterations = 300
valid_addr_by_limit = [0] * max_address


for seed in range(iterations):
    random.seed(seed)

    for i in range(max_address):
        limit = i
        virtual_address = random.random() * 1024
        if virtual_address < limit:
            valid_addr_by_limit[i] += 1

percentages = [x / iterations * 100 for x in valid_addr_by_limit]
print(percentages)
