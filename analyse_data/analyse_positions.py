import matplotlib.pyplot as plt
import sys
from utils import readPositionsFromFile
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
    plt.figure(figsize=(10, 8))

    for name, coords in positions.items():
        xs, ys = zip(*coords)
        print(f"Plotting {name} with {len(xs)} points")
        plt.scatter(xs, ys, label=name, s=5)

    plt.xlabel("X [m]")
    plt.ylabel("Y [m]")
    #plt.xlim(-6e10, 6e10)
    #plt.ylim(-6e10, 6e10)
    #plt.xlim(-2.5e11, 2.5e11)
    #plt.ylim(-2.5e11, 2.5e11)
    #plt.xlim(-4e11, 4e11)
    #plt.ylim(-4e11, 4e11)
    
    
    plt.title("Positions of celestial bodies")
    plt.tight_layout()
    plt.legend()

    output_image = output_name.replace(".txt", ".png")
    plt.savefig(output_image, dpi=300)
    print(f"Saved: {output_image}")

if __name__ == "__main__":
    main()
