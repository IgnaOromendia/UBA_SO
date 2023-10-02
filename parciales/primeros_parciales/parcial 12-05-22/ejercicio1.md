### Sincornización y concurrencia

- 1 estante = `N` tablas + `M` tornillos + `K` clavos
- Recepción de materiales -> Ensamblaje -> Pintura -> Despacho
- Para **ensamblar** deben estar todos los materiales
- Para **pintar** se necesitan `L` estantes
- 3 tipos de procesos que representan cada material

```c
// Estructuras de sincornización
mutex_t mtx = sem(1);

semt_t ensamblar_tablas   = sem(0);
semt_t ensamblar_tornillo = sem(0);
sent_t ensamblar_clavos   = sem(0);
semt_t permiso_pintar     = sem(0);

// Variables globales
int cant_ensamblados        = 0;
int tablas_ensambladas      = 0;
int clavos_ensambladas      = 0;
int tornillo_ensambladas    = 0;
int cant_tablas             = 0;
int cant_tornillos          = 0;
int cant_clavos             = 0;

void tabla() {
    // Entramos a sección critca
    mtx.wait();

    cant_tablas++;

    // Avisa que se puede ensamblar
    if (cant_tablas == N && 
        cant_tornillos >= M && 
        cant_clavos >= K) {
            
        cant_tablas = 0;
        cant_tornillos -= M;
        cant_clavos -= K;
        ensamblar_tablas.signal(N);
        ensamblar_tornillos.signal(M);
        ensamblar_clavos.signal(K);
    }

    // Salimos de sección critica
    mtx.signal();
    ensamblar_tablas.wait();

    // Ensamblar
    ensamblar();

    // Entramos a sección critica
    mtx.wait();
    tablas_ensambladas++;

    // Avisa que se puede pintar
    if (tablas_ensambladas == N && 
        tornillos_ensamblados == M && 
        clavos_ensamblados == K) {

        tablas_ensambladas    = 0;
        tornillos_ensamblados = 0;
        clavos_ensamblados    = 0;

        cant_ensamblados++;
    }

    if (cant_ensamblados == L) {
        cant_ensamblados = 0;
        permiso_pintar.signal(L * N * M * K);
    }

    // Salimos de sección critica
    mtx.signal();
    permiso_pintar.wait();

    // Pintar
    pintar();

    // Despachar
    despachar();
}

void tornillo() {
    // Similar a tabla pero con cant_tornillos
}

void clavo() {
    // Similar a tabla pero con cant_clavos
}

```
