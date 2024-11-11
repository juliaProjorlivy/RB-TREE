import random
import time

filename = "range_queries_data.txt"
answers_filename = "range_queries_answers.txt"

MAX_K = 100
MIN_K = 20

MIN_VAL = -1000
MAX_VAL = 1000

NQUERIES = 100

random.seed(time.time())
Nk = random.randint(MIN_K, MAX_K)

data_set = set()
with open(filename, "w") as file, open(answers_filename, "w") as answers_file:
    for j in range(NQUERIES):
        for i in range(Nk):
            val = random.randint(MIN_VAL, MAX_VAL)
            data_set.add(val)
            file.write("k {:d} ".format(val))
        end = random.randint(MIN_VAL, MAX_VAL)
        begin = random.randint(MIN_VAL, end)
        file.write("q {:d} {:d} ".format(begin, end))
        res = 0
        for number in range(begin, end + 1):
            res += (number in data_set)
            print(begin, end, res)
        answers_file.write("{:d} ".format(res))

answers_file.close()
file.close()

