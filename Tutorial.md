# Input Files Guide

This simulator reads **two** text files:

- **`config.txt`** — global simulation settings
- **`bodies.txt`** — list of celestial bodies and their initial conditions

**Run (example):**
```bash
./main <run_name> <bodies_file> <config.txt>
# or, if available
./run.sh <run_name> <bodies_file> <config.txt>
```

---

## 1) `config.txt` — Simulation Configuration

**Format:** one `key=value` per line. Lines starting with `#` are comments.  
**Units:** SI — seconds, meters, kilograms, meters/second.

### Keys

| Key | Type | Units | Description | Example |
|---|---|---|---|---|
| `dt` | float/int | s | Integration time step. Smaller = more accurate, slower. | `dt=6` |
| `steps` | int | – | Total number of integration steps. | `steps=1000000` |
| `printingStepsPositions` | int | steps | Save positions every **N** steps. | `printingStepsPositions=1000` |
| `printingStepsEnergies` | int | steps | Save energies every **N** steps. | `printingStepsEnergies=1000` |
| `useLeapfrog` | `True`\|`False` | – | Integrator toggle. `True` = Leapfrog (symplectic; better long‑term energy). | `useLeapfrog=True` |
| `origin` | `x,y` **or** body name | m | Reference origin of the coordinate frame. Either two numbers (e.g., `0,0`) **or** the name of a defined body (e.g., `Sun`). | `origin=0,0` • `origin=Sun` |

> **Notes**
> - Booleans must be exactly `True` or `False` (capitalized).
> - Scientific notation is allowed: `1e6`, `9.94275e29`, etc.
> - Spaces around `=` are allowed. Avoid spaces **inside** pairs like `origin=0,0`.

**Minimal example**
```txt
# Simulation configuration
dt=6
steps=1000000
printingStepsPositions=1000
printingStepsEnergies=1000
useLeapfrog=False
origin=0,0
```

---

## 2) `bodies.txt` — Celestial Bodies

**One body per line.** Empty lines are allowed. **End each body line with a semicolon `;`.**  
**2D format:** positions `(x, y)`, velocities `(vx, vy)`.

### Grammar

```text
<Type> <Name> [(x, y), (vx, vy), mass]; [parent=ParentName]
```

**Fields**
- `<Type>` — one of: `Star`, `Planet`, `Moon`, `Comet`, `TestMass` (case‑sensitive).
- `<Name>` — identifier without spaces (use `_` if needed).
- `(x, y)` — initial position in **meters**.
- `(vx, vy)` — initial velocity in **m/s**.
- `mass` — mass in **kg** (scientific notation allowed; use `0` for massless tracers like `TestMass`).
- `parent=ParentName` *(optional)* — binds the body to its primary (e.g., planet → star, moon → planet).

> **Rules**
> - Always close the main block with `;` before any optional fields.
> - Use commas **inside** tuples: `(x, y)` and `(vx, vy)`.
> - Define a body **before** referencing it as `parent`.
> - Units must be SI across all values.
> - The format is **2D**; z components are implicitly zero.

### Examples

**Binary stars with two planets**
```txt
Star Star1 [(1e10, 0), (0, 30000), 9.94275e29];
Star Star2 [(-1e10, 0), (0, -30000), 9.94275e29];

Planet Planet1 [(6e10, 0), (0, 33000), 3e23]; parent=Star1
Planet Planet2 [(-6e10, 0), (0, -33000), 3e23]; parent=Star2
```

**Star → Planet → Moon**
```txt
Star Sun [(0, 0), (0, 0), 1.9885e30];
Planet Earth [(1.496e11, 0), (0, 29780), 5.972e24]; parent=Sun
Moon Moon_1 [(1.496e11 + 3.844e8, 0), (0, 29780 + 1022), 7.35e22]; parent=Earth
```
> Tip: precompute sums (e.g., replace `1.496e11 + 3.844e8` with the numeric result) to avoid parser issues.

---

## 3) Quick Validation Checklist

**`config.txt`**
- `dt` and `steps` set and numeric.
- Printing intervals are positive: `printingStepsPositions`, `printingStepsEnergies`.
- `useLeapfrog` is exactly `True` or `False`.
- `origin` is either `x,y` (two numbers) **or** a valid body name defined in `bodies.txt`.

**`bodies.txt`**
- One body per line; each line ends with `;`.
- Order and syntax match: `<Type> <Name> [(x,y), (vx,vy), mass]; [parent=...]`.
- `parent` (if any) references a previously defined body.
- Units are SI; masses are non‑negative.

---



## 4) Minimal Working Pair

**`config.txt`**
```txt
dt=10
steps=200000
printingStepsPositions=1000
printingStepsEnergies=1000
useLeapfrog=True
origin=0,0
```

**`bodies.txt`**
```txt
Star Alpha [(0, 0), (0, 0), 2.0e30];
Planet Beta [(1.5e11, 0), (0, 30000), 6.0e24]; parent=Alpha
```

**Run:**
```bash
./main demo bodies.txt config.txt
```
