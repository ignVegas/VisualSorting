#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <thread>
#include <random>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int BAR_WIDTH = 1;
const int BAR_GAP = 1;
const int NUM_BARS = WINDOW_WIDTH / (BAR_WIDTH + BAR_GAP);

bool isSorted(const std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

void drawBars(sf::RenderWindow& window, const std::vector<int>& bars) {
    window.clear();
    for (size_t i = 0; i < bars.size(); ++i) {
        sf::RectangleShape rect(sf::Vector2f(BAR_WIDTH, bars[i]));
        rect.setPosition(i * (BAR_WIDTH + BAR_GAP), WINDOW_HEIGHT - bars[i]);
        rect.setFillColor(sf::Color::Blue);
        window.draw(rect);
    }
    window.display();
}

void bubbleSort(std::vector<int>& arr, sf::RenderWindow& window) {
    bool swapped;
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        swapped = false;
        for (size_t j = 0; j < arr.size() - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                drawBars(window, arr);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void bogoSort(std::vector<int>& arr, sf::RenderWindow& window) {
    std::random_device rd;
    std::mt19937 g(rd());
    int maxIterations = 10000; // Adjust as needed
    int iterations = 0;
    while (!isSorted(arr) && iterations < maxIterations) {
        std::shuffle(arr.begin(), arr.end(), g);
        drawBars(window, arr);
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Add delay for visualization
        iterations++;
    }
    if (!isSorted(arr)) {
        std::cout << "Bogo Sort failed to sort the array within the maximum number of iterations.\n";
    }
}



void selectionSort(std::vector<int>& arr, sf::RenderWindow& window) {
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(arr[i], arr[minIndex]);
        drawBars(window, arr);
    }
}

void insertionSort(std::vector<int>& arr, sf::RenderWindow& window) {
    for (size_t i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
        drawBars(window, arr);
    }
}

int partition(std::vector<int>& arr, int low, int high, sf::RenderWindow& window) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
            drawBars(window, arr);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    drawBars(window, arr);
    return i + 1;
}

void quickSort(std::vector<int>& arr, int low, int high, sf::RenderWindow& window) {
    if (low < high) {
        int pivot = partition(arr, low, high, window);
        quickSort(arr, low, pivot - 1, window);
        quickSort(arr, pivot + 1, high, window);
    }
}

void chooseAlgorithm(std::vector<int>& bars, sf::RenderWindow& window) {
    std::cout << "Choose a sorting algorithm:\n"
        << "1. Bubble Sort\n"
        << "2. Selection Sort\n"
        << "3. Insertion Sort\n"
        << "4. Quick Sort\n"
        << "5. Bogo Sort\n";
    int choice;
    std::cin >> choice;

    // Clear input buffer
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice) {
    case 1:
        std::cout << "Press any key to start sorting...\n";
        std::cin.get(); // Wait for user input
        bubbleSort(bars, window);
        break;
    case 2:
        std::cout << "Press any key to start sorting...\n";
        std::cin.get(); // Wait for user input
        selectionSort(bars, window);
        break;
    case 3:
        std::cout << "Press any key to start sorting...\n";
        std::cin.get(); // Wait for user input
        insertionSort(bars, window);
        break;
    case 4:
        std::cout << "Press any key to start sorting...\n";
        std::cin.get(); // Wait for user input
        quickSort(bars, 0, bars.size() - 1, window);
        break;
    case 5:
        std::cout << "Press any key to start sorting...\n";
        std::cin.get(); // Wait for user input
        bogoSort(bars, window);
        break;
    default:
        std::cout << "Invalid choice\n";
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Visual Sorting");

    std::vector<int> bars(NUM_BARS);
    for (int i = 0; i < NUM_BARS; ++i) {
        bars[i] = rand() % (WINDOW_HEIGHT - 50) + 50;
    }

    chooseAlgorithm(bars, window);

    

    

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}
