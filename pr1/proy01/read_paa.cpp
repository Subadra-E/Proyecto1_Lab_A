/* 
 * read_pas.cpp: Código para lectura de archivos .paa
 * provenientes de la captura de datos de un WCD con la
 * utilidad Pulse Acquire para Red Pitaya. 
 * 
 * Héctor Pérez, marzo 2021.
 * 
 *Modificaciones: Subadra Echeverria, Marzo,2021
 *
 * Para el curso de Laboratorio Avanzado
 * ECFM - USAC
 * 
 */

#include <cstdio>
#include <vector>

#include "TGraph.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TFile.h"

/* Header de la clase paa_file que maneja los archivos .paa */
#include "paa.hpp"

/* Header de la clase largs que maneja los argumentos de línea */
#include "largs.hpp"

int main(int argc, char* argv[])
{
    /* Primero se crea una instancia de la clase que hace el 
     * "parsing" de los argumentos de línea proporcionados 
     * al programa. */ 
    largs cmd_args(argc,argv);

    /* Si los argumentos de la línea de comandos no son adecuados se 
     * interrumpe la ejecución delprograma. */
    if( !cmd_args.Args_Ok() )
        return 1;

    /* Se asocia el archivo de entrada provisto en el argumento
     * de línea con una instancia de la clase paa_file. */
    paa_file mi_archivo( cmd_args.GetLArgInputFile() );

    /* Se verifica si la asociación del archivo fue exitosa, 
     * Si no, se sale del programa */
    if(!mi_archivo.Is_Open())
        return 1;

    /* Se crean dos vectores de enteros para almacenar los datos
     * del pulso que se va leer desde el archivo .paa */
    std::vector<int> * pulseData_v;
    std::vector<int> * pulseData_t = new std::vector<int>;
    
    /***************************************************CAMBIOS*********************************/
    
    /* valor del voltaje de Threshold para cada pulso*/
    int vt = -270;

    /*variable utilizada como "bandera" para la sentencia de pulsos */

    bool d;
    
    /*contadores de tiempo para los pulsos seleccionados*/

    int t1; //*tiempo para el puso 1*/
    int t2;  /*tiempo para el pulso 2*/

    /* Histograma a llenar con los datos de pulsos dobles*/

    TH1D *aHist = new TH1D("h1"," Vida  Media del Muon ",29,0,0);
    

    /* Se procede a recorrer cada uno de los pulsos del archivo*/
    /*el siguiente "for" va desde 0 hasta el número de pulsos contenidos*/
    /* en cada archivo.paa, el cual está dado por  (mi_archivo.GetPulseEntries())*/

    for(int i=0; i < mi_archivo.GetPulseEntries(); i++){

        /*Se recorren todos los pulsos*/
        pulseData_v = mi_archivo.GetPulse( i ); 

       /* Se verifica que se hayan obtenido correctamente los datos
        * del pulso. */
       if(!pulseData_v)
        return 1;
        
        /*Iniciando a la bandera*/ 
        d = false;
        /*Iniciando los contadores en 0 para cada iteración*/ 
        t1 = 0;
        t2 = 0;
        
        /*Se procede a recorrer todos los datos obtenidos para cada pulso*/
        /* el numero de datos por pulso es 1100*/

        for (int j = 0; j < 1100; j++)
        {  
        
          /*Si el Dato es menor al voltaje Umbral, se considera lo */
          /*siguiente*/
          if( ((pulseData_v->at(j)) < vt) && (d == false) ){
            
            /*el indice de tiempo para el primer pulso será igual al índice del dato encontrado*/
            t1 = j;
            d = true;  /* se cambia el valor de la bandera a "true"*/
                
            j = j + 20; /*Tomando en cuenta el ancho del primer pulso encontrado,*/
                        /* se aumenta el índice para que solo se tome en cuenta al */
                        /*pulso una sola vez. En este caso se obtuvo un buen resultado*/
                        /* considerando un ancho de 20*/

          }else if( ((pulseData_v->at(j)) < vt) && (d == true)){ /* si el contador ahora es 1, se ejecuta lo que sigue para*/
                                                               /*el siguiente pulso encontrado*/
                
                /*el indice de tiempo para el segundo pulso sera igual al indice del dato encontrado*/
                t2 = j;    

               
                /*Ahora se irá llenando el histograma con los datos encontrados*/
                std::cout<< "num pulso: "<<i<<" tiempo entre pulsos = "<<((t2-t1)*8)<<"ns"<<std::endl;
                aHist->Fill((t2-t1)*8);/*se convierte el tiempo a nanosegundos al multiplicar por el*/
                               /*tiempo de muestreo que es 8 ns*/

                break; /* se detiene la búsqueda y pasa al  siguiente */
                       /* elemento del archivo*/
                
                           }
            
        }
    
        
    }

    /*Se crea un nuevo archivo para almacenar el histograma*/

     TFile *aFile= new TFile(cmd_args.GetLArgOutputFile().c_str(),"RECREATE");

    
    aHist->Write(); /* se almacena el histograma y  se cierra el archivo*/
    aFile->Close();
    

    return 0;

}


