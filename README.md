LAB-SDL

ОПИСАНИЕ

===========

Прогулка по лабирнту. Программа использует OpenGL3 и SDL 

КОМПИЛЯЦИЯ(Build)

===========

Используется CMake. 


БИБЛИОТЕКИ (Libraries)

==========

SDL
GLEW
SOIL
Glm

Перед запуском необходимо скопировать папку /Data в то место где расположен исполнимый файл. 

===================================

Основные изменения (30.08.2019)

1. Текстуры пола и стен - отдельные файлы: floor.png и wall.png соответственно

2. Добавлена возможность загружать карту из файла (файл map)
Формат файла:

width
height
string1
...
stringn

где width - длина карты, height - ширина, string1 .. stringn последовательность строк, которые состоят из символов от '0' до '3'. Другие символы запрещены. Количество строк и символов строке произвольно, лишь бы общее количество символов во всех строках string1 .. stringn совпадало с произведением width*height.

 
3. Внутренние изменения: 

1) добавлен Mipmap

2) объединение рядом расположенных стенок клеток в одну длинную стену. Тем самым уменьшается кол-во вершин. Применены тайловые текстуры.

