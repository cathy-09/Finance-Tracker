# 📊Финансов Мениджър📊

## Описание на проекта
`Финансов Мениджър` е конзолно приложение, което позволява на потребителя да управлява личните си финанси. Системата позволява:
- да се създаде финансов профил
- да се въвеждат месечни доходи и разходи
- да се визуализират отчети
- да се визуализират диаграми
- да се правят прогнози за бъдещи спестявания или дефицити
- да се извеждат месеци по различни критерии

Целта на проекта е потребителят да получи цялостна представа за бюджета си, спестяванията.

## Основни функционалности

| Команда&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; | Описание&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|-------------------------------------------------------------|-------------------------------------------------------------|
| `help`                                                       | Показва `списък` с всички команди.                                                           |
| `setup <months>`                                                       | Създава `нов финансов профил` за избран брой месеци.                                                           |
| `add`                               | Добавя приходи и разходи за даден месец.                                                          |
| `report`                                                       | Показва отчет за всички `въведени` месеци с общ приход, разход и баланс.                                                           |
| `search <month>`                               | Показва детайлна информация за `избран месец` (приходи, разходи, баланс,процентен дял на разходите).                                                          |
| `sort <type>`                                                       | Сортира месеците по `income`, `expense` или `balance` и извежда `топ 3` месеца                                                           |
| `forecast <monthsAhead>`                         | Прогнозира `спестяванията` или `дълговете` за зададен брой месеци напред.                                                          |
| `chart`                                                       | Визуализира годишните приходи и разходи `(balance)` като бар диаграма.                                                           |
| `exit`                                                       | Изход от програмата с финален отчет на въведените данни.                                                           |

<hr style="border-width: 5px !important;">

**При стартиране на програмата се визуализира следното:**
```
=================================
   Welcome to Finance Profile!
=================================
Type 'help' to see commands list.
```

<hr style="border-width: 5px !important;">

### `help`
**При избиране на командата 'help' се визуализира списък с команди:**
```
> help
Available Commands
-------------------------------------------------------------
> setup <month> - Create a new finance profile.
> add - Add income and expenses for a month.
> report - Show report for all months.
> search <month> - Show information for selected month.
> sort <type> - Sort by income, expense or balance.
> forecast <monthsAhead> - Financial forecast for m months.
> chart - Show graphical chart
> exit - Exit the program.
> help - Show list of commands.
-------------------------------------------------------------
```

<hr style="border-width: 5px !important;">

### `setup <month>`
Създава нов финансов профил. Потребителят избира за колко месеца ще се води симулацията. 
```
> setup
Enter number of months: 12
Profile created successfully.
```

<hr style="border-width: 5px !important;">

### `add`
Добавя данни за приходите и разходите на даден месец.
```
> add
Enter month (1-12): 3
Enter income: 2200
Enter expense: 1900
Result: Balance for March: +300.00
```

<hr style="border-width: 5px !important;">

### `report`
Показва отчет за всички въведени месеци с общ приход, разход и баланс.
```
> report
Month      | Income       | Expense      | Balance
--------------------------------------------------------
January    |      2500.00 |      1250.00 |      +1250.00
February   |      2400.00 |      1350.00 |      +1050.00
March      |      2200.00 |      1900.00 |       +300.00
--------------------------------------------------------
Total income: 7100.00
Total expense: 4500.00
Average balance: +866.67
```

<hr style="border-width: 5px !important;">

### `search <month>`
Показва детайлна информация за избран месец: приходи, разходи, баланс и процентен дял на разходите.
```
> search February
Income: 2400
Expense: 1350
Balance: +1050.00
Expense ratio: 56.3%
```

<hr style="border-width: 5px !important;">

### `sort <type>`
Сортира месеците по избран критерий: **`income`**, **`expense`** или **`balance`**.
След сортиране програмата показва **топ 3** месеца с най-висока стойност.
```
> sort balance
Sorted by monthly balance (descending):
1. January: +1250.00
2. February: +1050.00
3. March: +300.00
```

<hr style="border-width: 5px !important;">

### `forecast <monthsAhead>`
Прави прогноза на спестяванията или дълговете за зададен брой месеци напред.
```
> forecast 6
Current savings: +2600.00
Average monthly change: +866.67
Predicted savings after 6 months: +7800.00
```

<hr style="border-width: 5px !important;">

### `chart`
Визуализира годишните приходи и разходи `(balance)` чрез бар диаграма. Всеки символ `#` представлява определена сума.
```
> chart
=== YEARLY FINANCIAL CHART ===
 1250 | #
  950 | # #
  650 | # #
  350 | # #
   50 | # # #
      ------------------------
      Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec
```

<hr style="border-width: 5px !important;">

### `exit`
Излиза от програмата. При изход се извежда финален отчет.
```
> exit
Month      | Income       | Expense      | Balance
--------------------------------------------------------
January    |      2500.00 |      1250.00 |      +1250.00
February   |      2400.00 |      1350.00 |      +1050.00
March      |      2200.00 |      1900.00 |       +300.00
--------------------------------------------------------
Total income: 7100.00
Total expense: 4500.00
Average balance: +866.67
```

<hr style="border-width: 5px !important;">


## Архитектура на проекта
```cpp
Finance-Tracker/
├── Header Files/          # Декларации на функции и структури
│   ├── add.h             
│   ├── chart.h           
│   ├── commands.h        
│   ├── constants.h       # Константи
│   ├── forecast.h        
│   ├── report.h          
│   ├── search.h          
│   ├── setup.h           
│   ├── sort.h            
│   ├── structures.h      # Дефиниции на структури от данни
│   └── utils.h           # Помощни функции
│
├── Source Files/         # Имплементация на функционалности
│   ├── add.cpp
│   ├── chart.cpp
│   ├── commands.cpp
│   ├── Finance-Tracker.cpp  # Главен файл (main)
│   ├── forecast.cpp
│   ├── report.cpp
│   ├── search.cpp
│   ├── setup.cpp
│   ├── sort.cpp
│   └── utils.cpp
```
