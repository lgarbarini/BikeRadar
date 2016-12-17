import numpy as np
import input as i

i.setup()
a = i.get_vec()
print(len(np.split(a, 4)))
print(np.split(a, 4))
print(np.amax(a))
