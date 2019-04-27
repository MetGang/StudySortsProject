# Projekt ASD - Sortowanie

### Użyte algorytmy

QuickSort (ang. sortowanie szybkie) - algorytm rekursywny; stosuje metodę dziel i zwyciężaj, dzieli tablicę na mniejsze części tak, że wszystkie liczby na lewo od punktu podziału są od niego mniejsze, natomiast na prawo - większe. Wydajny dla nieposortowanych kolekcji.

HeapSort (ang. sortowanie przez kopcowanie) - algorytm iteracyjny; tworzy kopiec z kolekcji, a następnie przesuwa korzeń na jej koniec i wyklucza go z algorytmu, proces jest powtarzany do czasu posortowania kolekcji. Wydajność stała - niezależna od stanu posortowania kolekcji.

BubbleSort (ang. sortowanie bąbelkowe) - algorytm iteracyjny; jeden z najprostszych algorytmów sortujących - porównuje sąsiednie elementy i zamienia je kolejnością do czasu aż kolekcja będzie posortowana. Dzięki drobnej optymalizacji algorytmu wydajność rośnie w miarę stopnia posortowania kolekcji.

### Benchmark

Konfiguracja sprzętu:
* Intel Core i3-6006U (2.0GHz, 3MB L3 Cache)
* 8GB RAM DDR4
* 512GB SSD
* System operacyjny Windows 10 Home

Skompilowany za pomocą `gcc (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0` w standardzie C99. Użyto funkcji `rand` pochodzącej z biblioteki standardowej języka C do generowania liczb w tablicy.

**Random** - tablica elementów o losowej kolejności  
**Asc** - tablica posortowana rosnąco  
**Desc** - tablica posortowana malejąco  
**Tricky** - tablica posortowana rosnąco, lecz pierwszy element jest zamieniony miejscem z ostatnim

Ilość elementów w tablicy: 16384

Średni czas dla 10 wykonań:

| Rodzaj | QuickSort | HeapSort | BubbleSort |
| --- | --- | --- | --- |
| Random | 0.006s | 0.858s | 1.402s |
| Asc | 1.253s | 0.851s | 0.000s |
| Desc | 0.348s | 0.850s | 1.256s |
| Tricky | 1.220s | 0.861s | 0.581s |

### Podsumowanie

Jak widać każdy z wybranych algorytmów ma swoje mocne i słabe strony - każdy nadaje się do różnych sytuacji.

QuickSort w większości przypadków wypada lepiej lub nie tak aż znacznie gorzej od pozostałych algorytmów - bardzo dobrze sprawdza się na losowo wygenerowanych kolekcjach.

Jeśli chcemy mieć pewność odnośnie do czasu wykonania sortowania to najlepszym wyborem jest HeapSort. Wykazuje on przyzwoitą i stałą złożoność obliczeniową niezależną od stanu danych wejściowych.

Jeśli natomiast mamy do czynienia z w miarę posortowaną kolekcją możemy użyć lekko zmienionego BubbleSorta, który np. w przypadku całkowicie posortowanej kolekcji działa wręcz natychmiastowo.

Dobrym rozwiązaniem jest zastosowanie algorytmu hybrydowego jak to ma miejsce np. w bibliotece standardowej C++. `std::sort` jest przykładem algorytmu hybrydowego, który łączy w sobie (zazwyczaj) QuickSort, HeapSort oraz InsertionSort. Na początku stosowany jest QuickSort, po osiągnięciu limitu rekurencyjnych wywołań HeapSort, a gdy sortowany podzbiór jest wystarczająco mały - InsertionSort. Dzięki temu połączeniu `std::sort` ma zapewnioną liniowo-logarytmiczną złożoność obliczeniową.
