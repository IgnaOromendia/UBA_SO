### Sincronización

- Hay N carritos con capacidad C cada uno
- Llega uno al inicio y hasta que no se llena no sale
- Inicia el viaje y viene otro carrito
- Se baja la gente
- Vuelve a la fila

```c

// Estructuras de sincronización
vector<semaphore> carrito_viaje(N, 0);
vector<semaphore> permiso_subir(N, 0);
semaphore mutex = 1;
semaphore iniciar_viaje = 0;
semaphore permiso_bajar = 0;

// Globales
int cantidad_personas = 0;
int personas_bajadas  = 0;
int indice_carrito    = 0;
int carritos          = 0;

void carrito(int i) {
    // Para prevenir que haya más de N carritos
    mutex.wait();
    if (carritos == N) return;
    if (i == 0) permiso_subir[i].signal(C);
    carritos++;
    mutex.signal();

    while(true) {
        // Esperar a que se llene el carrito
        carrito_viaje[i].wait();

        // hace el recorrido
        recorrido();

        // baja toda la gente
        permiso_bajar.signal(C);
    }
}

[0,1,2]

void persona() {
    // Esperar a que haya un carrito disponible
    permiso_subir[indice_carrito].wait();

    // Subir al carrito
    mutex.wait();

    // Si es el último, iniciar el viaje
    if (cantidad_personas == C - 1) {
        // Reincica contador
        cantidad_personas = 0;

        // Avisa de iniciar el viaje
        carrito_viaje[indice_carrito].signal();

        // Avanzamos al siguiente carrito
        indice_carrito = (indice_carrito + 1) % N;

        // Avismaos que se pueden subir al siguiente carrito
        permiso_subir[indice_carrito].signal(C);
    }

    // Esperar a que se llene el carrito
    cantidad_personas++;
    mutex.signal();

    // Esperar a que termine el viaje
    permiso_bajar.wait();
}
```