/*1. Вернуть значение бита в числе N по его номеру K.
Позиции битов нумеруются с 0.

Необходимо использование битовых операций.
Использование арифметических операций запрещено.*/

//#include <iostream>
//#include <cassert>
//
////Функция поиска значения бита
//int BitValue(unsigned int N, unsigned int K) {
//    return (N >> K) & 1;
//}
//
//int main() {
//    unsigned int N, K;
//    std::cin >> N >> K;
//    assert(K <= 31);
//    std::cout << BitValue(N, K) << std::endl;
//    return 0;
//}



/* 2. Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. Для каждого элемента массива B[i] найдите минимальный индекс элемента массива A[k], ближайшего по значению к B[i]. n ≤ 110000, m ≤ 1000. Время работы поиска для каждого элемента B[i]: O(log(k)).
 
*/

//#include <iostream>
//#include <cassert>
//using namespace std;
//
////Экспоненциальный поиск
//int ExpSearch(int *arr, int target, int n) {
//    if (arr[0] >= target) {
//        return 0;
//    }
//    else if (arr[1] >= target) {
//        return 1;
//    }
//    int pow = 1; //степени двойки
//    while (pow < n and arr[pow] < target) {
//        pow *= 2;
//    }
//    return pow;
//}
//
////Бинарный поиск, при этом target будет лежать на интервале [left, left + 1]
//int BinarySearch(int *arr, int target, int n, int left, int right) {
//    while (left + 1 < right) {
//        int mid = (right + left) / 2;
//        if (arr[mid] < target) {
//            left = mid;
//        }
//        else if (arr[mid] > target) {
//            right = mid;
//        }
//        else {
//            return mid;
//        }
//    }
//    return left;
//}
//
////Ввод массива
//void inputArr(int *arr, int n) {
//    for (int i = 0; i < n; i++) {
//        cin >> arr[i];
//    }
//}
//
//int main() {
//    int n;
//    cin >> n;
//    int* A = new int[n]();
//    inputArr(A, n);
//
//    int m;
//    cin >> m;
//    int* B = new int[m]();
//    inputArr(B, m);
//
//    for (int i = 0; i < m; i++) {
//        int target = B[i];
//        int res1 = ExpSearch(A, target, n);
//        int res2 = BinarySearch(A, target, n, res1 / 2, min(res1, n));
//
//        if (target - A[res2] <= A[res2 + 1] - target) {
//            cout << res2 << " ";
//        }
//        else {
//            cout << min(res2 + 1, n - 1) << " ";
//        }
//    }
//    cout << endl;
//    return 0;
//}


/*3. Реализовать очередь с помощью двух стеков. Использовать стек, реализованный с помощью динамического буфера.
 
 Обрабатывать команды push back и pop front.

*/

