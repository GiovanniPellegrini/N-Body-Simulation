# stability_from_earth_frame.py
# English comments inside code

import numpy as np
import matplotlib.pyplot as plt
import sys, os
from utils import readPositionsFromFile

# --- simulation parameters ---
dt_step     = 31.5576              # [s] integrator step
outputEvery = 1000                 # written every 1000 steps
dt_rec      = dt_step * outputEvery
omega       = 2 * np.pi / (365.25 * 86400)   # [rad/s]

# --- read input file ---
if len(sys.argv) != 3:
    print(f"Usage: python {sys.argv[0]} <directory> <positions.txt>")
    sys.exit(1)

directory = sys.argv[1]
filename  = sys.argv[2]
filepath  = os.path.join(directory, filename)
if not os.path.exists(filepath):
    print(f"File {filepath} does not exist.")
    sys.exit(1)


pos = readPositionsFromFile(filepath)


for name in pos:
    pos[name] = np.array(pos[name])   

# build time arrays
N        = pos["L1"].shape[0]
t_sec    = np.arange(N) * dt_rec
t_years  = t_sec / (365.25 * 86400)


r_nom0 = {}
for body in ["L1","L2","L3","L4","L5"]:
    #
    r_nom0[body] = pos[body][0].copy()
# plot Δr(t) = |r_sim(t) - R(ωt) r_nom0|
plt.figure(figsize=(8,5))
for body in ["L1","L2","L3","L4","L5"]:
    arr = pos[body]         
    x_sim = arr[:,0]
    y_sim = arr[:,1]

    
    cosw = np.cos(omega * t_sec)
    sinw = np.sin(omega * t_sec)
    x_nom =  r_nom0[body][0] * cosw - r_nom0[body][1] * sinw
    y_nom =  r_nom0[body][0] * sinw + r_nom0[body][1] * cosw

   

    d_km = np.hypot(x_sim - x_nom, y_sim - y_nom) / 1e3
    plt.plot(t_years, d_km, label=body, linewidth=0.8)

plt.xlabel("Time [yr]")
plt.ylabel("Distance from nominal [km]")
plt.title("Stability of Earth–Sun Lagrange points")
plt.grid(which="both", ls=":")
plt.legend()
plt.tight_layout()
plt.savefig("stability_log.01.png", dpi=300)
print("Saved stability_log.png")
