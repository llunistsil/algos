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
g++ -std=c++17 -O2 -o "$WORK_DIR/task2" "$CODE_DIR/task2.cpp" || { echo "task2.cpp не скомпилировался"; exit 1; }
g++ -std=c++17 -O2 -o "$WORK_DIR/task7" "$CODE_DIR/task7.cpp" || { echo "task7.cpp не скомпилировался"; exit 1; }
g++ -std=c++17 -O2 -o "$WORK_DIR/task11" "$CODE_DIR/task11.cpp" || { echo "task11.cpp не скомпилировался"; exit 1; }
g++ -std=c++17 -O2 -o "$WORK_DIR/task14" "$CODE_DIR/task14.cpp" || { echo "task14.cpp не скомпилировался"; exit 1; }
g++ -std=c++17 -O2 -o "$WORK_DIR/task20" "$CODE_DIR/task20.cpp" || { echo "task20.cpp не скомпилировался"; exit 1; }

echo ""
echo "=== Задача 2: Заправки ==="

run_test "task2" "Тест 1: 950км, бак 400км, 4 заправки" \
"950
400
4
200 375 550 750" \
"2"

run_test "task2" "Тест 2: невозможно доехать" \
"10
3
4
1 2 5 9" \
"-1"

run_test "task2" "Тест 3: заправок не нужно" \
"200
250
2
100 150" \
"0"

echo ""
echo "=== Задача 7: Проблема сапожника ==="

run_test "task7" "Тест 1: 10 мин, 3 сапога (6,2,8)" \
"10 3
6 2 8" \
"2"

run_test "task7" "Тест 2: 3 мин, 2 сапога (10,20)" \
"3 2
10 20" \
"0"

echo ""
echo "=== Задача 11: Максимальное золото ==="

run_test "task11" "Тест 1: рюкзак 10, слитки 1,4,8" \
"10 3
1 4 8" \
"9"

run_test "task11" "Тест 2: рюкзак 20, слитки 5,10,15,20,25" \
"20 5
5 10 15 20 25" \
"20"

echo ""
echo "=== Задача 14: Максимум выражения ==="

run_test "task14" "Тест 1: 1+5" \
"1+5" \
"6"

run_test "task14" "Тест 2: 5-8+7*4-8+9" \
"5-8+7*4-8+9" \
"200"

echo ""
echo "=== Задача 20: Почти палиндром ==="

run_test "task20" "Тест 1: abcde, K=1" \
"5 1
abcde" \
"12"

run_test "task20" "Тест 2: aaa, K=3" \
"3 3
aaa" \
"6"

echo ""
echo "=== Результат: $PASSED пройдено, $FAILED провалено ==="
[ "$FAILED" -eq 0 ] && exit 0 || exit 1