//#include <iostream>
//#include <cassert>
//using namespace std;
//
///*Классический Стек с методами pop, push, isEmpty. Методы isFull и resize позволяют динамически
//обновлять размер стека, если изначально стек был длины 0, он станет длины 1, дальше с каждым переполнением
// будет увеличение размера стека в 2 раза*/
//class Stack {
//private:
//    int *arr;
//    int top;
//    int capacity;
//    void resize();
//
//    //Запрет копирования и присваивания
//    Stack(const Stack&) = delete;
//    Stack& operator=(const Stack&) = delete;
//public:
//    Stack(int len);
//
//    int pop();
//    void push(int new_data);
//    bool isEmpty();
//    bool isFull();
//
//    ~Stack();
//};
//
//Stack::Stack(int len) {
//    arr = new int[len];
//    top = -1;
//    capacity = len;
//}
//
//void Stack::resize() {
//    if (capacity == 0) {
//        capacity = 1;
//        return;
//    }
//    int *newArr = new int[capacity * 2];
//    for (int i = 0; i < capacity; i++) {
//        newArr[i] = arr[i];
//    }
//    capacity *= 2;
//    delete[] arr;
//    arr = newArr; //присваиваем переменной arr указатель на наш новый расширенный стек
//}
//
//int Stack::pop() {
//    if (isEmpty()) {
//        return -1;
//    }
//    return arr[top--];
//}
//
//void Stack::push(int new_data) {
//    if (isFull()) {
//        resize();
//    }
//    arr[++top] = new_data;
//}
//
//bool Stack::isEmpty() {
//    if (top == -1) {
//        return true;
//    }
//    return false;
//}
//
//bool Stack::isFull() {
//    if (top == capacity - 1) {
//        return true;
//    }
//    return false;
//}
//
//Stack::~Stack() {
//    delete[] arr;
//}
//
///*Реализация очереди на двух стеках. Основной алгоритм состоит в том, что enqueue(добавление элемента в
// конец) мы всегда выполняем для stack1, dequeue(возврат и удаление первого элемента очереди) наоборот всегда
// выполняем для stack2, при это если stack2 пуст, с помощью последовательных push и pop перекидываем все
// элементы из stack1 в stack2, таким образом в stack2 они будут в обратном порядке, что и обеспечит верный
// порядок извлечения из очереди*/
//class Queue {
//private:
//    Stack stack1;
//    Stack stack2;
//public:
//    Queue(int len);
//
//    void enqueue(int new_data);
//    int dequeue();
//    bool isEmpty();
//
//    ~Queue();
//
//    //Запрет копирования и присваивания
//    Queue(const Queue&) = delete;
//    Queue& operator=(const Queue&) = delete;
//};
//
//Queue::Queue(int len) : stack1(len), stack2(len) {
//
//}
//
//void Queue::enqueue(int new_data) {
//    stack1.push(new_data);
//}
//
//int Queue::dequeue() {
//
//    if (stack2.isEmpty()) {
//        while (not stack1.isEmpty()) {
//            int elem = stack1.pop();
//            stack2.push(elem);
//        }
//    }
//    return stack2.pop();
//}
//
//bool Queue::isEmpty() {
//    if (stack1.isEmpty() and stack2.isEmpty()) {
//        return true;
//    }
//    return false;
//}
//
//Queue::~Queue() {
//
//}
//
//bool proc(int n) {
//    Queue queue(0);
//    bool res = true;
//    for (int i = 0; i < n; ++i) {
//        int command = 0;
//        int data = 0;
//        cin >> command >> data;
//        if (command == 2) {
//            if (queue.isEmpty()) {
//                res = res and (data == -1);
//            }
//            else {
//                res = res and (data == queue.dequeue());
//            }
//        }
//        else if (command == 3) {
//            queue.enqueue(data);
//        }
//        else {
//            assert(false);
//        }
//    }
//    return res;
//}
//
//int main() {
//    int n;
//    cin >> n;
//    cout << (proc(n) ? "YES" : "NO") << endl;
//}


/*4. Имеется лог-файл, в котором хранятся пары для N пользователей (Идентификатор пользователя, посещаемость сайта).
 Напишите программу, которая выбирает K пользователей, которые чаще других заходили на сайт, и выводит их в порядке возрастания посещаемости. Количество заходов и идентификаторы пользователей не повторяются.
*/


/*5. Группа людей называется современниками если был такой момент, когда они могли собраться вместе. Для этого в этот момент каждому из них должно было  уже исполниться 18 лет, но ещё не исполниться 80 лет.
 Дан список Жизни Великих Людей. Необходимо получить максимальное количество современников. В день 18летия человек уже может принимать участие в собраниях, а в день 80летия и в день смерти уже не может.
 Замечание. Человек мог не дожить до 18-летия, либо умереть в день 18-летия. В этих случаях принимать участие в собраниях он не мог.
*/

