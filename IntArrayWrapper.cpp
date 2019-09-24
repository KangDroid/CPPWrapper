#include <iostream>
#include <malloc/malloc.h>
#include <ctime>
#include <cstdlib>
using namespace std;

class IntArrayWrapper {
    private:
        int * arr_mov;
        int size;
        int checkVal(int iterator, int randVal) {
            for (int i = 0; i < iterator; i++) {
                if (arr_mov[i] == randVal) {
                    return -1;
                }
            }
            return 0;
        }
    public:
        IntArrayWrapper(int * arr, int length) {
            srand(time(NULL));
            arr_mov = arr;
            this->size = length;
        }
        IntArrayWrapper(int * arr, int length, bool clear) {
            srand(time(NULL));
            arr_mov = arr;
            this->size = length;
            for (int i = 0; i < length; i++) {
                arr_mov[i] = 0;
            }
        }
        void show() {
            cout << "[ ";
            for (int i = 0; i < this->size; i++) {
                cout << arr_mov[i] << (i == (this->size - 1) ? "" : ", ");
            }
            cout << " ]" << endl;
        }
        void show(int st_range, int ed_range) { // st_range index to ed_range index(not ed_range - 1)
            cout << "[ ";
            for (int i = st_range; i < ed_range+1; i++) {
                cout << arr_mov[i] << ((i == ed_range) ? "" : ", ");
            }
            cout << " ]" << endl;            
        }
        void resetValRand(int bound) {
            for (int i = 0; i < this->size; i++) {
                arr_mov[i] = rand() % bound;
            }
        }
        void resetValRand(int bound, bool noOverlap) {
            int randval;
            for (int i = 0; i < this->size; i++) {
                randval = rand() % bound;
                if (checkVal(i, randval) == 0) {
                    arr_mov[i] = randval;
                } else {
                    i--;
                }
            }
        }
        void sort() {
            for (int a = 0; a < this->size; a++) {
                for (int i = 0; i < (this->size) -1; i++) {
                    if (arr_mov[i] > arr_mov[i+1]) {
                        int tmp = arr_mov[i];
                        arr_mov[i] = arr_mov[i+1];
                        arr_mov[i+1] = tmp;
                    }
                }
            }
        }
        void sort(bool upsc) {
            for (int a = 0; a < this->size; a++) {
                for (int i = 0; i < (this->size) -1; i++) {
                    if (arr_mov[i] < arr_mov[i+1]) {
                        swap(i, i+1);
                    }
                }
            }
        }
        void swap(int first_index, int second_index) {
            int tmp = arr_mov[first_index];
            arr_mov[first_index] = arr_mov[second_index];
            arr_mov[second_index] = tmp;
        }
        int *duplicateArray() {
            int *tmp = new int[this->size];
            for (int i = 0; i < this->size; i++) {
                tmp[i] = arr_mov[i];
            }
            return tmp;
        }
};

int main(void) {
    int *array = new int[10], *array_dup;
    IntArrayWrapper test(array, 10, true);
    test.resetValRand(100, true);
    test.sort();
    test.show();

    array_dup = test.duplicateArray();
    IntArrayWrapper tat(array_dup, 10);
    tat.show();


    delete[] array_dup;
    delete[] array;
    return 0;
}