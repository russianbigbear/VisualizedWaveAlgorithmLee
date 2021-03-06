## Консольный игровой уровень с визуализированным алгоритмом Ли

### Задание
За основу задания был взять обычный волновой алгоритм Ли для поиска пути до объекта.
Задачей было написать и улучшить данный алгоритм, реализовать визуализацию происходящих событий.

### Алгоритм
**Поиск пути** – это термин в информатике и ИИ, который означает определение наилучшего оптимального маршрута между двумя точками (начало и конец).<br/>
<br/>
Данный алгоритм используется в основном для 2D игр, где используется поиск пути от игрока до объекта,
а также для проектов где нужен поиск короткого пути от начальной точки и до конечной (игры лабиринты, поиск пути для врага, змейка, шахматы и т.п).
Этот алгоритм принадлежит к типу трассировочных алгоритмов. Основным плюсом данного алгоритма является его простая реализация и возможность применения
его к задачам поиска пути для динамичных объектов. Так, описание алгоритма и его реализация может быть произведена в разных средах программирования,
что говорит об его универсальности. Временная сложность схожа с алгоритмом Дейкстры и приближается в худшем случае к O(N^2).<br/>
<br/>
Описание классического волнового алгоритма Ли.<br/>
Алгоритм работает на дискретном рабочем поле (ДРП), представляющем собой ограниченную замкнутой линией фигуру, разбитом на ячейки(клетки). <br/>
На ДРП, есть несколько типов клеток:
1. Проходимые (свободные) ячейки. По таким ячейкам может быть проложен путь.
2. Непроходимые (препятствие). Такой тип ячеек можно только обойти, проход по ним запрещен
3. Стартовая ячейка (начало пути). С данной ячейки начинается поиск пути до финишной ячейки.
4. Финишная ячейка (конец пути). Эта ячейка является последней ячейкой в пути. До неё ведется поиск пути.

Основной задачей алгоритма является поиск кратчайшего пути между стартовой ячейкой и финишной. При отсутствии такого пути, выдает сообщение.<br/>
<br/>
Работа алгоритма включает в себя три этапа: инициализацию, распространение волны и восстановление пути.<br/>
<br/>
Во время инициализации строится образ множества ячеек обрабатываемого поля, каждой ячейке приписываются атрибуты проходимости/непроходимости, 
запоминаются стартовая и финишная ячейки.<br/>
<br/>
Далее, от стартовой ячейки порождается шаг в соседнюю ячейку, при этом проверяется, проходима ли она,
и не принадлежит ли ранее меченной в пути ячейке. В классическом алгоритме подразумевается поиск в 4 соседних ячейки.
В своей программе, я увеличил соседей до 8, включив возможность перемещения по диагонали.<br/>
<br/>
При выполнении условий проходимости и непринадлежности её к ранее отмеченным в пути ячейкам,
в атрибут ячейки записывается число, равное количеству шагов от стартовой ячейки, от стартовой ячейки на первом шаге это будет 1.
Каждая ячейка, меченая числом шагов от стартовой ячейки становится стартовой и из неё порождаются очередные шаги в соседние ячейки.
Очевидно, что при таком переборе будет найден путь от начальной ячейки к конечной, либо очередной шаг из любой порождённой в пути ячейки будет невозможен.<br/>
<br/>
Восстановление кратчайшего пути происходит в обратном направлении: от финишной ячейки к стартовой на каждом шаге выбирается ячейка,
имеющая атрибут расстояния от стартовой на единицу меньше текущей ячейки. Очевидно, что таким образом находится кратчайший путь между парой заданных ячеек. <br/>
<br/>
Есть модификации данного алгоритма, которые работаю быстрей классического. Волновой алгоритм характеризуется высокой эффективностью нахождения пути за счет исследования всех свободных ячеек ДРП, но требует значительного времени на распространение волны, поэтому используют различные методы ускорения выполнения первого этапа алгоритма.
Один из них – выбор начальной точки пуска волны.<br/>
Другая идея ускорения поиска пути заключается в исследовании не всех свободных ячеек ДРП, а лишь по заданным направлениям.
Один из таких алгоритмов – лучевой алгоритм. Для площадок А и В задают количество распространяемых лучей и разрешение направления их движения.
При прохождении луча через ячейку ей присваивают путевую координату.  Вероятность нахождения пути этим алгоритмом меньше, чем волновым.
Лучевой обычно используется для трассировки и компоновки плат.<br/>
<br/>
Есть аналоги волнового алгоритма. Такие как A* и Jump Point Search (JPS). Они работают быстрей за счёт исключения просмотра некоторых ячеек ДРП,
но иногда находят ни самый короткий путь.<br/>
Для демонстрации было взято видео со скрещенным алгоритмом A* JPS. Из этого видео можно подчеркнуть,
что данный алгоритм работает значительно быстрей классического алгоритма Ли, за счёт не обхода многих ячеек ДРП.<br/>
<br/>
**Работа программы.**<br/>
В начале данной программы, выводится красочная инструкция с названием карт и условными обозначениями. 
Далее, выбрав карту, нужно ввести её название, тогда пойдет обработка карты.<br/>
Все карты хранятся в основном каталоге и при желании, можно сделать ещё. Карты хранятся в разрешение .txt. Карта квадратная.<br/>
После ввода названия, идёт считывание карты с файла.
В данном файле хранится вся информация о проходимых, непроходимых ячейках, о начале и конце, а также размер карты.
Мы заносим всю информации в вектора, а также определяем координаты начала, занося их в очередь обходимых ячеек, и конца. Это инициализация.<br/>
После считывания карты и занесения данных в определенные вектора, идёт поиск пути.
Пока очередь поиска пути не пуста, мы извлекаем координаты x, y и ищем путь, то есть заносим не пройденные ранее и свободных соседей в очередь обработки,
а также увеличиваем дальность ячейки от начала на 1. При этом при каждом поиске мы выводим карту. Это второй этап – распространение волны.<br/>
Третьем и заключительным этапом идёт восстановление пути при удачном поиске. После восстановления пути выводится карта с найденным путём.
Путь находится для 8 соседей, как и восстановление пути.<br/>
В конце, мы можем либо выйти из программы, либо попробовать другую карту.<br/>



