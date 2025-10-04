from utils import readEnergiesFromFile, energy_error_metric
import matplotlib.pyplot as plt
import sys
import os

def main():
    if len(sys.argv) != 3:
        print(f"Usage: python {sys.argv[0]} <directory> <file_prefix>")
        return

    directory = sys.argv[1]
    filename = sys.argv[2]
    output_name = os.path.join(directory, filename)
    if not os.path.exists(output_name):
        print(f"File {output_name} does not exist.")
        return
    
    try:
        steps, ekins, epots, etots = readEnergiesFromFile(output_name)
    except Exception as e:
        print(f"Error reading file {output_name}: {e}")
        return

    virial_diff = [ep + 2 * ek for ep, ek in zip(epots, ekins)]
    E0   = etots[0]
    
    

    # Plotting the energies
    fig, ax = plt.subplots(2, 1, figsize=(10, 8), sharex=True)


    # Subplot 2: E_pot + 2 * E_kin
    ax[0].plot(steps, virial_diff, label="E_pot + 2·E_kin", color="green", linestyle=":")
    ax[0].set_ylabel("Energy [J]")
    ax[0].set_xlabel("Step")
    ax[0].set_title(f"Virial Theorem")
    ax[0].legend()
    ax[0].grid(True)
    
    # Subplot 3: error 
    rel_err = [abs((E - E0) / E0) for E in etots]
    error_max=energy_error_metric(etots, how="max")
    print(f"error: {max((rel_err))}")
    
    
    ax[1].plot(steps, rel_err, label="(E(t) - E₀) / E₀")
    ax[1].set_ylabel("Error")
    ax[1].set_xlabel("Step")
    ax[1].set_title("Relative Energy Error (E-E₀)/E₀")
    ax[1].legend()
    ax[1].grid(True, which="both", ls="--")
    
    output_name = os.path.join(directory, f"energies.png")
    plt.savefig(output_name, dpi=300)
    plt.close()
    print(f"Saved: {output_name}")
    print()
    print()

if __name__ == "__main__":
    main()



