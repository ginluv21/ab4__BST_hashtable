import numpy as np
import matplotlib.pyplot as plt

# ============================================================
# ЗАГРУЗКА ДАННЫХ ИЗ ФАЙЛОВ
# ============================================================

# data1.txt: N, bst_lookup, hash_lookup
x1, bst_lookup, hash_lookup = np.loadtxt("data1.txt", unpack=True)

# data2.txt: N, bst_add, hash_add
x2, bst_add, hash_add = np.loadtxt("data2.txt", unpack=True)

# data6_time.txt: N, kr_lookup, elf_lookup
x3, kr_lookup, elf_lookup = np.loadtxt("data6_time.txt", unpack=True)

# data6.txt: N, kr_collisions, elf_collisions
x4, kr_col, elf_col = np.loadtxt("data6.txt", unpack=True)

# ============================================================
# ПРЕОБРАЗОВАНИЕ ДАННЫХ
# ============================================================

# Ось X в тысячах элементов
x = x1 / 1000
xf = np.linspace(x.min(), x.max(), 400)

# Время в микросекундах
bst_lookup *= 1e6
hash_lookup *= 1e6
bst_add *= 1e6
hash_add *= 1e6
kr_lookup *= 1e6
elf_lookup *= 1e6

# ============================================================
# ФУНКЦИЯ АППРОКСИМАЦИИ (ПОЛИНОМ 3-Й СТЕПЕНИ)
# ============================================================

def approx(x, y, deg=3):
    p = np.poly1d(np.polyfit(x, y, deg))
    return p(xf)

# ============================================================
# НАСТРОЙКИ ГРАФИКОВ
# ============================================================

plt.rcParams.update({
    "figure.figsize": (14,10),
    "axes.grid": True,
    "grid.linestyle": "--",
    "grid.alpha": 0.3,
    "lines.linewidth": 2,
    "font.size": 11
})

fig, ax = plt.subplots(2,2)

# ============================================================
# ГРАФИК 1 — Lookup BST vs Hash
# ============================================================

ax[0,0].scatter(x, bst_lookup, label="BST")
ax[0,0].scatter(x, hash_lookup, label="Hash")
ax[0,0].plot(xf, approx(x, bst_lookup), "--")
ax[0,0].plot(xf, approx(x, hash_lookup), "--")
ax[0,0].set_title("Lookup time (µs)")
ax[0,0].set_xlabel("Elements (thousands)")
ax[0,0].set_xlim(x.min(), x.max())
ax[0,0].legend()

# ============================================================
# ГРАФИК 2 — Add BST vs Hash
# ============================================================

ax[0,1].scatter(x, bst_add, label="BST")
ax[0,1].scatter(x, hash_add, label="Hash")
ax[0,1].plot(xf, approx(x, bst_add), "--")
ax[0,1].plot(xf, approx(x, hash_add), "--")
ax[0,1].set_title("Add time (µs)")
ax[0,1].set_xlabel("Elements (thousands)")
ax[0,1].set_xlim(x.min(), x.max())
ax[0,1].legend()

# ============================================================
# ГРАФИК 3 — KR vs ELF Lookup
# ============================================================

ax[1,0].scatter(x, kr_lookup, label="KRHash")
ax[1,0].scatter(x, elf_lookup, label="ELFHash")
ax[1,0].plot(xf, approx(x, kr_lookup), "--")
ax[1,0].plot(xf, approx(x, elf_lookup), "--")
ax[1,0].set_title("Lookup time KR vs ELF (µs)")
ax[1,0].set_xlabel("Elements (thousands)")
ax[1,0].set_xlim(x.min(), x.max())
ax[1,0].legend()

# ============================================================
# ГРАФИК 4 — Collisions
# ============================================================

ax[1,1].scatter(x, kr_col, label="KRHash")
ax[1,1].scatter(x, elf_col, label="ELFHash")
ax[1,1].plot(xf, approx(x, kr_col), "--")
ax[1,1].plot(xf, approx(x, elf_col), "--")
ax[1,1].set_title("Collisions")
ax[1,1].set_xlabel("Elements (thousands)")
ax[1,1].set_xlim(x.min(), x.max())
ax[1,1].legend()

plt.tight_layout()
plt.show()