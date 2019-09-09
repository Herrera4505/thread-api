# Thread API # 

En esta sección escribiremos algunos programas multi-hilo y usaremos una herramienta específica llamada ```helgrind``` para encontrar problemas en estos programas. 

## Questions ##

1. Primero codifique ```main-race.c```. Examine el código de manera que usted pueda ver (ojalá de manera obvia) un data race en el código. Ahora ejecute ```helgrind``` (al teclear ```valgrind --tool=helgrind ./main-race```) y vea como este programa reporta los *data races*. ¿Se muestran las líneas de código involucradas?, ¿Qué otra información entrega este programa?

    *R/En esta caso ya que la region ciritica se estan implementando el mutex lock y unlock este no presenta nignuna condicion de *data races* y al no haber conlfictos no nos entrega nignun tipo de información sobre algun error como se puede ver en la imagen.


    *Si modificamos el codigo y evitamos el uso de los locks se generan errores de posibles *data races* puesto que no se garantiza un acceso atomico a la variable compartida *balance*, esto se puede ver en la siguiente imagen, donde se nos muestra que el error esta en las lineas de codigo 13 y 27, helgrind tambien nos indica cuales son los hilos involucrados en el data race

2. ¿Qué ocurre cuando usted elimina una de las líneas que generan problemas en el código? Ahora agrege un lock alrededor de las actualizaciones de la variable compartida, y entonces alrededor de ambas. ¿Qué reporta ```helgrind``` en cada uno de estos casos?

    *R/Los lock se agregaron en el punto anterior, ahora al momento de eliminar una de las variables *balance*, el programa no muestra ningun tipo de error, esto debido a que ya no existe un *data race*

3. Ahora observe ```main-deadlock.c```. Examine el código. Este código tiene un problema conocido como deadlock. ¿Puede ver que problema podrá este tener?
4. Ahora ejecute ```helgrind``` en este código. ¿Qué reporta helgrind?
5. Ahora ejecute ```helgrind``` en ```main-deadlock-global.c```. Examine el código. ¿Tiene este el mismo problema que ```main-deadlock.c```? ¿Muestra ```helgrind``` el mismo reporte de error? ¿Qué dice esto a cerca de herramientas como ```helgrind```?
6. Ahora observe ```main-signal.c```. Este código usa una variable (```done```) para señalar que el hijo esta hecho y que el padre puede continuar. ¿Por qué este códido es ineficiente? (En que termina el padre dedicando su tiempo, si el hijo toma una gran cantidad de tiempo en completarse).
7. Ahora ejecute ```helgrind``` para este programa. ¿Qué reporta helgrind?, ¿Es correcto el código?
8. Ahora observe una versión levemente modificada del código, la cual es encontrada en ```main-signal-cv.c```. Esta versión usa una variable de condición para señalizar (y asociar un lock). ¿Por qué este código es mejor que la versión previa? ¿Es la corrección, o el desempeño, o ambos?
9. Ejecute de nuevo ```helgrind``` en ```main-signal-cv``` ¿Reporta algunos errores?

**Nota**: Se adjuntan los códigos para facilitar en análisis.
