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
    
mat = []
for i in range(m):
    mat.append([])
    for j in range(n):
        mat[i].append(0)
    
print('Составить исходную матрицу предпочтений: ')
for i in range(m):
    print('Эксперт №', i+1)
    for j in range(n):
        while True:
            print("\tЦель №", j+1, ": ", end=' ')
            val = float(input())
            if val < 0 or val > 10:
                print('Введено неверное значение. Повторите попытку!')
                continue
            else:
                mat[i][j] = val
                break

print('\n' * 100)

print('Исходная матрица: ')
for i in range(m):
    print()
    for j in range(n):
        print(int(mat[i][j]), end = ' ')

list_of_normed_rates = []
for i in range(m):
    list_of_normed_rates.append([])
    for j in range(n):
        list_of_normed_rates[i].append(0)

list_of_sums = []
for i in range(m):
    sum_of_rates = 0
    for j in range(n):
        sum_of_rates += mat[i][j]
    list_of_sums.append(sum_of_rates)

print('\n\nМатрица нормированных оценок: ')
for i in range(m):
    print()
    for j in range(n):
        list_of_normed_rates[i][j] = mat[i][j]/list_of_sums[i]
        print(round(list_of_normed_rates[i][j], 3),  end = ' ')

omega = []
for i in range(n):
    omega.append(0)

print('\n\nИскомые веса целей:')
for j in range(n):
    sum_of_column = 0
    for i in range(m):
        sum_of_column += list_of_normed_rates[i][j]
    omega[j] = sum_of_column/float(m)
    print(round(omega[j], 3), end = ' ')

max_omega = omega[0]
solution = 1
for i in range(n):
    if omega[i] > max_omega:
        max_omega = omega[i]
        solution = i + 1

print('\n\nОТВЕТ: Наиболее выгодна альтернатива №', solution)


