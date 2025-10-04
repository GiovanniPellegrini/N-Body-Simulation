import numpy as np

def readPositionsFromFile(filename):
    data = {}
    with open(filename, "r") as inFile:
        for line in inFile:
            line = line.strip()
            if not line:  # skip empty lines
                continue
            try:
                name, coords = line.split(" ", 1)
                x_str, y_str = coords.strip("()").split(",")
                x = float(x_str)
                y = float(y_str)

                if name not in data:
                    data[name] = []
                data[name].append((x, y))

            except Exception as e:
                print("Skipping unclear line:", line)
                continue

    return data

def energy_error_metric(etot, how="max"):
    etot = np.array(etot)
    delta = (etot - etot[0]) / etot[0]
    if how == "max":
        return np.max(np.abs(delta))
    elif how == "rms":
        return np.sqrt(np.mean(delta**2))
    elif how == "final":
        return abs(delta[-1])
    else:
        raise ValueError("how must be 'max', 'rms' or 'final'")

def readEnergiesFromFile(filename):
    """Extract steps, kinetic energy, and potential energy from a simulation output file."""
    steps, ekins, epots, etots = [], [], [], []
    with open(filename, 'r') as file:
        for line in file:
            if not line.startswith("Step"):
                continue
            parts = line.strip().split()
            try:
                step = int(parts[1])
                ekin = float(parts[3])
                epot = float(parts[5])
                etot= float(parts[7])
                steps.append(step)
                ekins.append(ekin)
                epots.append(epot)
                etots.append(etot)
            except (IndexError, ValueError):
                continue
    return steps, ekins, epots, etots
