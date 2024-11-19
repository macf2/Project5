#include "Cat.hpp"
#include "OpenAddressing.h"
#include "SeparateChaining.h"
#include <fstream>
#include <sstream>

/* Examples of getKey functions
 *
 * If your unique attribute is a string:
 * string getLecturerName(Lecturer lec) {
 *     return lec.getName();
 * }
 *
 * If your unique attribute is not a string:
 * string getEmployeeID(Employee e) {
 *     return to_string(e.getID());
 * }
 *
 * If you only have one unique field in your class,
 * concatenate it with another field for your second key:
 * string getLecturerClassName(Lecturer lec) {
 *     return to_string(lec.getClass1()) + lec.getName();
 * }
 * */

// Stuff from project 1
std::vector<Cat> project1(char **ppdata) {
        FILE *pfile = fopen("cats_dataset.csv", "r");
        fseek(pfile, 0, SEEK_END);
        long szfile = ftell(pfile);
        rewind(pfile);
        char *pdata = (char *)malloc(szfile + 1);
        pdata[szfile] = '\0';
        fread(pdata, szfile, 1, pfile);

        std::vector<Cat> cats;

        while (*pdata++ != '\n')
                ;

        while (*pdata != '\0') {
                uint32_t i = atoi(pdata);

                while (*pdata++ != ',')
                        ;

                char *pbreed = pdata;

                while (*pdata++ != ',')
                        ;
                pdata[-1] = '\0';

                uint32_t age = atoi(pdata);

                while (*pdata++ != ',')
                        ;

                uint32_t weight = atoi(pdata);

                while (*pdata++ != ',')
                        ;

                uint32_t idx_color = pdata - pbreed;

                while (*pdata++ != ',')
                        ;
                pdata[-1] = '\0';

                uint32_t idx_gender = pdata - pbreed;

                while (*pdata++ != '\n')
                        ;
                pdata[-1] = '\0';

                cats.emplace_back(
                    Cat(i, pbreed, age, weight, idx_color, idx_gender));
        }

        *ppdata = pdata;
        return cats;
}

std::string getCatKeyA(Cat const &cat) {
        std::string breed = cat.get_pbreed();
        std::string id = std::to_string(cat.get_id());
        return breed + id;
}

std::string getCatKeyB(Cat const &cat) {
        std::string color = cat.get_pcolor();
        std::string id = std::to_string(cat.get_id());
        return color + id;
}

void writeCollisionsToCSV(std::ofstream &file, int *pcollisions,
                          int ncollisions) {
        for (uint32_t i = 0; i < ncollisions - 1; i++) {
                file << pcollisions[i];
                file << ", ";
        }
        file << pcollisions[ncollisions - 1];
        file << std::endl;
}