//#include <iostream>
//#include <cstring>
//using namespace std;
//
//struct Date {
//    int day;
//    int month;
//    int year;
//    int type; //+1 если испольнилось 18 и не умер, -1 если умер или исполнилось 80
//
//    Date() : year(0), month(0), day(0), type(0) {}
//
//    Date(int d, int m, int y, int t) : day(d), month(m), year(y), type(t) {}
//
//    bool operator<(const Date& other) const {
//        if (year != other.year) return year < other.year;
//        if (month != other.month) return month < other.month;
//        if (day != other.day) return day < other.day;
//        return type < other.type; //сначла смерти при прочих равных
//    }
//
//};
//
//template <typename T>
//struct DefaultComparator{
//    bool operator()(const T& l, const T& r) const{
//        return l < r;
//    }
//};
//
//template <typename T, typename Comparator = DefaultComparator<T>>
//void Merge(T* leftHalf, int sizeLeft, T* rightHalf, int sizeRight, T* c, Comparator comp = Comparator()){
//    int leftPoint = 0;
//    int rightPoint = 0;
//    int ind = 0;
//    while (leftPoint < sizeLeft or rightPoint < sizeRight) {
//        if (rightPoint < sizeRight and (comp(rightHalf[rightPoint], leftHalf[leftPoint]) or leftPoint >= sizeLeft)) {
//            c[ind++] = rightHalf[rightPoint++];
//        }
//        else {
//            c[ind++] = leftHalf[leftPoint++];
//        }
//    }
//}
//template<typename T> void MergeSort(T* arr, int size) {
//    if (size <= 1) {
//        return;
//    }
//    int leftSize = size / 2;
//    int rightSize = size - leftSize;
//    MergeSort(arr, leftSize);
//    MergeSort(arr + leftSize, rightSize);
//    T* c = new T[size];
//    Merge(arr, leftSize, arr + leftSize, rightSize, c);
//    memcpy(arr, c, sizeof(T) * size);
//    delete[] c;
//}
//
//void proc(Date* dates, int n, int &count) {
//    for (int i = 0; i < n; ++i) {
//        int d1, m1, y1, d2, m2, y2;
//        cin >> d1 >> m1 >> y1 >> d2 >> m2 >> y2;
//        int start = y1 + 18;
//        int end = y1 + 80;
//        if (start < y2 or (start == y2 and m1 < m2) or (start == y2 and m1 == m2 and d1 < d2)) {
//            dates[count++] = Date(d1, m1, start, 1);
//            if (end < y2 or (end == y2 and m1 < m2) or (end == y2 and m1 == m2 and d1 < d2)) {
//                dates[count++] = Date(d1, m1, end, -1);
//            }
//            else {
//                dates[count++] = Date(d2, m2, y2, -1);
//            }
//        }
//    }
//}
//
//int solution(int n) {
//    Date* dates = new Date[n * 2];
//    int count = 0;
//    proc(dates, n, count);
//    MergeSort(dates, count);
//    int cur = 0;
//    int maximum = 0;
//    for (int i = 0; i < count; ++i) {
//        cur += dates[i].type;
//        maximum = max(maximum, cur);
//    }
//    delete[] dates;
//    return maximum;
//}
//
//int main() {
//    int n;
//    cin >> n;
//    cout << solution(n) << endl;
//    return 0;
//}



/*4. Имеется лог-файл, в котором хранятся пары для N пользователей (Идентификатор пользователя, посещаемость сайта).
 Напишите программу, которая выбирает K пользователей, которые чаще других заходили на сайт, и выводит их в порядке возрастания посещаемости.
 Количество заходов и идентификаторы пользователей не повторяются.
*/

