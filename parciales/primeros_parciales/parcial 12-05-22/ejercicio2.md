### Scheduling

- Real time
- Interactivas

Pensado para un scheduler con preemtive con multicolas de _k_ prioridades. En las cuales para la prioridad 0 se utiliza un _FIFO_ y para las demas un _Round Robin_ con un quantum de **8k** unidades de tiempo con aging.

Para las `real time` un _FIFO_ ya que queremos que se ejecuten en el orden que llegan.

Para las `interactivas`, la cuales entran con prioridad mayor a 0, un _Round Robin_ con un quntum de **8k** unidades de tiempo, siendo k la prioridad, ya que queremos beneficiar a los procesos que hacen I/O. Ya que si un proceso hace E/S, este pone su estado en _waiting_ y deja su lugar a otro proceso. Sin embargo, si consume todo el quantum signifca que esta utilizando mucho el CPU. Igualmente debe teber `feedback (aging)` para que no se queden en la cola para siempre y se genere `starvation`. En caso de que el proceso haga E/S la prioridad aumenta.