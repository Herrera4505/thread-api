# Thread API # 

En esta sección escribiremos algunos programas multi-hilo y usaremos una herramienta específica llamada ```helgrind``` para encontrar problemas en estos programas. 

## Questions ##

1. Primero codifique ```main-race.c```. Examine el código de manera que usted pueda ver (ojalá de manera obvia) un data race en el código. Ahora ejecute ```helgrind``` (al teclear ```valgrind --tool=helgrind ./main-race```) y vea como este programa reporta los *data races*. ¿Se muestran las líneas de código involucradas?, ¿Qué otra información entrega este programa?

    *R/En esta caso ya que la region ciritica se estan implementando el mutex lock y unlock este no presenta nignuna condicion de *data races* y al no haber conlfictos no nos entrega ningún tipo de información sobre algun error como se puede ver en la imagen.
    
    ![enlace](https://raw.githubusercontent.com/Herrera4505/thread-api/master/lab/imagenes/raceLocks.png)

    *Si modificamos el codigo y evitamos el uso de los locks se generan errores de posibles *data races* puesto que no se garantiza un acceso atomico a la variable compartida *balance*, esto se puede ver en la siguiente imagen, donde se nos muestra que el error esta en las lineas de codigo 13 y 27, helgrind tambien nos indica cuales son los hilos involucrados en el data race
    
    ![enlace](https://raw.githubusercontent.com/Herrera4505/thread-api/master/lab/imagenes/raceNoLocks.png)

2. ¿Qué ocurre cuando usted elimina una de las líneas que generan problemas en el código? Ahora agrege un lock alrededor de las actualizaciones de la variable compartida, y entonces alrededor de ambas. ¿Qué reporta ```helgrind``` en cada uno de estos casos?

    *R/Los lock se agregaron en el punto anterior, ahora al momento de eliminar una de las variables *balance*, el programa no muestra ningun tipo de error, esto debido a que ya no existe un *data race*
    
    ![enlace](https://raw.githubusercontent.com/Herrera4505/thread-api/master/lab/imagenes/raceNobalance.png)

3. Ahora observe ```main-deadlock.c```. Examine el código. Este código tiene un problema conocido como deadlock. ¿Puede ver que problema podrá este tener?

    *R/ El hilo p1 intentara adquirir el lock de la variable m1 y luego de m2, pero tambien lo intentara el hilo p2, si existe un cambio de contexto luego de que un hilo a adquirido m1, no podra adquirir m2 ya que sera p2 quien lo adquiera, ningun hilo podra continuar su ejecucion al la espera de el otro lock, produciendo un interbloqueo *Deadlock*.

4. Ahora ejecute ```helgrind``` en este código. ¿Qué reporta helgrind?

    *R/ Muestra que se tiene un error, una violacion en el hilo 3, quien adquirio el lock de m2 *0X6020E0* pero no pudo adquirir el de m1, el segundo hilo p1 adquirio el lock de m1 *0X6020A0*.

    ![enlace](https://raw.githubusercontent.com/Herrera4505/thread-api/master/lab/imagenes/deadLock.png)

5. Ahora ejecute ```helgrind``` en ```main-deadlock-global.c```. Examine el código. ¿Tiene este el mismo problema que ```main-deadlock.c```? ¿Muestra ```helgrind``` el mismo reporte de error? ¿Qué dice esto a cerca de herramientas como ```helgrind```?

    *R/ Este codigo no tiene el mismo problema, ya que implementa un mutex con una variable global *g*, que bloquea la zona donde estan los demas mutex, sin embargo al ejecutar el helgrind, aparece reportado el mismo error del codigo anterior lo que nos enseña que no es completamente confiable la informacion arrojada por herramientas como *helgrind*.

    ![enlace](https://raw.githubusercontent.com/Herrera4505/thread-api/master/lab/imagenes/deadlockGlobal.png)

6. Ahora observe ```main-signal.c```. Este código usa una variable (```done```) para señalar que el hijo esta hecho y que el padre puede continuar. ¿Por qué este códido es ineficiente? (En que termina el padre dedicando su tiempo, si el hijo toma una gran cantidad de tiempo en completarse).

    *R/Este codigo a pesar de funcionar, no es eficiente debido a que mientras el padre espera a que el hijo termine, que podria ser mucho tiempo en otros casos, va a consumir recursos sin necesidad, en una espera activa desperdicia tiempo de cpu. 

7. Ahora ejecute ```helgrind``` para este programa. ¿Qué reporta helgrind?, ¿Es correcto el código?

    *R/Reporta un posible *race condition* aunque no es un problema real, se debe a que la variable *done* es global y es utilizada tanto por el padre en la espera, como por el hijo para indicar que ya fue ejecutado.

    ![enlace](https://raw.githubusercontent.com/Herrera4505/thread-api/master/lab/imagenes/mainSignal.png)

8. Ahora observe una versión levemente modificada del código, la cual es encontrada en ```main-signal-cv.c```. Esta versión usa una variable de condición para señalizar (y asociar un lock). ¿Por qué este código es mejor que la versión previa? ¿Es la corrección, o el desempeño, o ambos?

    *R/Esta version es mejor debido a que no consume tiempo de cpu por el hilo padre, mientras es ejecutado el hijo, a traves del wait, el padre duerme a la espera de poder continuar.

9. Ejecute de nuevo ```helgrind``` en ```main-signal-cv``` ¿Reporta algunos errores?

**Nota**: Se adjuntan los códigos para facilitar en análisis.
