/*// Encriptación simple (mejorable)
string Reporte::encriptar(const string& texto) {
    string resultado = texto;
    for (char& c : resultado) {
        c = c + 3; // Desplazamiento simple
    }
    return resultado;
}

string Reporte::desencriptar(const string& texto) {
    string resultado = texto;
    for (char& c : resultado) {
        c = c - 3; // Revertir desplazamiento
    }
    return resultado;
}*/