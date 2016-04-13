import re
import os

currentDir = os.path.dirname(__file__)
data = open(os.path.join(currentDir, "graph15.txt"), 'r').readlines()
maxDeg = 0
for i in range(0, len(data)):
    x = re.findall("[0-9]+", data[i])
    if len(x) > maxDeg:
        maxDeg = len(x)

print "MaximalGrad ist " +  str(maxDeg)
