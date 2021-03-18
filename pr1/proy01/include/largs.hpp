/* 
 * largs.hpp: Definición de una clase para manejo de
 * argumentos de línea del programa paa_reader
 * Esta clase utiliza las librerías program_options 
 * de Boost. 
 * 
 * Héctor Pérez, marzo 2021.
 * 
 * Para el curso de Laboratorio Avanzado
 * ECFM - USAC
 * 
 */

#ifndef __LARGS_H__
#define __LARGS_H__


#include <cstdlib>
#include <string>


/* Clase para manejo de argumentos de línea del programa
 * paa_reader */
class largs
{
    private:

        /* Los atributos son básicamente los argumentos
         * de línea que se desean obtener. */

        /* Input file name */
        std::string *InputFileName;
        
        /* Input file name */
        std::string *OutputFileName;
        
        /* Pulse number */
        int PulseNumber;

        /* Adicional a los argumentos, se define un atributo
         * de verificación. Se utiliza para indicar si la línea
         * de argumentos es válida */
        bool ArgsOk;

    
    public:


        largs();

        /* Constructor con argumentos */
        largs(int argc, char* argv[]);

        /* Destructor */
        ~largs();

        /* Métodos GET */

        /* Devuelve el nombre del archivo de entrada proporcionado 
         * en la linea de comandos (opción -i)*/
        std::string GetLArgInputFile(){ return *InputFileName; };

        /* Devuelve el nombre del archivo de salida proporcionado 
         * en la linea de comandos (opción -o) */
        std::string GetLArgOutputFile(){ return *OutputFileName; };

        
        /* Devuelve el número de pulso proporcionado 
         * en la linea de comandos (opción -p) */
        int GetLArgPulseNumber(){ return PulseNumber; };

        /* Indica si la línea de comandos es válida */
        bool Args_Ok(){ return ArgsOk; };

        int Parse(int argc, char* argv[]);

};

#endif