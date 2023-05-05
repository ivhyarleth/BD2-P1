### [BD2] PROYECTO 1: Organización de Archivos

**INTEGRANTE:**
Arleth Lapa Carhuamaca

---

## Introducción

La organización de archivos es un proceso fundamental para mantener la eficacia en el acceso a la documentación generada. Por ello, el principal objetivo del presente proyecto es lograr la implementación y análisis de los algoritmos de almacenamiento de archivos físicos y acceso concurrente para lograr una buena gestión de archivos. En primer lugar, se implementó dos técnicas de organización de archivos en memoria secundaria, las cuales son: _Seguential_ _File_ y _Extendible_ _Hashing_, cada una con sus respectivas operaciones principales, tales como, inserción, eliminación y búsqueda. En la siguiente sección se explica con mayor detalle lo antes mencionado. En segundo lugar, el dominio de datos a usar es de un dataset público llamado Kaggle, contiene un archivo plano con datos reales de una lista de películas y series. En tercer lugar se realizó pruebas y los resultados experimentales obtenidos nos brindaran una comparación entre las dos técnicas utilizadas, discusión y análisis de estos. En último lugar, se demostrara la evidencia de las funcionalidades de este programa en un video.

## Fundamento

### Sequential File

Es una técnica simple de organización de datos,en esta los archivos se almacenan secuencialmente según una secuencia lógica en la memoria de la computadora, tiene dos formas de implementación: Pile File y Sorted File. Asimismo, admite operaciones de datos, tales como: insertar, actualizar, eliminar y recuperar datos.

#### Búsqueda específica

Se implementó una búsqueda binaria, ya que los archivos están ordenados, con esta función se retorna la posición donde se encuentra el registro que se busca.

#### Inserción

Se recibe a un archivo como input, los archivos se encuentran ordenados físicamente, por ello se realiza un auxiliar para insertar el nuevo registro y luego se actualiza, con ello se asegura que nuestro archivo se encuentre ordenado.

#### Eliminación

Primero se busca y encuentra el registro a eliminar, con la función seekg(pos) obtenemos la posición, con esta posición aplicamos la técnica LIFO, donde en el header escribimos el nuevo next delete y modificamos el next delete a eliminar.

### Extendible Hashing

Es una técnica de hash dinámico, por lo cual es muy flexible para localizar los datos que estan asociados con un identificador único o clave determinada. Esta técnica proporciona una estructura dinámica que crece y se reduce a medida que la base de datos crece y se reduce.

#### Búsqueda específica

Se aplica la función Hash sobre la key que se quiere encontrar y esta devuelve una secuencia de índices, luego la entrada al directorio que coincide con dicho índice es la que dirige a un bucket, el cual contiene el registro que buscamos.

#### Búsqueda por rango

Utilizando la lógica anterior, se utilizan los dos parámetros para buscar en cada bucket y verificar si estos se encuentran en el rango buscado.

#### Inserción

Primero se localiza el bucket respectivo, si no encontró el bucket, procede a buscar uno con la profundidad local mínima y a crearlo. Si encuentra un bucket y no está lleno, procede a instalarlo, y si el bucket está lleno, este se divide y reinsertar todos los registros.

#### Eliminación

Se localiza el buffer respectivo y se elimina dicho registro, cuando éste quede vacío, este puede ser liberado.

#### Video

La presentación final en video se encuentra en el siguiente [link][https://drive.google.com/file/d/1BITSe0JpOkjizn4gKW2LFWt9lRRfynvL/view?usp=sharing]
