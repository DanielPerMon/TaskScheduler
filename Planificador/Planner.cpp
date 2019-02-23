#include "pch.h"
#include "Planner.h"


Planner::Planner()
{
	contador = 0;
	numProcesos = 0;
	canales = 0;
}

Planner::Planner(uint32 &&size, uint32&& newCanales): numProcesos(size), canales(newCanales)
{
	Tabla.reserve(size);
	Lista.reserve(size);
	contador = 0;
}

void Planner::addProceso(Proceso nuevo)
{
	vector<Proceso>::iterator i;
	i = Tabla.end();
	this->Tabla.insert(i, nuevo);
}

void Planner::llenaLista(uint32 &tiempo)
{
	for (vector<Proceso>::iterator i = Tabla.begin(); i != Tabla.end(); ++i) {
		if (i->getLlegada() == 0) {
			Lista.push_back(*i);
		}
	}
}

bool Planner::isEmpty()
{
	return Lista.size() == 0;
}

void Planner::printLista()
{
	for (vector<Proceso>::iterator i = Lista.begin(); i != Lista.end(); ++i) {
		i->print();
		cout << endl;
	}
}

void Planner::printTabla()
{
	for (vector<Proceso>::iterator i = Tabla.begin(); i != Tabla.end(); ++i) {
		i->print();
		cout << endl;
	}
}

void Planner::Lista_ordenaPEASC()
{
	Proceso temp;
	for (uint32 i = 0; i < Lista.size(); ++i) {
		for (uint32 j = i; j < Lista.size(); ++j) {
			if (Lista[j].comparacionPEASC(Lista[i])) {
				temp = Lista[j];
				Lista[j] = Lista[i];
				Lista[i] = temp;
			}
		}
	}
}

void Planner::Lista_ordenaEPASC()
{
	Proceso temp;
	for (uint32 i = 0; i < Lista.size(); ++i) {
		for (uint32 j = i; j < Lista.size(); ++j) {
			if (Lista[j].comparacionEPASC(Lista[i])) {
				temp = Lista[j];
				Lista[j] = Lista[i];
				Lista[i] = temp;
			}
		}
	}
}

void Planner::Lista_ordenaPEDESC()
{
	Proceso temp;
	for (uint32 i = 0; i < Lista.size(); ++i) {
		for (uint32 j = i; j < Lista.size(); ++j) {
			if (Lista[j].comparacionPEDESC(Lista[i])) {
				temp = Lista[j];
				Lista[j] = Lista[i];
				Lista[i] = temp;
			}
		}
	}
}

void Planner::Lista_ordenaEPDESC()
{
	Proceso temp;
	for (uint32 i = 0; i < Lista.size(); ++i) {
		for (uint32 j = i; j < Lista.size(); ++j) {
			if (Lista[j].comparacionEPDESC(Lista[i])) {
				temp = Lista[j];
				Lista[j] = Lista[i];
				Lista[i] = temp;
			}
		}
	}
}

bool Planner::keepExecuting()
{
	for (vector<Proceso>::iterator i = Tabla.begin(); i != Tabla.end(); ++i) {
		if (i->getUejecucion() != 0) {
			return true;
		}
	}
	return false;
}

void Planner::ejecuta()
{
	for (vector<Proceso>::iterator i = Lista.begin(); i != Lista.end(); ++i) {
		if (i->getUejecucion() > 0) {
			i->ejecuta();
		} 
	}
}

void Planner::eliminaCeros(uint32& Fin)
{
	for (vector<Proceso>::iterator i = Lista.begin(); i != Lista.end(); ++i) {
		if (i->getUejecucion() == 0) {
			for (vector<Proceso>::iterator it = Tabla.begin(); it != Tabla.end(); ++it) {
				if (*i == *it) {
					it->agregaTiempoFinal(Fin);
					it->setTiempoFinal();
				}
			}
			Lista.erase(Lista.remove(Lista.begin(), Lista.end(),); //ARREGLAR EXCEPCION FUERA DE RANGO
		}
	}
}

void Planner::agregaListaMonotarea(uint32 &i)
{
	for (vector<Proceso>::iterator it = Tabla.begin(); it != Tabla.end(); ++it) {
		if (it->getLlegada() == i) {
			Lista.insert(Lista.end(), *it);
		}
	}
}

void Planner::runMonotarea()
{
	uint32 uExe = 0;
	while (keepExecuting()) {
		eliminaCeros(uExe);
		agregaListaMonotarea(uExe);
		Lista_ordenaPEASC();
		ejecuta();
		++uExe;
	}
}



Planner::~Planner()
{
}
