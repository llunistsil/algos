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
    actual=$(cat "$WORK_DIR/output.txt")
    expected_trimmed=$(echo "$expected" | sed '/^$/d')

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
g++ -std=c++17 -O2 -o "$WORK_DIR/task1" "$CODE_DIR/task1.cpp" || { echo "task1.cpp не скомпилировался"; exit 1; }
g++ -std=c++17 -O2 -o "$WORK_DIR/task6" "$CODE_DIR/task6.cpp" || { echo "task6.cpp не скомпилировался"; exit 1; }
g++ -std=c++17 -O2 -o "$WORK_DIR/task7" "$CODE_DIR/task7.cpp" || { echo "task7.cpp не скомпилировался"; exit 1; }

echo ""
echo "=== Задача 1: Наивный поиск подстроки ==="

run_test "task1" "Тест 1: пример из условия" \
"aba
abaCaba" \
"2
1 5"

run_test "task1" "Тест 2: нет вхождений" \
"xyz
abcdef" \
"0
"

run_test "task1" "Тест 3: полное совпадение" \
"abc
abc" \
"1
1"

run_test "task1" "Тест 4: перекрывающиеся вхождения" \
"aa
aaaa" \
"3
1 2 3"

echo ""
echo "=== Задача 6: Z-функция ==="

run_test "task6" "Тест 1: пример из условия 1" \
"aaaAAA" \
"2 1 0 0 0"

run_test "task6" "Тест 2: пример из условия 2" \
"abacaba" \
"0 1 0 3 0 1"

run_test "task6" "Тест 3: все одинаковые символы" \
"aaaaa" \
"4 3 2 1"

echo ""
echo "=== Задача 7: Наибольшая общая подстрока ==="

run_test "task7" "Тест 1: пример из условия 1" \
"cool
toolbox" \
"1 1 3"

run_test "task7" "Тест 2: нет общей подстроки" \
"aaa
bb" \
"0 0 0"

# Тест 3: пример из условия 3 - допустимы оба ответа: "0 4 3" или "2 3 3"
# Проверяем вручную
echo -e "aabaa\nbabbaab" > "$WORK_DIR/input.txt"
cd "$WORK_DIR" && ./task7 > /dev/null 2>&1
actual=$(cat "$WORK_DIR/output.txt")
if [ "$actual" = "0 4 3" ] || [ "$actual" = "2 3 3" ]; then
    echo "  [OK] Тест 3: пример из условия 3 (допустимы оба ответа)"
    PASSED=$((PASSED+1))
else
    echo "  [FAIL] Тест 3: пример из условия 3 (допустимы оба ответа)"
    echo "    Ожидалось: '0 4 3' или '2 3 3'"
    echo "    Получено:  '$actual'"
    FAILED=$((FAILED+1))
fi

run_test "task7" "Тест 4: полное совпадение" \
"abc
abc" \
"0 0 3"

run_test "task7" "Тест 5: одна общая буква" \
"abc
defc" \
"2 3 1"

echo ""
echo "=== Результат: $PASSED пройдено, $FAILED провалено ==="
[ "$FAILED" -eq 0 ] && exit 0 || exit 1
