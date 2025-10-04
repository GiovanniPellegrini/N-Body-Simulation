from utils import readPositionsFromFile
import sys
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation, PillowWriter
import numpy as np
import os




def main():
    if len(sys.argv) != 3:
        print(f"Usage: python {sys.argv[0]} <directory> <file>")
        return

    directory = sys.argv[1]
    filename = sys.argv[2]
    output_name = os.path.join(directory, filename)
    if not os.path.exists(output_name):
        print(f"File {output_name} does not exist.")
        return    

    try:
        positions = readPositionsFromFile(output_name)
    except Exception as e:
        print(f"Error reading file {output_name}: {e}")
        return

    positions = readPositionsFromFile(output_name)
    bodies = list(positions.keys())
    n_frames = len(next(iter(positions.values())))

    fig, ax = plt.subplots(figsize=(10, 8))
    ax.set_xlim(-1.7e11, 1.7e11)
    ax.set_ylim(-1.7e11, 1.7e11)
    ax.set_xlabel("X [m]")
    ax.set_ylabel("Y [m]")
    ax.set_title("Positions animations of celestial bodies")

    scatters = {name: ax.scatter([], [], s=50, label=name) for name in bodies}
    ax.legend(loc='upper right', fontsize='small')

    def init():
        for scat in scatters.values():
            scat.set_offsets(np.empty((0, 2)))
        return scatters.values()

    def update(frame):
        for name in bodies:
            x, y = positions[name][frame]
            scatters[name].set_offsets(np.array([[x, y]]))
        return scatters.values()
    
    anim = FuncAnimation(
        fig,
        update,
        frames=range(0, n_frames, 5),
        init_func=init,
        blit=True,
        interval=50
    )

    out_file = output_name.replace('.txt', '.gif')
    writer = PillowWriter(fps=20)

    anim.save(out_file, writer=writer)

    print(f"Saved GIF animation to {out_file}")
    plt.close(fig)

if __name__ == "__main__":
    main()
