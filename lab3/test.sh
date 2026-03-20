#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
CODE_DIR="$SCRIPT_DIR/../src"
WORK_DIR=$(mktemp -d)
trap "rm -rf $WORK_DIR" EXIT

PASSED=0
FAILED=0

run_test() {
    local task="$1"
    local test_name="$2"
    local input="$3"
    local expected="$4"

    echo -e "$input" > "$WORK_DIR/input.txt"
    cd "$WORK_DIR" && ./$task > /dev/null 2>&1
    actual=$(cat "$WORK_DIR/output.txt" | tr -d '\n' | xargs)
    expected_trimmed=$(echo "$expected" | tr -d '\n' | xargs)

    if [ "$actual" = "$expected_trimmed" ]; then
        echo "  [OK] $test_name"
        PASSED=$((PASSED+1))
    else
        echo "  [FAIL] $test_name"
        echo "    Ожидалось: '$expected_trimmed'"
        echo "    Получено:  '$actual'"
        FAILED=$((FAILED+1))
    fi
}

echo "=== Компиляция ==="
g++ -std=c++17 -O2 -o "$WORK_DIR/task4" "$CODE_DIR/task4.cpp" || { echo "task4.cpp не скомпилировался"; exit 1; }
g++ -std=c++17 -O2 -o "$WORK_DIR/task9" "$CODE_DIR/task9.cpp" || { echo "task9.cpp не скомпилировался"; exit 1; }
g++ -std=c++17 -O2 -o "$WORK_DIR/task15" "$CODE_DIR/task15.cpp" || { echo "task15.cpp не скомпилировался"; exit 1; }

echo ""
echo "=== Задача 4: Порядок курсов (топологическая сортировка) ==="

run_test "task4" "Тест 1: пример из условия 1" \
"4 3
1 2
4 1
3 1" \
"4 3 1 2"

run_test "task4" "Тест 2: пример из условия 2" \
"4 1
3 1" \
"4 3 2 1"

run_test "task4" "Тест 3: пример из условия 3" \
"5 7
2 1
3 2
3 1
4 3
4 1
5 2
5 3" \
"5 4 3 2 1"

echo ""
echo "=== Задача 9: Аномалии курсов валют (отрицательный цикл) ==="

run_test "task9" "Тест 1: пример из условия (есть отрицательный цикл)" \
"4 4
1 2 -5
4 1 2
2 3 2
3 1 1" \
"1"

run_test "task9" "Тест 2: без отрицательного цикла" \
"3 3
1 2 1
2 3 2
3 1 3" \
"0"

echo ""
echo "=== Задача 15: Герои (BFS) ==="

run_test "task15" "Тест 1: пример из условия 1" \
"5 5
11111
10001
10001
10001
11111
4 4 10
2 2 1
2 3 2
3 2 3
3 3 4" \
"10"

run_test "task15" "Тест 2: пример из условия 2 (никто не успевает)" \
"5 5
11111
10001
10111
10101
11111
4 4 10
2 2 1
2 2 2
2 2 3
2 2 4" \
"0"

echo ""
echo "=== Результат: $PASSED пройдено, $FAILED провалено ==="
[ "$FAILED" -eq 0 ] && exit 0 || exit 1
