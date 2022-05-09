#include <stdio.h>
#include <stdbool.h>
// Si, no se puede usar tipos booleanos por defecto en c, hay que importar su librería


// Un dato cualquiera

typedef struct Foo
{
    int x, y;
    char msg[100];
} Foo;


// Binary files operations

// FILE es un tipo de C que permite manipulat archivos de texto plano y binarios
// Como tal no se pueden almacenar archivos en un tipo de dato pero si se pueden referenciar
// para luego escribir y leer datos
// A esos tipos los denominamos "File Handlers" o manipuladores de archivos

bool writeToBinary(Foo data, const char* fileName){ // No funciona bien si ponemos const char[], debe ser const char*
    // Declaramos un puntero a FILE el cual de ahora en más llamaremos handler
    FILE* file;
    // La función fopen_s nos permite darle la información necesaria al handler que declaramos
    // ¿Cómo funciona?
    // Primero, necesita la dirección de memoria de un handler(o un puntero al mismo) para poder 
    // otorgarle la información necesaria, eso va en el primer parámetro.
    // ¿De quién? Del archivo el cual ponemos su ruta en el segundo parámetro, si no existe lo creará

    /*** No olvidar que si solo pones el nombre del archivo con su extensión por defecto se 
    buscará dentro de la carpeta del programa ***/

    // El último parámetro indica la operación que realizaremos, en este caso es
    // writing binary o wb

    // Si hubo error en la lectura o el archivo se el handler será nulo
    // En C nulo se describe como NULL, en c++ como NULL o nullptr, nullptr es más seguro
    // ¿Por qué es más seguro? Ese será tema para algún taller o video en mi canal, háganme saber

    if(file == NULL) // Si es nulo retorna false
        return false;
    
    fopen_s(&file,fileName,"wb");

    // fwrite nos ayuda a escribir datos en binario
    // Para ello debemos pasarle la dirección de memoria del elemento a escribir
    // Luego le pasamos el tamaño del datos a escribir con ayuda de la función sizeof
    // Después, le pasamos la cantidad de elementos a escribir, en el caso de que
    // en lugar de escribir un sólo elemento fueran varios (una colección de elementos, Ej: arreglo)
    // en dicho casos pondríamos la cantidad de elementos de esa colección
    // Finalmente, el último parámetro es el handler con la información del achivo en el cual escribiremos
    // La función, de ejecutarse correctamente debería retornar la cantidad de elementos escritos
    // Si retorna 0 ha ocurrido un error

    size_t count = fwrite(&data,sizeof(Foo),1,file);

    // fwrite escribel en el archivo binario bit a bit la data que le damos, ya que cada tipo de dato
    // al fin y al cabo es un conjunto de bits en memoria

    if(count == 0)
        return false;
    fclose(file); // Cerramos en archivo con fclose y retornamos verdadero porque tuvimos éxito :D
    return true;
}

bool readFromBinary(const char* fileName){ // No funciona bien si ponemos const char[], debe ser const char*
    // Declaramos el handler
    FILE* file;
    // fopen nos ayuda a leer el archivo binario
    // Necesita tres parámetros
    // - La dirección de memoria de un handler que referenciará y manipulará ese archivo, de existir
    // - La ruta del archivo a leer
    // - El modo de la operación, en este caso es read binary o rb
    fopen_s(&file,fileName,"rb");
    if(file == NULL) // Si la lectura falla se almacena NULL en el handler y luego retornamos false
        return false;
    Foo f; // Definimos el dato que recepcionará la data que leeremos
    size_t readCount = fread(&f,sizeof(Foo),1,file);
    // con fread leemos el archivo
    // Esta función necesita tres parámetros:
    // - Una referencia del elemento que contendrá el dato leído, de tener éxito
    // - El tamaño del archivo a leer con ayuda de sizeof
    // - La cantidad de elementos a leer, en el caso de que
    // en lugar de escribir un sólo elemento fueran varios (una colección de elementos, Ej: arreglo)
    // en dicho casos pondríamos la cantidad de elementos de esa colección
    // - El handler que permite leer el archivo y recuperar los datos
    fclose(file);
    printf("\nEl dato leído es: Foo(%d, %d, %s)", f.x, f.y, f.msg);
    return true;
}


// Plain text operations
// Pronto... pero es muc

int main() {
    Foo data = {5,6,"Hola desde un archivo binario"}; // Constructor implícito en C, también existe C++
    bool writingResult = writeToBinary(data,"CFile.bin"); // Puede ser .bin o .dat
    // .bin se puede sobrescribir, .dat no, compruébenlo si desean :D
    if(writingResult) printf("\nSe escribió con éxito :D");
    else printf("\nAlgo salió mal en la escritura :(");

    bool readingResult = readFromBinary("CFile.bin");

    if(readingResult) printf("\nSe leyó con éxito :D");
    else printf("\nAlgo salió mal en la lectura :(");
    return 0;
}