#include <iostream>
#include <list>
using namespace std;

using uint = unsigned int;

// Pre: 0 <= mes < 12
uint dias_en_mes(uint mes) {
    uint dias[] = {
        // ene, feb, mar, abr, may, jun
        31, 28, 31, 30, 31, 30,
        // jul, ago, sep, oct, nov, dic
        31, 31, 30, 31, 30, 31
    };
    return dias[mes - 1];
}

// Ejercicio 7, 8, 9 y 10

// Clase Fecha

class Fecha{
public:
    Fecha(int mes, int dia);
    int mes();
    int dia();
    void incrementar_dia();
    bool operator==(Fecha o);
private:
    int mes_;
    int dia_;
};

Fecha::Fecha(int mes, int dia):mes_(mes), dia_(dia) {
}
bool Fecha::operator==(Fecha o) {
    return (o.mes()==this->mes() and o.dia() == this->dia());
}
int Fecha::mes() {
    return mes_;
}

int Fecha::dia() {
    return dia_;
}

void Fecha::incrementar_dia() {
    dia_ = dia_ + 1;
    if(dia_> dias_en_mes(mes_)){
        dia_ = 1;
        mes_ = mes_ + 1;
        if(mes_>12){
            mes_ = 1;
        }
    }
}

ostream& operator<<(ostream& os, Fecha f) {
    os <<  f.dia() << "/" << f.mes();
    return os;
}



// Ejercicio 11, 12
class Horario{
public:
    Horario(uint hora, uint min);
    uint hora();
    uint min();
    bool operator==(Horario o);
    bool operator<(Horario h);

private:
    uint hora_;
    uint min_;
};

Horario::Horario(uint hora, uint min): hora_(hora), min_(min) {

}

uint Horario::hora() {
    return hora_;
}

uint Horario::min() {
    return min_;
}

bool Horario:: operator==(Horario o) {
  return this->hora()==o.hora() and this->min()==o.min();
}

bool Horario::operator<(Horario h) {
    return (this->hora()<h.hora() or (this->hora()==h.hora() and this->min()<h.min()));
}

ostream& operator<<(ostream& os, Horario h) {
    os <<  h.hora() << ":" << h.min();
    return os;
}


// Ejercicio 13
class Recordatorio{
public:
    Recordatorio(Fecha, Horario, string);
    Fecha fechaRecordatorio();
    Horario horarioRecordatorio();
    string mensajeRecordatorio();

private:
    Fecha fecha_;
    Horario horario_;
    string mensaje_;
};

Recordatorio::Recordatorio(Fecha f, Horario h, string msj): fecha_(f), horario_(h), mensaje_(msj) {

}

Fecha Recordatorio::fechaRecordatorio() {
    return fecha_;
}

Horario Recordatorio::horarioRecordatorio() {
    return horario_;
}

string Recordatorio::mensajeRecordatorio() {
    return mensaje_;
}

ostream& operator<<(ostream& os, Recordatorio r) {
    os <<  r.mensajeRecordatorio() << " @ " << r.fechaRecordatorio() << " " << r.horarioRecordatorio();
    return os;
}

// Ejercicio 14

// Clase Agenda

class Agenda {
public:
    Agenda(Fecha fecha_inicial);
    void agregar_recordatorio(Recordatorio rec);
    void incrementar_dia();
    list<Recordatorio> recordatorios_de_hoy();
    Fecha hoy();
private:
    Fecha fechaActual_;
    list<Recordatorio> recordatoriosAgendados_;

};

Agenda::Agenda(Fecha fecha_inicial): fechaActual_(fecha_inicial), recordatoriosAgendados_() {

}

void Agenda::agregar_recordatorio(Recordatorio rec) {
    recordatoriosAgendados_.push_back(rec);
}

void Agenda::incrementar_dia() {
    fechaActual_.incrementar_dia();
}

list<Recordatorio> Agenda::recordatorios_de_hoy() {
    list<Recordatorio> res;
    for(Recordatorio r : recordatoriosAgendados_){
        if(r.fechaRecordatorio()==fechaActual_){
            res.push_back(r);
        }
    }
    return res;
}

Fecha Agenda::hoy() {
    return fechaActual_;
}
static bool sortPorHorarios(Recordatorio &r1, Recordatorio &r2)
{
    return r1.horarioRecordatorio() < r2.horarioRecordatorio();
}

ostream& operator<<(ostream& os, Agenda a) {
    os << a.hoy() << endl;
    os << "=====" << endl;
    list<Recordatorio> paraHoy = a.recordatorios_de_hoy();
    paraHoy.sort(sortPorHorarios);
    for(Recordatorio r : paraHoy){

        os <<  r << endl;
    }
    return os;
}
