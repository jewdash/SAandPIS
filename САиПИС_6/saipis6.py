def check(a, b):
    if a > 0 and b > 0:
        return True
    else:
        return False

while True:
    m = int(input('Введите кол-во экспертов: '))
    n = int(input('Введите кол-во целей: '))
    if not check(m, n):
        print('Вы ввели некорректные значения. Повторите попытку!')
        continue
    else:
        break

while True:
    scale = int(input('Введите размерность шкалы: '))
    if scale < 0:
        print('Вы ввели некорректные значения. Повторите попытку!')
        continue
    else:
        break

list_of_mats = []
for k in range(m):
    list_of_mats.append([])
    for i in range(n):
        list_of_mats[k].append([])
        for j in range(n):
            list_of_mats[k][i].append(0)

for k in range(m):
    print("\nЭКСПЕРТ №", k + 1)
    for i in range(n):
        for j in range(i + 1, n):
            while True:
                print("Предпочтение цели №", i + 1,"над целью №", j + 1, ":", end = ' ')
                list_of_mats[k][i][j] = int(input())
                if list_of_mats[k][i][j] > scale:
                    print('Вы ввели некорректные значения. Повторите попытку!')
                    continue
                else: break
            list_of_mats[k][j][i] = scale - list_of_mats[k][i][j]
    print()

print('\n' * 100)

print("Матрицы экспертов: \n")
for k in range(m):
    print("\nЭКСПЕРТ №", k + 1)
    for i in range(n):
        print()
        for j in range(n):
            if i == j:
                print("-----", end = '\t\t')
            else:
                print(list_of_mats[k][i][j], "/", scale, end = '\t\t')
    print()

mat_of_rates = []
for i in range(n):
    mat_of_rates.append([])
    for j in range(m):
        mat_of_rates[i].append(0)

print("\n\nОценки предпочтений: \n")
for k in range(m):
    print("\nЭКСПЕРТ №", k + 1)
    for i in range(n):
        sum_of_elem = 0
        for j in range(n):
            if i != j:
                sum_of_elem += list_of_mats[k][i][j]
        mat_of_rates[i][k] = sum_of_elem
        print(mat_of_rates[i][k], "/", scale, end = '\t\t')
    print()

norm = n * (n - 1)
print("\n\nНормированные оценки N =", norm)

mat_of_normed_rates = []
for i in range(m):
    mat_of_normed_rates.append([])
    for j in range(n):
        mat_of_normed_rates[i].append(0)

for i in range(m):
    print("\nЭКСПЕРТ №", i + 1)
    for j in range(n):
        mat_of_normed_rates[i][j] = float((mat_of_rates[j][i]/scale)/norm)
        print(round(mat_of_normed_rates[i][j], 3), end = '\t')
    print()

omega = []
for i in range(n):
    omega.append(0)

print('\n\nИскомые веса целей:')
for i in range(n):
    for j in range(m):
        omega[i] += mat_of_normed_rates[j][i]
    print("omega", i + 1, ":", round(omega[i], 3))

max_omega = omega[0]
solution = 1
for i in range(n):
    if omega[i] > max_omega:
        max_omega = omega[i]
        solution = i + 1

print('\n\nОТВЕТ: Наиболее выгодна альтернатива №', solution)