//#include <iostream>
//#include <cstring>
//using namespace std;
//
//template <typename T>
//struct DefaultComparator{
//    bool operator()(const T& l, const T& r) const{
//        return l < r;
//    }
//};
//
//struct User {
//    int id;
//    int counter;
//
//    User() : id(0), counter(0) {}
//    User(int i, int c) : id(i), counter(c) {}
//
//    bool operator<(const User& other) const {
//        return counter < other.counter;
//    }
//};
//
//template <typename T, typename Comparator = DefaultComparator<T>>
//class Heap {
//private:
//    T* buffer;
//    int size_buff;
//    int count;
//
//    Comparator comp;
//    //Восстанавливает упорядоченность, проталкивая элемент вниз(после удаления)
//    void siftDown();
//    //Восстанавливает упорядоченность, проталкивая элемент наверх(после добавления)
//    void siftUp();
//    //Расширение размера буфера
//    void resize();
//public:
//    Heap();
//
//    // Добавить элемент в кучу за O(log(n))
//    void push(const T& element);
//    // Удалить максимум из кучи за O(log(n))
//    void pop();
//    // Посмотреть значение максимума в куче за O(1)
//    const T& top() const;
//    // Размер кучи
//    int size() const;
//
//
//    Heap(const Heap&) = delete;
//    Heap(const Heap&&) = delete;
//
//    Heap &operator=(const Heap &) = delete;
//    Heap &operator=(const Heap &&) = delete;
//
//    ~Heap();
//};
//
//template <typename T, typename Comparator>
//Heap<T, Comparator>::Heap() : buffer(new T[1]), size_buff(1), count(0), comp(Comparator()) {}
//
//template <typename T, typename Comparator>
//void Heap<T, Comparator>::push(const T& element) {
//    if (count == size_buff) resize();
//    buffer[count++] = element;
//    siftUp();
//}
//
//template <typename T, typename Comparator>
//void Heap<T, Comparator>::pop() {
//    buffer[0] = buffer[count - 1];
//    --count;
//    siftDown();
//}
//
//template <typename T, typename Comparator>
//const T& Heap<T, Comparator>::top() const {
//    return buffer[0];
//}
//
//template <typename T, typename Comparator>
//int Heap<T, Comparator>::size() const {
//    return count;
//}
//
//template <typename T, typename Comparator>
//Heap<T, Comparator>::~Heap() {
//    delete[] buffer;
//}
//
//template <typename T, typename Comparator>
//void Heap<T, Comparator>::siftDown() {
//    int ind = 0;
//    while (ind < count) {
//        int left = 2 * ind + 1;
//        int right = 2 * ind + 2;
//        int largest = ind;
//
//        if (left < count and comp(buffer[ind], buffer[left])) largest = left;
//        if (right < count and comp(buffer[largest], buffer[right])) largest = right;
//        if (largest != ind) {
//            swap(buffer[largest], buffer[ind]);
//            ind = largest;
//        }
//        else break;
//    }
//}
//
//template <typename T, typename Comparator>
//void Heap<T, Comparator>::siftUp() {
//    int ind = count - 1;
//    while (ind > 0) {
//        int parent = (ind - 1) / 2;
//        if (comp(buffer[parent], buffer[ind])) {
//            swap(buffer[parent], buffer[ind]);
//            ind = parent;
//        }
//        else break;
//    }
//}
//
//template <typename T, typename Comparator>
//void Heap<T, Comparator>::resize() {
//    T *new_buff = new T[size_buff * 2];
//    for (int i = 0; i < size_buff; ++i) {
//        new_buff[i] = buffer[i];
//    }
//    size_buff *= 2;
//    delete[] buffer;
//    buffer = new_buff;
//}
//
//
//void solution(int n, int k, int* ans) {
//    Heap <User> myHeap;
//    for (int i = 0; i < n; ++i) {
//        User user;
//        cin >> user.id >> user.counter;
//        myHeap.push(user);
//    }
//    for (int i = 0; i < k; ++i) {
//        ans[i] = myHeap.top().id;
//        myHeap.pop();
//    }
//}
//
//int main() {
//    int n, k;
//    cin >> n >> k;
//    if (k > n) k = n; // для случая, когда мы не можем взять K пользователей
//    int* ans = new int[k];
//    solution(n, k, ans);
//    for (int i = k - 1; i > -1; --i) {
//        cout << ans[i];
//        if (i > 0) cout << " "; else cout << endl;
//    }
//
//    delete[] ans;
//
//    return 1;
//}




/*РК1*/


/*1.Дан отсортированный по возрастанию массив попарно различных целых чисел A[0..n-1]. На вход также подается некоторое целое число k. Необходимо вернуть индекс элемента k в массиве A, если он там присутствует, либо вернуть позицию, куда его следовало бы вставить, чтобы массив остался отсортированным.
 
 Требование: сложность O(logN)

*/

//#include <iostream>
//#include <cstring>
//using namespace std;
//
//
//int BinarySearch(int *arr, int target, int n, int left, int right) {
//    while (left + 1 < right) {
//        int mid = (left + right) / 2;
//        if (arr[mid] < target) left = mid;
//        else if (arr[mid] > target) right = mid;
//        else return mid;
//    }
//    return right;
//}
//
//int main() {
//    int n;
//    cin >> n;
//    int* arr = new int[n];
//    for (int i = 0; i < n; ++i) {
//        cin >> arr[i];
//    }
//    int k;
//    cin >> k;
//    int idx = BinarySearch(arr, k, n, -1, n);
//    delete[] arr;
//    cout << idx << endl;
//}

/*3. На склад привезли много пустых ящиков. Все ящики пронумерованы по порядку поступления от 0.
 Известно, что их все можно сложить один в один (то есть так, что каждый следующий помещается в предыдущий). Один ящик можно вложить в другой, если его можно перевернуть так, что размеры одного ящика по всем осям станут строго меньше размеров другого ящика по соответствующим осям.
 Требуется определить, в какой последовательности они будут вложены друг в друга. Вывести номера ящиков.
 Для сортировки точек реализуйте алгоритм сортировки вставками.
 Максимальное кол-во 10000.*/


