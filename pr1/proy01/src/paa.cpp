/* 
 * paa.cpp: Implementación de una clase para manejo de
 * archivos .paa provenientes del software
 * Pulse Acquire Tools para Red Pitaya. 
 * 
 * Héctor Pérez, marzo 2021.
 * 
 * Para el curso de Laboratorio Avanzado
 * ECFM - USAC
 * 
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>

#include "paa.hpp"

paa_file::paa_file()
{
    name = 0;
    ps = 0;
    pc = 0;
    tl = 0;

}

paa_file::paa_file(std::string fileName)
{
    name = 0;
    ps = 0;
    pc = 0;
    tl = 0;
    
    open(fileName);

}

paa_file::~paa_file()
{
    PAAFile.close();
    delete name;
}

int paa_file::open(std::string fileName)
{
    if(!name)
        name = new std::string(fileName);
    else
    {
        std::cout << "File: " << *name << " already assosiated with this object. Not opening " << fileName << std:: endl;
        return 1;
    }

    PAAFile.open(fileName.c_str(), std::ios::in | std::ios::binary );
    
    if(!PAAFile.is_open())
    {
        std::cout << "Error openning file: " << fileName << std::endl;
        delete name;
        name = 0;
        return 1;
    }

    char ReadBuffer[512];

    PAAFile.getline(ReadBuffer,8);

    if( std::strcmp(ReadBuffer,"PAA 01") != 0 )
    {
        std::cout << "Invalid file: " << fileName << ". PAA v0.1 file expected."<< std::endl;
        delete name;
        name = 0;
        return 1;
    }

    std::cout   << "==================================================" << std::endl
                << *name << std::endl << std::endl;

    PAAFile.seekg(8);
    PAAFile.getline(ReadBuffer,512);
    std::cout << ReadBuffer << std::endl;
    PAAFile.getline(ReadBuffer,512);
    std::cout << ReadBuffer << std::endl;
    PAAFile.getline(ReadBuffer,512);
    std::cout << ReadBuffer << std::endl;
    PAAFile.getline(ReadBuffer,512);
    std::cout << ReadBuffer << std::endl;
    PAAFile.getline(ReadBuffer,512);
    std::cout << ReadBuffer << std::endl;

    std::cout << std::endl;

    PAAFile.seekg(524);
    PAAFile.read( (char*)&ps, 4);
    std::cout << "Points per pulse: " << ps << std::endl;
    PAAFile.read( (char*)&pc, 4);
    std::cout << "Pulses in this file: " << pc << std::endl;
    PAAFile.read( (char*)&tl, 4);
    std::cout << "Threshold level: " << tl << std::endl;

    std::cout   << "==================================================" << std::endl;

    

    return 0;

}

std::vector<int> *paa_file::GetPulse(unsigned int pulseNumber)
{
    if (!name)
    {
        std::cout << "No file associated" << std::endl;
        return 0;
    }
    
    if( ( pulseNumber < 0 ) || ( pulseNumber > (pc-1) ))
    {
        std::cout << "Error: Bad pulse number" << std::endl;
        return 0;
    }
    
    uint32_t offset = 640 + 2*ps*pulseNumber;
    PAAFile.seekg( offset );
    std::vector<int> *pulse_data_v = new std::vector<int>;
    uint16_t ipoint;
    for( int i = 0 ; i < ps ; i++ )
    {
        PAAFile.read( (char*)&ipoint, 2);
        if( ipoint > 8191 )
            pulse_data_v->push_back( ipoint - 16384 );
        else
            pulse_data_v->push_back( ipoint );
    }

    return pulse_data_v;

}