int main() {
        char *ppdata = NULL;
        std::vector<Cat> cats = project1(&ppdata);

        // Separate chaining with getCatKeyA
        SeparateChaining<Cat> sca0(1001);
        SeparateChaining<Cat> sca1(2000);
        SeparateChaining<Cat> sca2(3000);
        SeparateChaining<Cat> sca3(10000);
        SeparateChaining<Cat> sca4(100000);

        // Separate chaining with getCatKeyB
        SeparateChaining<Cat> scb0(1001);
        SeparateChaining<Cat> scb1(2000);
        SeparateChaining<Cat> scb2(3000);
        SeparateChaining<Cat> scb3(10000);
        SeparateChaining<Cat> scb4(100000);

        // QuadraticProbing with getCatKeyA
        QuadraticProbing<Cat> qpa0(1001);
        QuadraticProbing<Cat> qpa1(2000);
        QuadraticProbing<Cat> qpa2(3000);
        QuadraticProbing<Cat> qpa3(10000);
        QuadraticProbing<Cat> qpa4(100000);

        // QuadraticProbing with getCatKeyB
        QuadraticProbing<Cat> qpb0(1001);
        QuadraticProbing<Cat> qpb1(2000);
        QuadraticProbing<Cat> qpb2(3000);
        QuadraticProbing<Cat> qpb3(10000);
        QuadraticProbing<Cat> qpb4(100000);

        std::ofstream sca_file("graphs/separate_chaining/a.csv");
        sca_file << "tableSize = 1001, tableSize = 2000, tableSize = 3000, "
                    "tableSize = 10000, tableSize = 100000\n";
        std::ofstream scb_file("graphs/separate_chaining/b.csv");
        scb_file << "tableSize = 1001, tableSize = 2000, tableSize = 3000, "
                    "tableSize = 10000, tableSize = 100000\n";
        std::ofstream qpa_file("graphs/quadratic_probing/a.csv");
        qpa_file << "tableSize = 1001, tableSize = 2000, tableSize = 3000, "
                    "tableSize = 10000, tableSize = 100000\n";
        std::ofstream qpb_file("graphs/quadratic_probing/b.csv");
        qpb_file << "tableSize = 1001, tableSize = 2000, tableSize = 3000, "
                    "tableSize = 10000, tableSize = 100000\n";

        for (Cat const &c : cats) {
                // Separate chaining with getCatKeyA
                int psca_collisions[] = {0, 0, 0, 0, 0};
                sca0.insert(getCatKeyA(c), c, &psca_collisions[0]);
                sca1.insert(getCatKeyA(c), c, &psca_collisions[1]);
                sca2.insert(getCatKeyA(c), c, &psca_collisions[2]);
                sca3.insert(getCatKeyA(c), c, &psca_collisions[3]);
                sca4.insert(getCatKeyA(c), c, &psca_collisions[4]);

                // Write separate chaining collisions for getCatKeyA to the CSV
                writeCollisionsToCSV(sca_file, psca_collisions, 5);

                // Separate chaining with getCatKeyB
                int pscb_collisions[] = {0, 0, 0, 0, 0};
                scb0.insert(getCatKeyB(c), c, &pscb_collisions[0]);
                scb1.insert(getCatKeyB(c), c, &pscb_collisions[1]);
                scb2.insert(getCatKeyB(c), c, &pscb_collisions[2]);
                scb3.insert(getCatKeyB(c), c, &pscb_collisions[3]);
                scb4.insert(getCatKeyB(c), c, &pscb_collisions[4]);

                // Write separate chaining collisions for getCatKeyB to the CSV
                writeCollisionsToCSV(scb_file, pscb_collisions, 5);

                // QuadraticProbing with getCatKeyA
                int pqpa_collisions[] = {0, 0, 0, 0, 0};
                qpa0.insert(getCatKeyA(c), c, &pqpa_collisions[0]);
                qpa1.insert(getCatKeyA(c), c, &pqpa_collisions[1]);
                qpa2.insert(getCatKeyA(c), c, &pqpa_collisions[2]);
                qpa3.insert(getCatKeyA(c), c, &pqpa_collisions[3]);
                qpa4.insert(getCatKeyA(c), c, &pqpa_collisions[4]);

                // Write quadratic probing collisions for getCatKeyA to the CSV
                writeCollisionsToCSV(qpa_file, pqpa_collisions, 5);

                // QuadraticProbing with getCatKeyB
                int pqpb_collisions[] = {0, 0, 0, 0, 0};
                qpb0.insert(getCatKeyB(c), c, &pqpb_collisions[0]);
                qpb1.insert(getCatKeyB(c), c, &pqpb_collisions[1]);
                qpb2.insert(getCatKeyB(c), c, &pqpb_collisions[2]);
                qpb3.insert(getCatKeyB(c), c, &pqpb_collisions[3]);
                qpb4.insert(getCatKeyB(c), c, &pqpb_collisions[4]);

                // Write quadratic probing collisions for getCatKeyB to the CSV
                writeCollisionsToCSV(qpb_file, pqpb_collisions, 5);
        }

        // Print sizes for QuadraticProbing with getCatKeyA
        std::cout << qpa0.getTableSize() << std::endl;
        std::cout << qpa1.getTableSize() << std::endl;
        std::cout << qpa2.getTableSize() << std::endl;
        std::cout << qpa3.getTableSize() << std::endl;
        std::cout << qpa4.getTableSize() << std::endl;

        // Print sizes for QuadraticProbing with getCatKeyB
        std::cout << qpb0.getTableSize() << std::endl;
        std::cout << qpb1.getTableSize() << std::endl;
        std::cout << qpb2.getTableSize() << std::endl;
        std::cout << qpb3.getTableSize() << std::endl;
        std::cout << qpb4.getTableSize() << std::endl;

        sca_file.close();
        scb_file.close();
        qpa_file.close();
        qpb_file.close();

        free((void *)*ppdata);
        return 0;
}
