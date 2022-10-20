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
            val = int(input())
            if val < 0 or val > n:
                print('Введено неверное значение. Повторите попытку!')
                continue
            else:
                mat[i][j] = val
                break

print('\n' * 100)

print('Исходная матрица предпочтений: ')
for i in range(m):
    print()
    for j in range(n):
        print(mat[i][j], end = ' ')

print('\n\nМодифицированная матрица предпочтений:')
for i in range(m):
    print()
    for j in range(n):
        print(n-mat[i][j], end = ' ')

list_of_sums = []
print('\n\nСуммарные оценки предпочтений:')
for j in range(n):
    sum_of_marks = 0
    for i in range(m):
        sum_of_marks += (n-mat[i][j])
    print(sum_of_marks, end = ' ')
    list_of_sums.append(sum_of_marks)
    
omega = []
for i in range(n):
    omega.append(0)
    
print('\n\nИскомые веса целей:')
for i in range(n):
    omega[i] = list_of_sums[i]/sum(list_of_sums)
    print(round(omega[i], 2), end = ' ')
    
max_omega = omega[0]
solution = 1
for i in range(n):
    if omega[i] > max_omega:
        max_omega = omega[i]
        solution = i + 1

print('\n\nОТВЕТ: Наиболее выгодна альтернатива №', solution)


