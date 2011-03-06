# Parser wyrażeń zapisanych w notacji wrostkowej

## Treść zadania:

Napisać program umożliwiający przechowywanie wyrażeń algebraicznych i
obliczanie wartości tych wyrażeń dla zadanych wartości zmiennych.

## Wykonanie:

### Kompilacja:

Wywołanie `make all` powinno załatwić sprawę. W przeciwnym przypadku output
jest twoim przyjacielem.

### Obsługa:

Program umożliwia definiowanie wyrażeń poprzez wywowałanie polecenia `def` lub
`d`. Następnie wymaga podania nazwy i samego wyrażenia. Program rozpoznaje
podstawowe działania : `+ - / *`, oraz uznaje `-` jako znak wartości ujemnej.

Po zdefiniowaniu wyrażenia można kazać programowi wyliczyć jego wartość przez
polecenie `cal` lub `c`. Wymagane jest podanie nazwy wyrażenia i ciągu
wartości dla zmiennych w formacie: `a = 3.5; b = 1; c = -5;`.

Z założenia program nie akceptuje wyrażenia jeśli jest niepoprawne składniowo.
Jeśli wyrażenie zostanie zaakceptowane, program będzie próbował je wyliczyć i
prawdopodbnie się przewróci.

### Testy:

Testy są w `tests/`. Pokrywają podstawowe wymagania. Kompilacja i wywołanie
testów jest zdefiniowane w `Makefile` pod regułą `make test`.

## Autorzy:

* Tomasz Cudziło <cudzilot@ee.pw.edu.pl>
