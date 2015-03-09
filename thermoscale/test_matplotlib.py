from pylab import *
import numpy as np

data = range(100)

fig, ax = subplots()
plot(data)

min_val = 20
max_val = 50
plt.vlines([min_val, max_val], 0, 30, color='red')

plt.axis([max_val, 100, 0, 100], sharex=ax, sharey=ax, frameon=False)
plot(data)

plt.show()