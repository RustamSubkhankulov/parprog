### Метод глобального стека для параллельного вычисления интеграла с использованием **std::thread**.

#### Постановка задачи
Основным заданием данной лабораторной работы является разработка параллельной программы для вычисления определенного интеграла от функции $f(x)$ от $A$ до $B$. Решение должно быть сбалансированным - время выполнения задачи на всез нитях должно быть одинаковым. Шаги интегрирования должны выбираться динамически. Для реализации программы будет использоваться библеотека поддержки параллелизма (**Concurrency support library (since C++11)**).

$$f(x)=sin(\frac{1}{x})$$
$$A<=x<=B, A,B>0, A<B$$

#### Методы, не подходящие для решения 
Методы геометрического параллелизма (статическая балансировка) и коллективного решения (динамическая балансировка) практически непригодны для решения поставленной задачи и не удовлетворяют требования к программе:
- При использовании метода геометрического параллелизма возникает значительный дисбаланс нагрузки вычислительных узлов при расчете инеграла на разных отрезках
- При использовании метода коллективного решения возникает либо большой дисбаланс нагрузки процессоров, либо большой объём лишних вычислений в зависимости от числа отрезко интегрирования, на которое делится изначальный промежуток.

#### Метод глобального стека

За основу возьмем **метод локального стека**,

```
IntegrateLocalStack(A,B)
{
  J=0
  
  fA=f(A)
  fB=f(B)
  
  sAB=(fA+fB)*(B-A)/2
  
  while(1)
  {
    Обработка отрезка
  }

  return J
}
```

где обработка отрезка:
```
  C=(A+B)/2
  fC=f(C)

  sAC=(fA+fC)*(C-A)/2
  sCB=(fC+fB)*(B-C)/2

  sACB=sAC+sCB
  
  if(|sAB-sACB|≥ε|sACB|)
  {
    PUT_INTO_STACK( A, C, fA, fC, sAC)
    
    A=C
    fA=fC
    sAB=sCB
  }
  else
  {
    J+=sACB

    if(STACK_IS_FREE)
      break
    
    GET_FROM_STACK( A, B, fA, fB, sAB)
  }
```

Идея паралельного алгоритма:
1. Всем параллельным процессам доступен список отрезков интегрирования, организованный в виде стека. Назовем его **глобальным стеком**.
2. Каждому процессу доступен свой, доступный только этому процессу, локальный стек
3. Перед запуском параллельных процессов в глобальный стек помещается единственная запись (в дальнейшем **"отрезок"**):
  - координаты концов отрезка интегрирования
  - значения функции на концах
  - приближенное значение интеграла на этом отрезке
4. Каждый из параллельных процессов выполняет следующий алгоритм:
  - взять один **отрезок** из **глобального стека**
  - выполнить алгоритм локального стека (см. ниже), но если в момент обращения к **локальному стеку** в нем уже есть несколько **отрезков**, а в **глобальном стеке** отрезки отсутствуют, то переместить часть **отрезков** из **локального стека** в **глобальный стек**

#### Сборка
Для того, чтобы собрать проект, воспользуйтесь следующей коммандой:
```
cmake -b build && cmake --build build --target integrate
```

#### Запуск
Запуск программы производится с помощью следующей комманды:
```
./build/integrate
```
#### Результаты измерений