//#include <iostream>
//#include <cstring>
//using namespace std;
//
//
//struct Box {
//    int x;
//    int y;
//    int z;
//    int ind;
//
//
//
//    Box(): x(0), y(0), z(0), ind(0) {}
//    Box(int leng, int width, int height, int i) : x(leng), y(width), z(height), ind(i) {}
//
//
//    bool operator<(const Box& other) const {
//        if (x < other.x and y < other.y and z < other.z) return true;
//        else return false;
//    }
//};
//
//
//void insertionSort(Box *arr, int n) {
//    for (int i = 1; i < n; ++i) {
//        int j = i - 1;
//        while (arr[j + 1] < arr[j] and j >= 0) {
//            swap(arr[j], arr[j + 1]);
//            --j;
//        }
//    }
//}
//
//int main() {
//    int n;
//    cin >> n;
//    Box* arr = new Box[n];
//    for (int i = 0; i < n; ++i) {
//        int x, y, z;
//        cin >> x >> y >> z;
//        if (x > y) swap(x, y);
//        if (x > z) swap(x, z);
//        if (y > z) swap(y, z);
//        Box box_now = Box(x, y, z, i);
//        arr[i] = box_now;
//    }
//    insertionSort(arr, n);
//    for (int i = 0; i < n; ++i) {
//        cout << arr[i].ind << " ";
//    }
//    cout << endl;
//    delete[] arr;
//}

/*2. ВНИМАНИЕ! Для решения данной задачи нужно использовать структуру данных стек!
 
 Пара слов называется стековой анаграмой, если одно слово можно получить из другого, проведя последовательность стековых операций с его буквами (взять очередную букву исходного слова и поместить ее в стек; взять букву из стека и добавить ее в конец выходного слова). Для заданной пары слов требуется определить, можно ли выполнить последовательность стековых операций, переводящую первое слово во второе. Все буквы в слове различные. Длина анаграммы ≤ 10000.
 НЕ ДОПИСАНА, НЕ УВЕРЕН В ПРАВИЛЬНОСТИ!!!!!!

*/


//#include <iostream>
//#include <string>
//
//using namespace std;
//
//class Stack {
//private:
//    int *arr;
//    int top;
//    int capacity;
//    void resize();
//
//    //Запрет копирования и присваивания
//    Stack(const Stack&) = delete;
//    Stack& operator=(const Stack&) = delete;
//public:
//    Stack(int len);
//
//    int pop();
//    void push(int new_data);
//    bool isEmpty();
//    bool isFull();
//
//    const int& peeck() const{
//        return top;
//    }
//
//    int size() {
//        return capacity;
//    }
//
//    ~Stack();
//};
//
//Stack::Stack(int len) {
//    arr = new int[len];
//    top = -1;
//    capacity = len;
//}
//
//void Stack::resize() {
//    if (capacity == 0) {
//        capacity = 1;
//        return;
//    }
//    int *newArr = new int[capacity * 2];
//    for (int i = 0; i < capacity; i++) {
//        newArr[i] = arr[i];
//    }
//    capacity *= 2;
//    delete[] arr;
//    arr = newArr; //присваиваем переменной arr указатель на наш новый расширенный стек
//}
//
//int Stack::pop() {
//    if (isEmpty()) {
//        return -1;
//    }
//    return arr[top--];
//}
//
//void Stack::push(int new_data) {
//    if (isFull()) {
//        resize();
//    }
//    arr[++top] = new_data;
//}
//
//bool Stack::isEmpty() {
//    if (top == -1) {
//        return true;
//    }
//    return false;
//}
//
//bool Stack::isFull() {
//    if (top == capacity - 1) {
//        return true;
//    }
//    return false;
//}
//
//
//Stack::~Stack() {
//    delete[] arr;
//}
//
//bool solution(string *word1, string *word2) {
//    int size = word1->size();
//    Stack my_stack(0);
//    int check = 0;
//
//    for (int i = 0; i < size; i++) {
//        my_stack.push((*word1)[i]);
//
//        while (!my_stack.isEmpty() && my_stack.peeck() == (*word2)[check]) {
//            my_stack.pop();
//            check++;
//        }
//    }
//
//    return my_stack.isEmpty() && check == word2->size();
//}
//
//
//int main(){
//    string word1, word2;
//    cin >> word1 >> word2;
//    bool k = solution(word1, word2);
//    if (k) cout << "YES" << endl;
//    else cout << "NO" << endl;
//
//    return 0;
//}


