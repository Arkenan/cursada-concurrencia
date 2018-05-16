---
author: Tomás Arjovsky
date: 14 de Mayo de 2018
title: Repaso antes del Parcial
---

### Señales

Acordarse de bloquear una señal cuando se abre el handler. Esto se debe porque si no se hace y se llama a la misma señal durante el handler, la segunda llamada al handler comenzará en un estado no consistente.

Al volver continúa en el mismo punto.

Recordar que siempre se llama de forma:

```c
void signal_handler_function (int signum) {
  ...;
}
```

Es void. No tiene sentido que devuelva otra cosa además. Primero, quién lo agarra? Segundo, se ejecuta de forma asincrónica.

Hay handlers que por default hacen cosas (ver cuáles). Hacen kill, dump, stop, continue, etc. Una vez que les asignamos un handler eso no se hace más. Sigkill y Sigstop no se puede hacer nada.

Los handlers no deberían ser muy largos: podría recibir mil veces la señal en el medio y perderlas.

Tip: no toman patrones de diseño. Las señales se usan a lo rústico.

### Shared Memory

El shmctl marca para destrucción. Se lo eliminará solo cuando haya sido detachado por todos. Puede ocurrir que el sistema operativo se encargue de borrar el segmento de memoria si nadie lo tiene atacheado al final de todo, pero eso no es excusa. Hay que hacer detach desde todos.

Una opción es hacer un if para ver si están todos desatachados.

No es bloqueante el shmctl, no?

### Semáforos

En general nunca deberíamos resetear el valor de un semáforo, sino usar siemrpe p y v, pero por el simple hecho de que un semáforo representa una serie de recursos compartidos y no suele haber discontinuidades en esos recursos. Un caso legítimo de reset de un semáforo es tal vez para una barrera por la que se puede pasar muchas veces, pero nunca que represente recursos.

### Pipes y FIFOS

Tiene que sí o sí haber algún tipo de parentezco entre los procesos. Hijo y padre, ambos hijos de un padre, o lo que sea. La razón es porque es necesario tener acceso a file descriptors que apunten al pipe. Tienen que tener la misma tabla de archivos abiertos o nunca podrán estar relacionados entre sí los file descriptors.

**Recordar cerrar todos los file descriptors**.

Para archivos sin relación se usan sí o sí fifos. Cualquiera que acceda al filesystem puede acceder. Habría que ver si hay diferencia de performance por acceso al filesystem o no, pero esto no es algo que importe en este examen.

Recordar que el FIFO puede bloquearse en read y write, pero también en open. No abrir y cerrar un open/close adentro de un for, por ejemplo. Recordar practicar FIFOS de muchos a uno y demás.

### Varios

Recordar que puede haber preguntas teóricas. De los miércoles, pero teóricas.
