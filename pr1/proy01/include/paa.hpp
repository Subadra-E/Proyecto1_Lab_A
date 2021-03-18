/* 
 * paa.hpp: Definición de una clase para manejo de
 * archivos .paa provenientes del software
 * Pulse Acquire Tools para Red Pitaya. 
 * 
 * Héctor Pérez, marzo 2021.
 * 
 * Para el curso de Laboratorio Avanzado
 * ECFM - USAC
 * 
 */

#ifndef __PAA_H__
#define __PAA_H__


#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


/* Clase para manejo de archivos .paa */
class paa_file
{
    private:

        /* Nombre del archivo asociado con la instancia */
        std::string *name;

        /* Input stream  para archivo asociado */
        std::ifstream PAAFile;

        /* Datos por pulso */
        uint32_t ps;

        /* Número de pulsos contenidos en el archivo */
        uint32_t pc;
        
        /* Threshold level utilizado para la captura */
        int32_t tl;
    
    public:

        /* Constructores */
        paa_file();
        paa_file(std::string fileName);

        /* Destructor */
        ~paa_file();

        /* Métodos GET */

        /* Retorna el número de pulsos contenidos en el archivo */
        int GetPulseEntries(){ return pc; };

        /* Retorna el número de datos por pulso */
        int GetPulseSize(){ return ps; };

        /* Retorna el threshold level utilizado par la captura del pulso */
        int GetThresholdLevel(){ return tl; };

        /* Retorna los datos del pulso pulseNumber del archivo */
        std::vector<int>* GetPulse(unsigned int pulseNumber);

        /* Indica si el archivo fue asociado correctamente y está
         * abierto */
        bool Is_Open(){ return ( name? true : false ); };

        /* Método para asociar un archivo .paa a una instancia */
        int open(std::string fileName);

};

#endif