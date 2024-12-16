#include <bits/stdc++.h>
#include <graphics.h>
#include <conio.h>
#include <pqxx/pqxx>

using namespace std;

pqxx::connection localConnection(
        "dbname=postgres user=dboper password=dboper@321 host=120.46.71.168 port=26000 options='-c client_encoding=UTF8'");
pqxx::connection cloudConnection(
        "dbname=SMUMS057 user=dboper password=dboper@321 host=120.46.71.168 port=26000 options='-c client_encoding=UTF8'");
pqxx::result res;

int main() {

}