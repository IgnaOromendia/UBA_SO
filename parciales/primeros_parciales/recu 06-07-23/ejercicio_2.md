### Scheduling

1. RR con quantum 3 (Round Robin)
2. FCFS (First Come First Served)
3. SRT (Shortest Remaining Time)


|Proceso|Instante de llegada|Ráfaga de CPU|
|:-----:|:-----------------:|:-----------:|
|P1|1|9|
|P2|2|5|
|P3|6|8|
|P4|5|4|

**a)**\
**RR con quantum 3**\
Desde inclusive hasta exclusive
|Tiempo|EXEC|READY|Finalizados|
|:----:|:-----:|:---:|:---------:|
|1-4|P1|P1| -
|4-7|P2|P1, P2| -
|7-10|P4|P3, P1, P2, P4| -
|10-13|P3|P1, P2, P4, P3| -
|13-16|P1|P2, P4, P3, P1| -
|16-18|P2|P4, P3, P1, P2| P2
|18-19|P4|P3, P1, P4| P2, P4
|19-22|P3|P1,P3| P2, P4
|22-25|P1|P3| P2, P4, P1
|25-27|P3|-| P2, P4, P1, P3

_Turnaround_: (25 - 1) + (18 - 2) + (27 - 6) + (19 - 5) / 4 = 18.75

**FCFS**
|Tiempo|EXEC|READY|Finalizados|
|:----:|:-----:|:---:|:---------:|
|1-10|P1|P1| -
|10-15|P2|P2| P1
|15-19|P4|P4| P1, P2
|19-27|P3|P3| P1, P2, P4
|27| - | - | P1, P2, P4, P3

_Turnaround_: 9 + (15 - 2) + (19 - 5) + (27 - 6) / 4 = 14.25

**SRT**
|Tiempo|EXEC|READY|Finalizados|
|:----:|:-----:|:---:|:---------:|
|1-2|P1|P1| -
|2-7|P2|P1, P2| -
|7-12|P4|P1, P4, P3| P2
|12-21|P1|P1, P3| P2, P4
|21-30|P3|P3| P2, P4, P1
|30| - | - | P2, P4, P1, P3

_Turnaround_: (21 - 1) + (7 -2) + (30 - 6) + (12 - 5) / 4 = 14

En este caso, el algoritmo que mejor resultado da es el **SRT**, ya que es el que tiene el menor turnaround.
