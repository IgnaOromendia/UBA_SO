### Gestión de memoria

secuencia: 7,2,3,1,2,5,3,4,6,7,7,1,0,5,4,6,2,3,0,1

**LRU**
|Páginas de marco|Lista|#Hits|
|:--------------:|:---:|:---:|
|7 - -| 7 - -| 0 |
|7 2 -| 2 7 -| 0 |
|7 2 3| 3 2 7| 0 |
|1 2 3| 1 3 2| 0 |
|1 2 3| 2 1 3| 1 |
|1 2 5| 5 2 1| 1 |
|3 2 5| 3 5 2| 1 |
|3 4 5| 4 3 5| 1 |
|3 4 6| 6 4 3| 1 |
|7 4 6| 7 6 4| 1 |
|7 4 6| 7 6 4| 2 |
|7 1 6| 1 7 6| 2 |
|7 1 0| 0 1 7| 2 |
|5 1 0| 5 0 1| 2 |
|5 4 0| 4 5 0| 2 |
|5 4 6| 6 4 5| 2 |
|2 4 6| 2 6 4| 2 |
|2 3 6| 3 2 6| 2 |
|2 3 0| 0 3 2| 2 |
|1 3 0| 1 0 3| 2 |

_Hit rate = 2 / 20_


Falta FIFO y Second Chance