/*6. Дано множество целых чисел из [0..109] размера n.
 
 Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:

 10% перцентиль
 медиана
 90% перцентиль
 Требования:

 К дополнительной памяти: O(n).
 Среднее время работы: O(n)
 Должна быть отдельно выделенная функция partition.
 Рекурсия запрещена.
 Решение должно поддерживать передачу функции сравнения снаружи.*/

//#include <iostream>
//using namespace std;
//
//template <typename T>
//struct DefaultComparator{
//    bool operator()(const T& l, const T& r) const{
//        return l < r;
//    }
//};
//
//template <typename T, typename Comparator = DefaultComparator<T>>
//int MedianOfThree(T *arr, int idx1, int idx2, int idx3, Comparator comp = Comparator()) {
//    if (comp(arr[idx1], arr[idx2])) {
//        if (comp(arr[idx3], arr[idx1])) {
//            return idx1;
//        }
//        else if (comp(arr[idx2], arr[idx3])) {
//            return idx2;
//        }
//        return idx3;
//    }
//    else if (comp(arr[idx3], arr[idx2])) {
//        return idx2;
//    }
//    return idx3;
//}
//
//template <typename T>
//void input(T *arr, int n) {
//    for (int i = 0; i < n; ++i) {
//        cin >> arr[i];
//    }
//}
//
//template <typename T>
//void show(T *arr, int n) {
//    for (int i = 0; i < n; ++i) {
//        cout << arr[i] << " ";
//    }
//    cout << endl;
//}
//
//template <typename T, typename Comparator = DefaultComparator<T>>
//int partition(T *arr, int l, int r, Comparator comp = Comparator()) {
//    int pivot_idx = MedianOfThree(arr, l, (l + r) / 2, r - 1, comp);
//    swap(arr[pivot_idx], arr[r - 1]);
//    int i = l;
//    int j = l;
//    while (j < r - 1) {
//        if (comp(arr[r - 1], arr[j])) ++j;
//        else {
//            swap(arr[i], arr[j]);
//            ++i;
//            ++j;
//        }
//    }
//    swap(arr[r - 1], arr[i]);
//    return i;
//}
//
//template <typename T, typename Comparator = DefaultComparator<T>>
//void kthElement(T *arr, int size, int k, Comparator comp = Comparator()) {
//    int l = 0;
//    int r = size;
//    while (l < r) {
//        int pivot_pos = partition(arr, l, r, comp);
//        if (pivot_pos == k) return;
//        else if (pivot_pos > k) r = pivot_pos;
//        else l = pivot_pos + 1;
//    }
//}
//
//template <typename T>
//void percentile(T *arr, int n, int percent) {
//    int ind = (percent * n) / 100;
//    kthElement(arr, n, ind);
//    cout << arr[ind] << endl;
//}
//
//
//int main() {
//    int n;
//    cin >> n;
//    
//    int* arr = new int[n];
//    input(arr, n);
//    
//    percentile(arr, n, 10);
//
//    percentile(arr, n, 50);
//    
//    percentile(arr, n, 90);
//
//    delete[] arr;
//    return 0;
//}


/*7. Дан массив неотрицательных целых 64-битных чисел. Количество чисел не больше 1000000. Отсортировать массив методом поразрядной сортировки LSD по байтам.*/

#include <iostream>
using namespace std;

template <typename T>
void input(T *arr, int n) {
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
}

template <typename T>
void show(T *arr, int n) {
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}


void CountingSort(long long *arr, int n, int rank) {
    int const capacity = 256;
    int counters[capacity];

    for (int i = 0; i < capacity; ++i) {
        counters[i] = 0;
    }

    for (int i = 0; i < n; ++i) {
        counters[(arr[i] >> (rank * 8)) & 0xFF]++;
    }

    for (int i = 0; i < capacity - 1; ++i) {
        counters[i + 1] += counters[i];
    }

    long long* temp_arr = new long long[n];

    for (int i = n - 1; i >= 0; --i) {
        temp_arr[--counters[(arr[i] >> (rank * 8)) & 0xFF]] = arr[i]; //берем i-ый байт числа
    }

    copy(&temp_arr[0], &temp_arr[n], &arr[0]);

    delete[] temp_arr;
}

void radixSortLsd(long long *arr, int n) {
    for (int i = 0; i < 8; ++i) {
        CountingSort(arr, n, i);
    }
}

int main() {
    int n;
    cin >> n;
    long long* arr = new long long[n];

    input(arr, n);
    radixSortLsd(arr, n);
    show(arr, n);

    delete [] arr;
    return 0;
}
