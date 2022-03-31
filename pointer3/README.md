#CM0dul3s

+--- ./pointer3/fourth\_task.c ---+
<p><b>Создание трехмерного списка и работа с ним</b></p>
<br><img src="../images/image4.jpg"></img>
<br>
<b>ru:</b> Техническое задание:<br>
Функция читает из файла текст по словам и возвращает двухуровневый динамический массив указателей на строки, каждый элемент которого указывает на строки,<br>содержащие слова из исходного файла, упорядоченные по алфавиту (тип данных char ***).<br>
Размерность массива указателей нижнего уровня задана, каждый массив указателей ограничен NULL. Очередная строка<br> вставляется с сохранением порядка, в первом цикле просматривается массив<br>
указателей первого уровня и в каждом – элемент с индексом 0 второго уровня. Если его значение больше нового,<br>
то выполянется вставка в предыдущий массив указателей нижнего уровня. Если при вставке происходит переполнение,<br>
массив создается новый массив указателей, в который копируется половина указателей текущего.<br>
<br>
<br>
<p><b>Creating and working with a 3D list</b></p><br>
<b>en:</b> Terms of Reference:<br>
The function reads text word by word from the file and returns a two-level dynamic array of pointers to strings, each element of which points to strings<br>containing the words from the source file, sorted alphabetically (data type char ***).<br>
The dimension of the array of low-level pointers is given, each array of pointers is limited to NULL. The next row<br> is inserted in order, in the first loop the array<br> is looked through
pointers of the first level and in each - an element with index 0 of the second level. If its value is greater than the new one,<br>
then insertion into the previous array of lower-level pointers is performed. If pasting overflows,<br>
array, a new array of pointers is created, into which half of the current pointers are copied.<br> 
<br>

+---------------------------------+
