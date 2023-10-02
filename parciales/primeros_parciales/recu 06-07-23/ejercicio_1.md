### Ejercicio 1

**a)**

**Árbol de procesos**
- Proceso 88
    - Proceso 89
        - Proceso 91
    - Proceso 90
        - Proceso 92
        - Proceso 93

**Proceso padre:**
1. pipe
2. Hace 2 forks (id1: 89, id2: 90)
3. read de "Abuelaaaa, la, la, la..."
4. write de "Mensaje de mi nieto: Abuelaaa, la, la, la ..."
5. wait de id1 = 89
6. wait de id2 = 90
7. extit

**Proceso 89 (hijo de padre):**
1. Fork (id: 91)
2. sleep de 1 segundo
3. write de "Soy el hijo pepito"
4. wait de id = 91
5. kill(91, SIGKILL)
6. exit

**Proceso 90 (hijo de padre):**
1. Fork (id: 92)
2. getpid() = 90
3. Fork (id: 93)
4. sleep de 2 segundos
5. write de "Soy la hija juanita"
6. wait de id = 92
7. write de "Oh no ... mi hijo nos quiere matar!"
8. kill(89, SIGTERM)
9. kill(92, SIGKILL)
10. exit

**Proceso 91 (hijo de 89):**
1. sleep de 2 segundos
2. write de "Soy el nieto juanito"
3. write de "Abuelaaaa, la, la, la..."
4. sleep de 9999 segundos
5. killed by 89

**Proceso 92 (hijo de 90):**
1. sleep de 9999 segundos
2. killed by 90

**Proceso 93 (hijo de 90):**
1. sleep de 3 segundos
2. write de "No se quien soy... debo matar!!"
3. kill(90, SIGTERM)
4. exit

- **Fork:** Crea un proceso hijo, que es una copia del padre con un pid distinto al padre.
- **Pipe:** Crea un canal de comunicación entre procesos, que permite la comunicación entre procesos padre e hijo.
- **Wait:** Espera a que el proceso hijo termine.
- **Kill:** Envia una señal a un proceso.
- **SIGKILL:** Señal que mata al proceso.
- **SIGTERM:** Señal que termina al proceso pero le permite a este hacer cosas antes de terminar.

**b)**

```c

// Constantes
#define READ 0
#define WRITE 1

// Globales
int nieto1, pepito_pid, juanita_pid, junaito_pid;

// 88
void abulea() {
    int pipe[2];

    pipe(pipe);

    pepito_pid = fork();

    if (pepito_pid == 0) pepito();
    
    juanita_pid = fork();

    if (juanita_pid == 0) juanita();

    char msg[30];

    read(pipe[READ], &msg, 30);

    write(1, msg, 30);

    wait(pepito_pid);

    wait(juanita_pid);

    exit(0)
}

void jandler_pepito() {
    kill(juanito_pid, SIGKILL);
}

// 89
void pepito() {
    signal(SIGTERM, SIGTERM)

    juanito_pid = fork();

    if (juanito_pid == 0) juanito();

    sleep(1);

    write(1, "Soy el hijo pepito!\n", 19);

    wait(juantio_pid);

    exit(0);
}

void handler_juanita() {
    kill(pepito_pid, SIGTERM);
    kill(nieto1, SIGKILL);
}

// 90
void juanita() {
    signal(SIGTERM, handler_juanita())

    nieto1 = fork();

    if (nieto1 == 0) nieto1();

    int mi_pid = getpid();

    int nieto2 = fork();

    if (nieto2 == 0) nieto2();

    sleep(2);

    write(1, "Soy la hijo juanita\n", 20);

    wait(nieto1);

    exit(0);
}

// 91
void juanito() {
    sleep(2);

    write(1, "Soy el nieto juanito\n", 21);

    write(pipe[WRITE], "Abuelaaaa, la, la, la...\0", 30);

    sleep(9999);
}

// 92
void nieto1(){ 
    sleep(9999);
}

// 93
void nieto2() {
    sleep(3);

    write(1, "No se quien soy... debo matar!!\n", 32);

    kill(juanita_pid, SIGTERM);

    exit(0);
}




```