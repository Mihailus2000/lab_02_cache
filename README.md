# Лабораторная работа №2

> Кэш - промежуточный буфер с быстрым доступом, содержащий информацию, которая может быть запрошена с наибольшей вероятностью. Доступ к данным в кэше осуществляется быстрее, чем выборка исходных данных из более медленной памяти или удаленного источника, однако её объём существенно ограничен по сравнению с хранилищем исходных данных.

### Задача

Для каждого из вариантов проходов (*прямой*, *обратный* и *случайный*) целочисленного массива 
провести исследование зависимости времени от размера.

Каждое исследование включает в себя серию эксперементов c определенными размерами.

Количество экспериментов в серии определяется следующим образом:

```cpp
1/2 * cache_sizes['1'] < 2^x < 2^(x+1) < ... < 2^(x+n) < 3/2 * cache_sizes['max']
```

### Пример

В примере ниже показано, что для процессора с тремя уровнями кэша (`2mb`, `4mb`, `8mb`)
необходимо провести серию из 5 эксперементов.

```cpp
cache_size['1'] = 2 mb;
cache_size['2'] = 4 mb;
cache_size['3'] = 8 mb;

// 1mb < 2mb < 4mb < 8mb < 12mb
```

### Эксперимент

Каждый эксперемент состоит из 3 шагов:

```cpp
1. Создание буфера
2. Прогревание кэша
// <-- время начала эксперемнта
3. Циклический проход (1000 итераций)
// <-- время окончание эксперемента
```

#### Шаг 1

Инициализация буфера может происходит, как с помощью чтения данных из файла в выделенную область памяти,
так и с помощью случайного заполнения с использованием генератора случайных чисел.

#### Шаг 2

Данный шаг необходимо выполнить для получения репрезентативных данных, т.к. кэш-память еще не заполнена.

#### Шаг 3

Для получения времени обхода от размера массива процедуру прохода необходимо многократно повторить (порядка 1000 раз).

### Результаты

Ниже представлен формат и пример отчета:

```yaml
investigation:                                       |  investigaion:
  travel_variant: <вариант_прохода>                  |    travel_order: "direction"
  experiments:                                       |    experiments:
  - experiment:                                      |    - experiment:
      number:                                        |        number: 1
      input_data:                                    |        input_data:
        buffer_size: <размер_буфера>                 |          buffer_size: "1mb"
      results:                                       |        results:
        duration: <продолжительность>                |          duration: "1ns"
  - experiment:                                      |    - experiment:
      number: <номер_эксперимента>                   |        number: 2
      input_data:                                    |        input_data:
        buffer_size: <размер_буфера>                 |          buffer_size: "2mb"
      results:                                       |        results:
        duration: <продолжительность>                |          duration: "2ns"
                                                     |
investigation:                                       |  investigation:
...                                                  |  ...
```

⚠️ В отчет также необходимо добавить общий график с результатами всех исследований. ⚠️

Ссылка на график зависимостей Времени выполнения от размера буфера для Realease режима:
    http://yotx.ru/#!1/3_h/sH%406Ctg4N9I4bwv7Z/tH%40wf7DvJ6XW9jcudngHuxunIN7W7sbWDox3sbuxc3bKg%401unG3t8LYudze2DnZAPNDB7sbOAQjG29qC7W6ADi5PeRcHF7v7O/skGnYDdMB43AFtMR5BB7v7W/tb%40xsXO7yt3Y1TEG9nd2NrB8YD7W7snJ3yYLsbZ1s7vK3L3Y2tgx0Q7wK2u7FzAILxLnd2N0AHl6e8HdjB7v7OPomG3dg5O2M8bm1dMh63ELv7W/tb%40xsXO7yd3Y1TEA%402u7G1A%40NtIXY3ds5OeaCz3Y2zrR3e1s7F7sbWwQ6IBzoA7W7sHIBgvK2ty63djYuDy1PexdnZwe7%40zj6Jht3YgiEYjweMx4Pd/a39rX0B

Ссылка на график зависимостей Времени выполнения от размера буфера для Debug режима:
    http://yotx.ru/#!1/3_h/sH%406Ctg4N9I4bwv7Z/tH%40wf7DvJ6XW9jcudnhbZ4jdjVMQb%40dya3djawfGOz2D7W7snJ3ytna2DnY3zrZ2eFuXMMTuxtbBDoh3cXm6tbu/s0%40iYTdAB4zHHdAW4xF0sLu/tb%401v3Gxw9va2drdOAXxdkAXuxtbOzAe6HJrd2Pn7JR3CTvY3Tjb2uFtXZ7Cdje2DnZAPNDBzsXuxs4BCMaDHWzBdjdAB5envK3Tsx3Y7v7OPomG3dg5O2M8bm1dMh63ELv7W/tb%40xsXO7ytU9DuximId3EB293Y2oHxTk%403djd2zk55WxeI092Ns60d3s7l5dbuxtbBDoiHOLiA7W7sHIBgvK1T0MXB7gbo4PKUB4KdXZ7t7u/sk2jYjS0YgvF4wHg82N3f2t/aBwU=

