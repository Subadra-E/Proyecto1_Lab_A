/* 
 * largs.cpp: Implementación de una clase para manejo de
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

#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>

/* Se utiliza la libreria program_options de Boost */
#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include "largs.hpp"

largs::largs()
{
    InputFileName  = 0;
    OutputFileName = 0;
    PulseNumber = 0;
    ArgsOk = false;
}

largs::largs(int argc, char* argv[])
{ 
    InputFileName  = 0;
    OutputFileName = 0;
    PulseNumber = 0;
    ArgsOk = false;
 
    Parse(argc, argv);
}

largs::~largs()
{
    delete InputFileName;
    delete OutputFileName;
}

int largs::Parse(int argc, char* argv[])
{
    
    ArgsOk = true;
    
    /* Definición de la línea de comandos. El valor por defecto del número de
     * pulso es 0. */
    po::options_description desc("USAGE");
    desc.add_options()
        ("pulse,p", po::value<int>(&PulseNumber)->default_value(0), "Pulse number to plot")
        ("input_file_name,i", po::value< std::vector<std::string> >(), ".paa input file name")
        ("output_file_name,o", po::value< std::vector<std::string> >(), ".pdf output file name")
        ;

    po::variables_map vm;
    store(po::command_line_parser(argc, argv).
            options(desc).run(), vm);
    notify(vm);

    if (vm.count("input_file_name"))
        InputFileName = new std::string( vm["input_file_name"].as< std::vector<std::string> >()[0] );
    else
    {
        std::cout << "No Input file name" << std::endl;
        InputFileName = 0;
        ArgsOk = false;
    }

    if (vm.count("output_file_name"))
        OutputFileName = new std::string( vm["output_file_name"].as< std::vector<std::string> >()[0] );
    else
    {
        std::cout << "No output file name" << std::endl;
        OutputFileName = 0;
        ArgsOk = false;
    }
    
    if(!ArgsOk)
        std::cout << std::endl << desc << std::endl;

    return ( ArgsOk ? 0 : 1 );
}