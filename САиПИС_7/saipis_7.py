from itertools import combinations
from math import factorial
from xmlrpc.server import list_public_methods

def rate_in(rate, c, d):
    while True:
        print("Предпочтение проекта №", c, "над проектом №", d, ":", end = ' ')
        rate = float(input())
        if rate > 1 or rate < 0:
            print('Вы ввели некорректные значения. Повторите попытку!')
            continue
        else: return rate

def check(a, b):
    if a > 0 and b > 0:
        return True
    else:
        return False

while True:
    x = int(input('Введите кол-во экспертов: '))
    y = int(input('Введите кол-во проектов: '))
    if not check(x, y):
        print('Вы ввели некорректные значения. Повторите попытку!')
        continue
    else:
        break

z = factorial(y)//(factorial(y - 2) * 2)

list7 = []
for i in range(z * 2):
    list7.append([])
    for j in range(x + 2):
        list7[i].append(0)

c = 1
d = c + 1
i = 0
while i < z * 2:
    list7[i][0] = c
    list7[i + 1][0] = d
    d += 1
    if d > y:
        c += 1
        d = c + 1
    i += 2

for i in range(1, x + 1):
    print("\nЭКСПЕРТ №", i)
    for j in range(0, z * 2, 2):
        list7[j][i] = rate_in(list7[j][i], list7[j][0], list7[j + 1][0])
        list7[j + 1][i] = 1 - list7[j][i]

print('\n' * 5)
print("Исходная матрица предпочтений: ")

print("Эксы/проекты", end = '\t')
for j in range(0, z * 2, 2):
    print(list7[j][0], "*****", list7[j + 1][0], end = '\t')

for i in range(1, x + 1):
    print()
    print("ЭКСПЕРТ №", i, end = '\t')
    for j in range(0, z * 2, 2):
        print(round(list7[j][i], 2), "**", round(list7[j + 1][i], 2), end = '\t')

print()
print('Сумма оценок: ', end = ' ')
for j in range(0, z * 2, 2):
    my_sum = 0
    for i in range(1, x + 1):
        my_sum += list7[j][i]
    list7[j][x + 1] = my_sum
    list7[j + 1][x + 1] = x - my_sum
    print(round(list7[j][x + 1], 2), "**", round(list7[j + 1][x + 1], 2), end = '\t')

list_of_sums = []
for i in range(y):
    list_of_sums.append(0)

print('\n' * 3)
print('Суммарные оценки предпочтений: ')
for i in range(1, y + 1):
    my_sum = 0
    for j in range(0, z * 2):
        if list7[j][0] == i:
            my_sum += list7[j][x + 1]
        list_of_sums[i - 1] = my_sum

for i in range(y):
    print('Проект №', i + 1, ':', round(list_of_sums[i], 2))

omega = []
for i in range(y):
    omega.append(0)

print('\n' * 3)
print('Искомые веса проектов: ')

for i in range(y):
    print('Проект №', i + 1, ':', round((list_of_sums[i]/sum(list_of_sums)), 3))
    omega[i] = round((list_of_sums[i]/sum(list_of_sums)), 3)

max_omega = omega[0]
solution = 1
for i in range(y):
    if omega[i] > max_omega:
        max_omega = omega[i]
        solution = i + 1

print('\n\nОТВЕТ: Наиболее выгодный проект №', solution)
