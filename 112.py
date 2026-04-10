import numpy as np
import matplotlib.pyplot as plt

# ============================================================
# ДАННЫЕ
# ============================================================

elements = np.array([
    20000,40000,60000,80000,100000,120000,140000,160000,180000,200000,
    220000,240000,260000,280000,300000,320000,340000,360000,380000,400000
])

# Lookup
bst_lookup = np.array([
    2.7e-7,3.1e-7,3.5e-7,3.7e-7,4.1e-7,4.5e-7,4.8e-7,5.2e-7,5.5e-7,5.7e-7,
    6.0e-7,6.2e-7,6.5e-7,6.6e-7,6.8e-7,7.1e-7,7.2e-7,7.4e-7,7.4e-7,7.6e-7
])

hash_lookup = np.array([
    1.0e-7,1.1e-7,1.1e-7,1.3e-7,1.4e-7,1.5e-7,1.6e-7,1.6e-7,1.7e-7,1.8e-7,
    1.9e-7,1.9e-7,2.0e-7,2.0e-7,2.1e-7,2.2e-7,2.2e-7,2.3e-7,2.3e-7,2.4e-7
])

# Collisions
kr_collisions = np.array([
    500,1889,4212,7493,11600,16356,21915,28173,35043,42593,
    50677,59378,68777,78516,88773,99609,110710,122369,134376,146766
])

elf_collisions = np.array([
    550,2070,4592,8029,12388,17548,23381,29997,37331,45424,
    54062,63289,72915,83296,94153,105327,116939,128954,141337,154206
])

# ============================================================
# ПОДГОТОВКА
# ============================================================

x = elements / 1000  # тысячи
xf = np.linspace(x.min(), x.max(), 400)

# Полиномы для аппроксимации
poly_bst  = np.poly1d(np.polyfit(x, bst_lookup*1e6, 3))
poly_hash = np.poly1d(np.polyfit(x, hash_lookup*1e6, 3))

poly_kr   = np.poly1d(np.polyfit(x, kr_collisions, 3))
poly_elf  = np.poly1d(np.polyfit(x, elf_collisions, 3))

# ============================================================
# ГРАФИКИ
# ============================================================

plt.rcParams.update({
    "figure.figsize": (14,6),
    "axes.grid": True,
    "grid.alpha": 0.3,
    "lines.linewidth": 2
})

fig, ax = plt.subplots(1,2)

# ---------------- Lookup ----------------
ax[0].plot(x, bst_lookup*1e6, 'o', label='BST (data)')
ax[0].plot(x, hash_lookup*1e6, 'o', label='Hash (data)')

ax[0].plot(xf, poly_bst(xf), '--', label='BST approx')
ax[0].plot(xf, poly_hash(xf), '--', label='Hash approx')

ax[0].set_title("Lookup time")
ax[0].set_xlabel("Elements (thousands)")
ax[0].set_ylabel("Time (µs)")
ax[0].set_xlim(x.min(), x.max())
ax[0].legend()

# ---------------- Collisions ----------------
ax[1].plot(x, kr_collisions, 'o', label='KRHash (data)')
ax[1].plot(x, elf_collisions, 'o', label='ELFHash (data)')

ax[1].plot(xf, poly_kr(xf), '--', label='KR approx')
ax[1].plot(xf, poly_elf(xf), '--', label='ELF approx')

ax[1].set_title("Collisions")
ax[1].set_xlabel("Elements (thousands)")
ax[1].set_ylabel("Count")
ax[1].set_xlim(x.min(), x.max())
ax[1].legend()

plt.tight_layout()
plt.show()